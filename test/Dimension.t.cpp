#include "MetricTypes.h"
#include "DerivedUnits.h"
#include "WhatAmI.h"
#include "Dimension.h"
#include "operators.h"
#include "ExpectUnitTest.h"
#include <gtest/gtest.h>

TEST(Dimension, seconds)
{
    using namespace SOU::literals;
    auto const sec = 4.0_sec;
    EXPECT_EQ(SOU::Dim(sec), "[T]");
    //static_assert(SOU::Dim(sec) == "[T]")
}

TEST(Dimension, meters)
{
    using namespace SOU::literals;
    auto const meters = 4.0_meter;
    EXPECT_EQ(SOU::Dim(meters), "[L]");
}

TEST(Dimension, Hertz) {
    using namespace SOU::literals;
    auto const hertz = 5.0_hertz;
    EXPECT_EQ(SOU::Dim(hertz), "1/[T]");
}
TEST(Dimension, Newton) {
    using namespace SOU::literals;
    auto const arg = 5.0_newton;
    EXPECT_EQ(SOU::Dim(arg), "[M][L]/[T]^2");
}
TEST(Dimension, Pascal)
{
    using namespace SOU::literals;
    auto const arg = 5.0_pascal;
    EXPECT_EQ(SOU::Dim(arg), "[M]/[L][T]^2");
}

TEST(Dimension, Katal)
{
    using namespace SOU::literals;
    auto const arg = 5.0_kat;
    EXPECT_EQ(SOU::Dim(arg), "[N]/[T]");
}

TEST(Dimension, Lux)
{
    using namespace SOU::literals;
    auto const arg = 5.0_lux;
    EXPECT_EQ(SOU::Dim(arg), "[J]/[L]^2");
}

// Copyright © 2005-2023 "Curt" Leslie L. Martin, All rights reserved.
// curt.leslie.lewis.martin@gmail.com
//
// Permission to use, copy, modify, and distribute this software for any
// purpose is hereby granted without fee, provided that this copyright and
// permissions notice appear in all copies and derivatives.
//
// This software is provided "as is" without express or implied warranty.
