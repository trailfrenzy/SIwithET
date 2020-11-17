#include "SOU_math.h"
#include "MetricBaseUnits.h"
#include "TimeAtomicUnits.h"
#include "operators.h"
#include "ExpectUnitTest.h"
#include <gtest/gtest.h>

namespace AT = Metric::AtomicUnit;

typedef SOU::MakeType< Metric::AtomicUnit::Meter, AT::second, Metric::AtomicUnit::kilogram, Metric::AtomicUnit::kelvin, Metric::AtomicUnit::ampere > t_Base;
typedef t_Base::MakeDim<0, 1, 0, 0, 0>::type t_sec;
typedef t_Base::MakeDim<0, 0, 1, 0, 0>::type t_mass; // kilogram
typedef t_Base::MakeDim<1, 0, 0, 0, 0>::type t_m; // meter

TEST(MathFunc, Sine)
{
   auto num = t_m(3.1415926535897932384626433832795);
   auto den = t_m(2.0);
   EXPECT_DOUBLE_EQ(1.0, SOU::math::sin(num / den));
}

TEST(MathFunc, Cosine)
{
   auto num = t_m(3.1415926535897932384626433832795);
   auto den = t_m(0.5);
   EXPECT_DOUBLE_EQ(1.0, SOU::math::cos(num / den));
}

TEST(MathFunc, Tangent)
{
   auto num = t_m(3.1415926535897932384626433832795);
   auto den = t_m(0.5);
   EXPECT_NEAR(0.0, SOU::math::tan(num / den), 0.000000000000001);
}

/**
   Test is to see if dB is produced correctly.
*/
TEST(MathFunc, TestWithlog)
{
   t_sec T1{ 80.0 };
   t_sec T2{ 8.0 };

   //auto val = log(T1);  // causes errors as expected.

   //static_assert(SOU::operators::is_zero_dimensions< decltype(T1 / T2) >::value);
   static_assert(decltype(T1 / T2)::isZeroDimensions());

   auto timeRatio = T1 / T2;

   double x = SOU::math::log(timeRatio);

   EXPECT_DOUBLE_EQ(2.3025850929940456840179914546844, x); // << "Test to see if a scalar value is produced";
   EXPECT_UNIT_EQ(10.00, T1 / T2);

   EXPECT_DOUBLE_EQ(2.3025850929940456840179914546844, SOU::math::log(T1 / T2));
}

