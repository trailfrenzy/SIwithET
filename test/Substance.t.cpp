#include "MetricTypes.h"
#include "DerivedUnits.h"
#include "WhatAmI.h"
#include "Dimension.h"
#include "operators.h"
#include "ExpectUnitTest.h"
#include <gtest/gtest.h>

TEST(Substance, Sec)
{
    using namespace SOU::literals;
    auto const sec = 4.0_sec;
    EXPECT_EQ(SOU::WhatAmI(sec), "second");
    EXPECT_EQ(SOU::Dim(sec), "[T]");
}

TEST(Substance, Mole)
{
    using namespace SOU::literals;

    static_assert(Metric::t_mole::eN == 1);
    static_assert(Metric::t_mole::eJ == 0);

    Metric::t_mole moles = 2.0_mole;
    EXPECT_EQ(SOU::WhatAmI(moles), "mole");
    EXPECT_EQ(SOU::Dim(moles), "[N]");
}

TEST(Substance, ReturnMole)
{
    using namespace SOU::literals;

    auto moles = 200.0_kat * 4.0_sec;
    EXPECT_UNIT_EQ(moles, 800.0);
    EXPECT_EQ(SOU::WhatAmI(moles), "mole");
    EXPECT_EQ(SOU::Dim(moles), "[N]");
}

TEST(Substance, UseLux)
{
    using namespace SOU::literals;
    auto cad = 10.0_lux * (4.0_sec * 5.0_sec);
    EXPECT_UNIT_EQ(cad, 200.0);
    EXPECT_EQ(SOU::WhatAmI(cad), "candela");
    EXPECT_EQ(SOU::Dim(cad), "[J]");

}