#include "operators.h"
#include "SI.h"
#include "MetricTypes.h"
#include "TimeAtomicUnits.h"  // contains the time atomic units
#include "WhatAmI.h"
#include "Make_Squared.h"
#include "ExpectUnitTest.h"
#include <gtest/gtest.h>
#include <memory>

//namespace AT = Metric::AtomicUnit;
// basic test on the multiplication operator
struct DivisionFirst : public ::testing::Test
{
   typedef Metric::AtomicUnit::Meter Meter;
   typedef AT::second second;
   typedef Metric::AtomicUnit::gram gram;
   typedef Metric::AtomicUnit::ampere coul;
   typedef Metric::AtomicUnit::kelvin kelvin;
   typedef SOU::MakeType<Meter, second, gram, kelvin, coul> tMake;
   typedef tMake::MakeDim<1, 0, 0, 0, 0>::type t_Meter;
   typedef tMake::MakeDim<2, 0, 0, 0, 0>::type t_MeterSq;
   typedef tMake::MakeDim<3, 0, 0, 0, 0>::type t_MeterCubed;
};

TEST_F(DivisionFirst, NoUnit) {
   SOU::tNoUnit myScaler{ 9.0 };
   Metric::t_meter Meter{ 27.0 };
   auto val = Meter / myScaler;
   EXPECT_UNIT_EQ(val, 3.00);
   EXPECT_EQ("[L]", SOU::Diminsion(val)) << "Added as another check later on";
}
TEST_F(DivisionFirst, InverseNoUnit) {
   SOU::tNoUnit myScaler{ 27.0 };
   Metric::t_meter const Meter{ 9.0 };
   auto val = myScaler / Meter;
   EXPECT_EQ("1/[L]", SOU::Diminsion(val)) << "Added as another check later on";
   EXPECT_UNIT_EQ(val, 3.00);
}
TEST_F(DivisionFirst, InverseDouble){
   double myScaler = 90.0;
   Metric::t_meter const Meter{ 9.0 };
   const auto val = myScaler / Meter;
   EXPECT_UNIT_EQ(val, 10.0);
}
TEST_F(DivisionFirst, InverstInt) {
   int myScaler = 81;
   const t_MeterCubed M3{ 9.0 };
   auto const val = myScaler / M3;
   EXPECT_UNIT_EQ(val, 9.0);
   EXPECT_UNIT_EQ(9.0, 81 / M3);
}

TEST_F(DivisionFirst, Constexpr) {
   constexpr t_Meter m1{ 4.0 };
   constexpr t_MeterSq mSq{ 32.0 };
   constexpr auto M = mSq / m1;
   EXPECT_EQ("[L]", SOU::Diminsion(M));
   EXPECT_UNIT_EQ(M, 8.0);
}

TEST_F(DivisionFirst, Constexpr_scaler) {
   constexpr t_Meter m1{ 36.0 };
   constexpr auto m = m1 / 9;
   EXPECT_UNIT_EQ(m, 4.0);
   EXPECT_EQ("[L]", SOU::Diminsion(m));
}

/// Test division during assignement
TEST_F(DivisionFirst, TestDiv_Result)
{
   // division during intialization
   t_Meter m(t_MeterSq(1.0) / t_Meter(1.0));
   EXPECT_UNIT_EQ(m, 1.0);

   t_Meter m2 = t_MeterSq(1.0) / t_Meter(2.0);
   EXPECT_UNIT_EQ(m2, 0.5);

   auto m3 = t_MeterSq(1.0) / t_Meter(4.0);
   EXPECT_EQ("[L]", SOU::Diminsion(m3));
   EXPECT_UNIT_EQ(m3, 0.25);
}

/// Test with cube
TEST_F(DivisionFirst, TestWithCube)
{
   t_MeterSq sq1 = t_MeterCubed(9.0) / t_Meter(2.0);
   EXPECT_UNIT_EQ(sq1, 4.5);

   t_Meter m1 = t_MeterCubed(15.0) / t_MeterSq(5.0);
   EXPECT_UNIT_EQ(m1, 3.0);

   t_Meter m2 = t_MeterSq(4.0) / t_Meter(2.0);
   EXPECT_UNIT_EQ(m2, 2.0);

   auto m3 = t_MeterCubed(15.0) / t_MeterSq(3.0); // test with auto
   EXPECT_UNIT_EQ(m3, 5.0);
   EXPECT_EQ("[L]", SOU::Diminsion(m3));
}

