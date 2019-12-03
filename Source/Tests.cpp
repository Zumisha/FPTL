#include <cassert>

#include "DataTypes/Ops/BaseOps.h"
#include "DataTypes/Ops/BooleanOps.h"
#include "DataTypes/Ops/IntegerOps.h"
#include "DataTypes/Ops/DoubleOps.h"

namespace FPTL {
	namespace Runtime {
		int doTest()
		{
			const auto iV1 = IntegerOps::Create(-10);
			const auto iV2 = IntegerOps::Create(20);

			// Тест целочисленных операций.
			assert(iV1.ops);

			assert((iV1 + iV2).ToInt() == 10);
			assert((iV1 - iV2).ToInt() == -30);
			assert((iV1 * iV2).ToInt() == -200);
			assert((iV2 / iV1).ToInt() == -2);
			assert((iV1 % iV2).ToInt() == -10);
			assert(iV1.Abs().ToInt() == 10);

			assert(iV1.EqualTo(iV1));
			assert(!iV1.EqualTo(iV2));
			assert(iV1.LessThan(iV2));
			assert(iV2.GreaterThan(iV1));

			// Тест операций с плавающей точкой.
			const auto dV1 = DoubleOps::Create(-10.0);
			const auto dV2 = DoubleOps::Create(20.0);

			assert(dV1.ops);

			assert((dV1 + dV2).ToInt() == 10.0);
			assert((dV1 - dV2).ToInt() == -30.0);
			assert((dV1 * dV2).ToInt() == -200.0);
			assert((dV2 / dV1).ToInt() == -2.0);
			assert(dV1.Abs().ToInt() == 10.0);

			assert(dV1.EqualTo(dV1));
			assert(!dV1.EqualTo(dV2));
			assert(dV1.LessThan(dV2));
			assert(dV2.GreaterThan(dV1));

			// Тест смешанных операций.

			assert((iV1 + dV2).ToInt() == 10.0);
			assert((iV1 - dV2).ToInt() == -30.0);
			assert((iV1 * dV2).ToInt() == -200.0);
			assert((dV2 / iV1).ToInt() == -2.0);
			assert((iV1 % dV2).ToInt() == -10.0);

			assert(iV1.EqualTo(dV1));
			assert(!iV1.EqualTo(dV2));
			assert(iV1.LessThan(dV2));
			assert(dV2.GreaterThan(iV1));

			assert((dV1 + iV2).ToInt() == 10.0);
			assert((dV1 - iV2).ToInt() == -30.0);
			assert((dV1 * iV2).ToInt() == -200.0);
			assert((iV2 / dV1).ToInt() == -2.0);

			assert(dV1.EqualTo(iV1));
			assert(!dV1.EqualTo(iV2));
			assert(dV1.LessThan(iV2));
			assert(iV2.GreaterThan(dV1));

			// Тест значение "неопределенность".
			const auto uV = BaseOps::Create();
			const auto bV1 = BooleanOps::Create(true);
			const auto bV2 = BooleanOps::Create(false);

			assert(!uV.EqualTo(bV1));
			assert(!uV.EqualTo(bV2));

			//assert(!v1.EqualTo(uv));
			assert(!uV.EqualTo(iV1));

			return -1;
		}

#ifdef _DEBUG
		static int test = doTest();
#endif
	}
}
