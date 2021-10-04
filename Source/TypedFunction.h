#pragma once

#include <functional>
#include <utility>
#include <typeinfo>
#include <utility>

#include "Evaluator/Context.h"


namespace FPTL::Runtime
{
	typedef std::function<void(SExecutionContext &)> TFunction;

	class TypedFunction
	{

	private:

		template <typename ...T>
		static void PutResult(SExecutionContext& aCtx, std::tuple <T...> res)
		{
			for (size_t i = 0; i < sizeof...(T); ++i)
			{
				aCtx.push(DataValue(std::get<i>(res)));
			}
		}

		template <typename T>
		static void PutResult(SExecutionContext& aCtx, T res)
		{
			aCtx.push(DataValue(res));
		}

		template <size_t i, typename Arg>
		static Arg getArgs(const SExecutionContext& aCtx)
		{
			return getArg<Arg>(aCtx, i);
		}

		template <typename T>
		static bool getArg(const SExecutionContext& aCtx, size_t i)
		{
			return static_cast<T>(aCtx.getArg(i).GetBool());
		}

		template <typename T>
		static int64_t getArg(const SExecutionContext& aCtx, size_t i)
		{
			return static_cast<T>(aCtx.getArg(i).GetInt64());
		}

		template <typename T>
		static double getArg(const SExecutionContext& aCtx, size_t i)
		{
			return static_cast<T>(aCtx.getArg(i).GetDouble());
		}

		template <typename T>
		static T getArg(const SExecutionContext& aCtx, size_t i)
		{
			return static_cast<T>(aCtx.getArg(i).GetPtr());
		}

	public:
	public:

		TypedFunction(TypedFunction&& other) noexcept
		{
			std::swap(other.isLong, isLong);
			std::swap(other.isRepeatingInput, isRepeatingInput);
			std::swap(other.inputType, inputType);
			std::swap(other.outputType, outputType);
			std::swap(other.function, function);
		}

		TypedFunction& operator=(TypedFunction&& other) noexcept
		{
			if (this != &other)
			{
				std::swap(other.isLong, isLong);
				std::swap(other.isRepeatingInput, isRepeatingInput);
				std::swap(other.inputType, inputType);
				std::swap(other.outputType, outputType);
				std::swap(other.function, function);
			}

			return *this;
		}

		TypedFunction(const TypedFunction&) = delete;
		TypedFunction& operator=(const TypedFunction& other) = delete;

		template<typename ...R, typename ...Args>
		TypedFunction(std::tuple<R...>(*aFunction)(Args...), const bool aIsLong, const bool aIsRepeatingInput) :
			inputType(std::tuple<Args...>::_Myfirst),
			outputType(std::tuple<R...>()),
			isLong(aIsLong),
			isRepeatingInput(aIsRepeatingInput)
		{
			function = [&](SExecutionContext& aCtx)
			{
				size_t i = 0;
				PutResult(aCtx, aFunction(getArg<Args>(aCtx, i++)...));
			};
		}

		template<typename R, typename ...Args>
		TypedFunction(R(*aFunction)(Args...), const bool aIsLong, const bool aIsRepeatingInput) :
			isLong(aIsLong),
			isRepeatingInput(aIsRepeatingInput)
		{
			for (size_t i = 0; i < sizeof...(Args); ++i)
			{
				inputType.push_back(std::tuple_element<i, std::tuple<Args...>>::type);
			}
			outputType.push_back(typeid(R));

			function = [&](SExecutionContext& aCtx)
			{
				size_t i = 0;
				PutResult(aCtx, aFunction(getArg<Args>(aCtx, i++)...));
			};
		}

		TFunction function;
		std::vector<const type_info> inputType;
		std::vector<const type_info> outputType;
		bool isLong;
		bool isRepeatingInput;
	};

}