/// @code The SystemOfUnits::operators::Div_Result<T1,T2> @endcode must be able to handle chaining
/// of division.
TEST_F(DivisionFirst, TestChaining)
{
   t_Meter m1 = t_Meter(2.0) * t_Meter(2.0) / t_Meter(2.0);
   EXPECT_UNIT_EQ(m1, 2.0);

   t_Meter m2 = t_MeterCubed(27.0) / t_Meter(3.0) / t_Meter(3.0);
   EXPECT_UNIT_EQ(m2, 3.0);

   m2 = t_MeterCubed(27.0) / t_Meter(3.0) / t_Meter(3.0) / 2;
   EXPECT_DOUBLE_EQ(1.5, m2.amount()) << "test with operator=()";

   t_Meter m3 = (t_Meter(2.0) * t_Meter(9.0)) / t_Meter(3.0);
   EXPECT_UNIT_EQ(m3, 6.0);

   t_Meter const m4 = 2 * (t_Meter(2.0) * t_Meter(9.0)) / t_Meter(3.0);
   EXPECT_UNIT_EQ(12.0, m4 );

   auto const m5 = (2 * t_Meter(2.0) * t_Meter(9.0)) / t_Meter(3.0);
   EXPECT_UNIT_EQ(12.0, m5 );
   EXPECT_EQ("[L]", SOU::Diminsion(m5));
}

/// Test that the result can be diminsionless such as Mach or dB.
TEST_F(DivisionFirst, TestDimisionLess)
{
   // see how well a diminsonless unit is handled
   auto d1 = t_MeterSq(12.0) / t_MeterSq(4.0);
   EXPECT_TRUE(d1 == 3.0);

   auto const d2 = t_Meter(11.0) / t_Meter(11.0);
   EXPECT_UNIT_EQ(1.0, d2);

   auto d3 = t_MeterCubed(24.0) / t_MeterCubed(12.0);
   EXPECT_UNIT_EQ(2.0, d3);
   EXPECT_EQ("", SOU::Diminsion(d3)) << "Caused a compile time failure";
}

TEST_F(DivisionFirst, DimensionLessDenom) {
   auto const res = t_MeterSq(12.0) / 4.0;
   EXPECT_DOUBLE_EQ(3.0, res.amount()) << SOU::WhatAmI(res);
   ASSERT_EQ(SOU::Diminsion(res), std::string("[L]^2"));
}

TEST_F(DivisionFirst, DimensionlessNum) {
   auto res = 36.0 / t_MeterSq(12.0);
   EXPECT_UNIT_EQ(3.0, res );
   ASSERT_EQ(SOU::Diminsion(res), std::string("1/[L]^2"));
}

/** Test with non-atomic values.  When dividing meters by centimeters. */
TEST_F(DivisionFirst, TestWithNonAtomicUnitUnitsLength)
{
   using namespace Metric;
   const t_centimeter cent(200.0);
   t_Meter meter{ 7.0 };
   t_MeterSq meterSq(14.0);

   typedef SOU::operators::Div_Result<t_MeterSq, t_centimeter> t_result;
   EXPECT_TRUE(static_cast<bool>(t_result::ALLTYPES_THE_SAME::val) == true);

   meter = meterSq / cent;
   EXPECT_UNIT_EQ(7.0, meter );

   typedef SOU::MakeSQ< Metric::t_centimeter >::type t_centSq;
   t_centSq centSq = t_centimeter(600) * meter;
   t_centimeter cent2 = centSq / meter;
   EXPECT_UNIT_EQ(600.0, cent2 );

   typedef SOU::MakeSQ< Metric::t_kilometer >::type t_kiloSQ;
   Metric::t_kilometer kilo = t_kiloSQ(12.0) / cent2;
   EXPECT_UNIT_EQ(2000.0, kilo );
}

template< int NUMERATOR, int DENOMINATOR, int RATIO > struct ARG {
   enum {
      eN = NUMERATOR, eD = DENOMINATOR, eR = RATIO
   };
};


// template used to make many division tests
//template< int RESULT, int DIV1, int DIV2 >
template< typename T_ARG >
class SOU_Division : public testing::Test //: public CppUnit::TestFixture
{
protected:
	enum { eNUM = T_ARG::eN, eDEN = T_ARG::eD, eRATIO = T_ARG::eR };
	// define the basic types that will be used here.
	typedef Metric::AtomicUnit::Meter Meter;
	typedef Metric::AtomicUnit::second second;
	typedef Metric::AtomicUnit::gram gram;
	typedef Metric::AtomicUnit::ampere coul;
	typedef Metric::AtomicUnit::kelvin kelvin;

