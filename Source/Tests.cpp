#include <cassert>

#include "DataTypes/Ops/Ops.h"

namespace FPTL {
	namespace Runtime {
		int doTest()
		{
			const auto iV1 = DataBuilders::createInt(-10);
			const auto iV2 = DataBuilders::createInt(20);

			// Тест целочисленных операций.
			assert(iV1.getOps());

			assert(iV1.getOps()->add(iV1, iV2).mIntVal == 10);
			assert(iV1.getOps()->sub(iV1, iV2).mIntVal == -30);
			assert(iV1.getOps()->mul(iV1, iV2).mIntVal == -200);
			assert(iV2.getOps()->div(iV2, iV1).mIntVal == -2);
			assert(iV1.getOps()->mod(iV1, iV2).mIntVal == -10);
			assert(iV1.getOps()->abs(iV1).mIntVal == 10);

			assert(iV1.getOps()->equal(iV1, iV1).mIntVal);
			assert(!iV1.getOps()->equal(iV2, iV1).mIntVal);
			assert(iV1.getOps()->less(iV1, iV2).mIntVal);
			assert(iV2.getOps()->greater(iV2, iV1).mIntVal);

			// Тест операций с плавающей точкой.
			const auto dV1 = DataBuilders::createDouble(-10.0);
			const auto dV2 = DataBuilders::createDouble(20.0);

			assert(dV1.getOps());

			assert(dV1.getOps()->add(dV1, dV2).mDoubleVal == 10.0);
			assert(dV1.getOps()->sub(dV1, dV2).mDoubleVal == -30.0);
			assert(dV1.getOps()->mul(dV1, dV2).mDoubleVal == -200.0);
			assert(dV2.getOps()->div(dV2, dV1).mDoubleVal == -2.0);
			assert(dV1.getOps()->abs(dV1).mDoubleVal == 10.0);

			assert(dV1.getOps()->equal(dV1, dV1).mIntVal);
			assert(!dV1.getOps()->equal(dV2, dV1).mIntVal);
			assert(dV1.getOps()->less(dV1, dV2).mIntVal);
			assert(dV2.getOps()->greater(dV2, dV1).mIntVal);

			// Тест смешанных операций.

			assert(iV1.getOps()->combine(dV2.getOps())->add(iV1, dV2).mDoubleVal == 10.0);
			assert(iV1.getOps()->combine(dV2.getOps())->sub(iV1, dV2).mDoubleVal == -30.0);
			assert(dV2.getOps()->combine(iV1.getOps())->mul(iV1, dV2).mDoubleVal == -200.0);
			assert(iV1.getOps()->combine(dV2.getOps())->div(iV2, dV1).mDoubleVal == -2.0);

			assert(iV1.getOps()->combine(dV1.getOps())->equal(iV1, dV1).mIntVal);
			assert(!dV2.getOps()->combine(iV1.getOps())->equal(dV2, iV1).mIntVal);
			assert(iV1.getOps()->combine(dV2.getOps())->less(dV1, iV2).mIntVal);
			assert(dV2.getOps()->combine(iV1.getOps())->greater(dV2, iV1).mIntVal);

			// Тест значение "неопределенность".
			const auto uV = DataBuilders::createUndefinedValue();
			const auto bV1 = DataBuilders::createBoolean(true);
			const auto bV2 = DataBuilders::createBoolean(false);

			assert(!uV.getOps()->equal(uV, bV1).mIntVal);
			assert(!uV.getOps()->equal(uV, bV2).mIntVal);

			//assert(!v1.EqualTo(uv));
			assert(!uV.getOps()->equal(uV, iV1).mIntVal);

			return -1;
		}

#ifdef _DEBUG
		static int test = doTest();
#endif
	}
}
