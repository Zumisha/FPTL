#include <sstream>
#include <utility>

#include "Macros.h"
#include "Value.h"
#include "ADTValue.h"
#include "Evaluator/Context.h"
#include "DataTypes/Ops/ADTOps.h"

namespace FPTL {
	namespace Runtime {
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
		void Constructor::execConstructor(SExecutionContext & aCtx) const
		{
			// Проверяем соответствие типов входного кортежа сигнатуре конструктора.
			std::unordered_map<std::string, struct TypeInfo> params;

			const size_t ar = arity();
			auto values = std::vector<Value>(ar);

			for (size_t i = 0; i < ar; ++i)
			{
				auto & arg = aCtx.getArg(i);

#if fptlDebugBuild
				if (!TypeInfo::matchType(arg.Type(), &mReferenceType[i], params))
				{
					throw std::runtime_error("type mismatch. Actual:" + arg.Type().typeName + " Expected: " + mReferenceType[i].typeName + ".");
				}
#endif

				values[i] = arg;
			}

			// С типами все ок, cоздаём абстрактный тип данных.
			aCtx.push(ADTOps::Create(this, values));
		}

		void Constructor::execDestructor(SExecutionContext& aCtx) const
		{
			// Проверяем что значение было создано именно этим деструктором.
			const auto& arg = aCtx.getArg(0);

#if fptlDebugBuild
			if (arg.Type().typeName != ADTOps::staticTypeInfo.typeName) return;
#endif

			const auto atd = static_cast<ADTValue*>(arg.mOtherVal);

			if (atd->ctor == this)
			{
				// Разворачиваем кортеж.
				for (size_t i = 0; i < arity(); ++i)
				{
					aCtx.push(atd->values[i]);
				}

				return;
			}

			// Добавляем UndefinedValue.
			aCtx.push(BaseOps::Create());
		}

	}
}