	// build a type from the basics
	typedef SOU::MakeType<Meter, second, gram, kelvin, coul> tMake;

	// Produce the actual Unit.
	typename typedef tMake::MakeDim< eNUM, 0, 0, 0, 0 >::type t_1;
	typename typedef tMake::MakeDim< eDEN, 0, 0, 0, 0 >::type t_2;
	typename typedef tMake::MakeDim< eRATIO, 0, 0, 0, 0 >::type t_3;
	typename typedef tMake::MakeDim<-eRATIO, 0, 0, 0, 0 >::type t_inv;

	// attributes used in the class
	void SetUp()
	{
		m_1 = std::make_unique<t_1>(12.0); // (3.0);
		m_2 = std::make_unique<t_2>(4.0);
		m_3 = std::make_unique<t_3>(3.0); // (12.0);
	}

	std::unique_ptr<t_1> m_1; /// Argument one
	std::unique_ptr<t_2> m_2;  /// Argument two
	std::unique_ptr<t_3> m_3; /// The product of the two arguments
private:
};

TYPED_TEST_SUITE_P(SOU_Division);

/** Early test to show how @code SOU::operators::Div_Result< T1, T2 >
@endcode worked
  */
TYPED_TEST_P(SOU_Division, TestDiv_Result)
{
	using TAG = SOU_Division<TypeParam >;

	SOU::operators::Div_Result< TAG::t_1, TAG::t_2 > res(*TAG::m_1, *TAG::m_2);
   EXPECT_UNIT_EQ(res.result(), *TAG::m_3 );
}

/// early test show that a simple division could work.
TYPED_TEST_P(SOU_Division, Test2)
{
	using TAG = SOU_Division<TypeParam >;

	auto /*TAG::t_3*/ res = *TAG::m_1 / *TAG::m_2;
   EXPECT_UNIT_EQ(res, *TAG::m_3);
	//EXPECT_DOUBLE_EQ( res.amount(), *TAG::m_3.amount() ) << "need to write an comparison for episoln";
   EXPECT_UNIT_EQ(*TAG::m_3, *TAG::m_1 / *TAG::m_2);

	auto res2 = *TAG::m_1 / *TAG::m_3;
   EXPECT_UNIT_EQ(res2, *TAG::m_2);
}

/// Did operator/() work with scalar values?
TYPED_TEST_P(SOU_Division, TestWithScaler)
{
	using TAG = SOU_Division<TypeParam >;
	EXPECT_DOUBLE_EQ(12.0, TAG::m_1->amount()) << "Verify we are starting correctly";

   typename TAG::t_1 const res = *TAG::m_1 / 4.0;
	EXPECT_DOUBLE_EQ(3.0, res.amount()) << SOU::WhatAmI(res);

	auto res1 = 36.0 / (*TAG::m_3);
   // TODO: Correct this, compile error in gtest.h 
   //auto ans = res1.amount();
	//ASSERT_TRUE(res1.amount() == 12.0 ) << SOU::WhatAmI(res1);
   EXPECT_UNIT_EQ(res1, 12.0);
   //std::cout << SOU::WhatAmI(res1) << '\n';
}

TYPED_TEST_P(SOU_Division, TestDivideAssign)
{
	using TAG = SOU_Division<TypeParam >;
	EXPECT_DOUBLE_EQ(12.0, TAG::m_1->amount() ) << "Verify we are starting correctly";

	*TAG::m_1 /= 2.0;
	EXPECT_DOUBLE_EQ(6.0, TAG::m_1->amount()) << "12/2 is 6";

	*TAG::m_1 /= 0.1;
   EXPECT_UNIT_EQ(60.0, *TAG::m_1 );
}

REGISTER_TYPED_TEST_SUITE_P(SOU_Division,
	TestDiv_Result, Test2, TestWithScaler, TestDivideAssign);

typedef ::testing::Types< ARG<2, 1, 1>, ARG< 3, 2, 1>, ARG<5, 2, 3>, ARG<2, 2, 0>, ARG<2, 0, 2>, ARG<2, 4, -2> > MyTypes;
INSTANTIATE_TYPED_TEST_SUITE_P(My, SOU_Division, MyTypes);

// Copyright © 2005-2020 "Curt" Leslie L. Martin, All rights reserved.
// curt.leslie.lewis.martin@gmail.com
//
// Permission to use, copy, modify, and distribute this software for any
// purpose is hereby granted without fee, provided that this copyright and
// permissions notice appear in all copies and derivatives.
//
// This software is provided "as is" without express or implied warranty.
