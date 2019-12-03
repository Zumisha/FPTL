#include <sstream>
#include <utility>

#include "Ops.h"
#include "ADTOps.h"
#include "GC/CollectedHeap.h"
#include "GC/GarbageCollector.h"
#include "Evaluator/Context.h"

namespace FPTL
{
	namespace Runtime
	{
		struct DataValueArray : public Collectable
		{
			DataValue values[];

			static size_t size(const size_t n)
			{
				return sizeof(DataValueArray) + n * sizeof(DataValue);
			}
		};

		const DataValue & ADTValue::operator[](const size_t i) const
		{
			return values->values[i];
		}

		DataValue & ADTValue::operator[](const size_t i)
		{
			return values->values[i];
		}

		size_t ADTValue::size() const
		{
			return DataValueArray::size(ctor->arity());
		}

		//-------------------------------------------------------------------------------

		// Операции с абстрактным типом данных.
		class ADTOps : public Ops
		{
			ADTOps() = default;

		public:
			static ADTOps * get()
			{
				static ADTOps ops;
				return &ops;
			}

			TypeInfo getType(const DataValue & aVal) const override
			{
				return *aVal.mADT->ctor->targetType();
			}

			// Добавлять сюда методы по мере добавления новых типов.
			const Ops * combine(const Ops * aOther) const override
			{
				throw invalidOperation("combine");
			}

			const Ops * withOps(class Ops const * aOps) const override
			{
				throw invalidOperation("with Ops");
			}

			const Ops * withOps(class IntegerOps const * aOps) const override
			{
				throw invalidOperation("with IntegerOps");
			}

			const Ops * withOps(class BooleanOps const * aOps) const override
			{
				throw invalidOperation("with BooleanOps");
			}

			const Ops * withOps(class DoubleOps const * aOps) const override
			{
				throw invalidOperation("with DoubleOps");
			}

			const Ops * withOps(class StringOps const * aOps) const override
			{
				throw invalidOperation("with StringOps");
			}

			// Преобразование типов.
			long long toInt(const DataValue & aVal) const override
			{
				throw invalidOperation("toInt");
			}

			double toDouble(const DataValue & aVal) const override
			{
				throw invalidOperation("toDouble");
			}

			StringValue * toString(const DataValue & aVal) const override
			{
				throw invalidOperation("toString");
			}

			// Арифметические функции.
			DataValue add(const DataValue & aLhs, const DataValue & aRhs) const override
			{
				throw invalidOperation("add");
			}

			DataValue sub(const DataValue & aLhs, const DataValue & aRhs) const override
			{
				throw invalidOperation("sub");
			}

			DataValue mul(const DataValue & aLhs, const DataValue & aRhs) const override
			{
				throw invalidOperation("mul");
			}

			DataValue div(const DataValue & aLhs, const DataValue & aRhs) const override
			{
				throw invalidOperation("div");
			}

			DataValue mod(const DataValue & aLhs, const DataValue & aRhs) const override
			{
				throw invalidOperation("mod");
			}

			DataValue abs(const DataValue & aArg) const override
			{
				throw invalidOperation("abs");
			}

			// Функции сравнения.
			DataValue equal(const DataValue & aLhs, const DataValue & aRhs) const override
			{
				// TODO: возможно эту функцию можно определить.
				throw invalidOperation("equal");
			}

			DataValue less(const DataValue & aLhs, const DataValue & aRhs) const override
			{
				throw invalidOperation("less");
			}

			DataValue greater(const DataValue & aLhs, const DataValue & aRhs) const override
			{
				throw invalidOperation("greater");
			}

			void mark(const DataValue & aVal, ObjectMarker * marker) const override
			{
				if (marker->markAlive(aVal.mADT->values, aVal.mADT->size()))
				{
					for (size_t i = 0; i < aVal.mADT->ctor->arity(); i++)
					{
						marker->addChild(&(*aVal.mADT)[i]);
					}
				}
			}

			// Вывод в поток.
			void print(const DataValue & aVal, std::ostream & aStream) const override
			{
				const auto val = aVal.mADT;
				const size_t arity = val->ctor->arity();

				if (arity > 0)
				{
					aStream << "(";

					for (size_t i = 0; i < arity; ++i)
					{
						(*val)[i].getOps()->print((*val)[i], aStream);

						if (i + 1 < arity)
						{
							aStream << "*";
						}
					}

					aStream << ").";
				}

				aStream << val->ctor->name();
			}

			void write(const DataValue & aVal, std::ostream & aStream) const override
			{
				throw invalidOperation("write");
			}

			DataValue read(std::istream & aStream) const override
			{
				throw invalidOperation("read");
			}

		private:
			static std::runtime_error invalidOperation(const char * aOpName)
			{
				std::stringstream message;
				message << "invalid operation '" << aOpName << "' on type string";
				return std::runtime_error(message.str());
			}
		};

		//-------------------------------------------------------------------------------
		Constructor::Constructor(std::string aConstructorName, const std::string & aTypeName,
			std::vector<TypeInfo> aRefType, const std::vector<std::string> & aParameters)
			: mConstructorName(std::move(aConstructorName)),
			mTypeName(aTypeName),
			mReferenceType(std::move(aRefType)),
			mTargetType(aTypeName)
		{
			for (auto &param : aParameters)
			{
				mTargetType.typeParameters.emplace_back(param, TypeInfo(param));
			}
		}

		//-------------------------------------------------------------------------------
		Constructor::~Constructor() = default;

		//-------------------------------------------------------------------------------
		void Constructor::execConstructor(SExecutionContext & aCtx) const
		{
			// Проверяем соответствие типов входного кортежа сигнатуре конструктора.
			std::unordered_map<std::string, struct TypeInfo> params;

			const size_t ar = arity();
			auto values = aCtx.heap().alloc<DataValueArray>(DataValueArray::size(ar));

			for (size_t i = 0; i < ar; ++i)
			{
				auto & arg = aCtx.getArg(i);

				if (!TypeInfo::matchType(arg.getOps()->getType(arg), &mReferenceType[i], params))
				{
					throw std::runtime_error("type mismatch. Actual:" + arg.getOps()->getType(arg).typeName + " Expected: " + mReferenceType[i].typeName + ".");
				}

				values->values[i] = arg;
			}

			// С типами все ок, cоздаём абстрактный тип данных.
			aCtx.push(DataBuilders::createADT(new ADTValue(this, values.ptr()), ADTOps::get()));
		}

		//-------------------------------------------------------------------------------
		void Constructor::execDestructor(SExecutionContext & aCtx) const
		{
			// Проверяем что значение было создано именно этим деструктором.
			auto & arg = aCtx.getArg(0);

			if (arg.getOps() == ADTOps::get())
			{
				const auto adt = arg.mADT;

				if (adt->ctor == this)
				{
					// Разворачиваем кортеж.
					for (size_t i = 0; i < arity(); ++i)
					{
						aCtx.push((*adt)[i]);
					}

					return;
				}
			}

			// Добавляем UndefinedValue.
			aCtx.push(DataBuilders::createUndefinedValue());
		}

		//-------------------------------------------------------------------------------
		EmptyConstructor::EmptyConstructor(const std::string & aConstructorName, const std::string & aTypeName)
			: Constructor(aConstructorName, aTypeName, std::vector<TypeInfo>(), std::vector<std::string>()),
			mTypeInfo(aTypeName)
		{
		}
	}
}
