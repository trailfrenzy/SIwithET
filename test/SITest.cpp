#include "SI.h"
#include <gtest/gtest.h>
#include <type_traits>
//#include <iostream>
#include <sstream>
#include <string>
#include <memory>
#include "MetricTypes.h"
#include "template_help.h"

template< class UNIT_TYPE >
class SITest : public testing::Test
{
protected:
	using p_type = std::unique_ptr<UNIT_TYPE>;
	p_type m_1;
	p_type m_2;
	p_type m_3;
	p_type m_4;

	using t_type = UNIT_TYPE;
	void SetUp()
	{
		m_1 = std::make_unique<t_type>(8.0);
		m_2 = std::make_unique<t_type>(5.0);
		m_3 = std::make_unique<t_type>(3.0);
		m_4 = std::make_unique<t_type>(4.0);
	}
};

TYPED_TEST_CASE_P(SITest);

/// All types should be the same as a double
/// Size is needed to show that unitType<> is the same size as a double
TYPED_TEST_P(SITest, SizeOf)
{
	using TAG = SITest<TypeParam >;
	EXPECT_TRUE(sizeof(double) == sizeof(TAG::t_type)) << "was not 64 bit";
}

//#define ASSERT_UNITTYPE_EQ(val1, val2)\
//  ASSERT_PRED_FORMAT2(::testing::internal::CmpHelperFloatingPointEQ<decltype(val1)>, \
//                      val1, val2)
//   ASSERT_UNITTYPE_EQ(TAG::t_type(4.5), *TAG::m_1);

TYPED_TEST_P(SITest, Comparison)
{
	using TAG = SITest<TypeParam >;
	//using namespace SI;
	*TAG::m_1 = TAG::t_type(4.5);
	*TAG::m_2 = TAG::t_type(4.5);

	EXPECT_TRUE(*TAG::m_1 == *TAG::m_2);
	EXPECT_TRUE(TAG::m_1->amount() == 4.5);

	// testing with one side double the other side unitType
	EXPECT_TRUE(*TAG::m_1 == 4.5)  << "Use to have three different comparison operators, now only one";
   EXPECT_TRUE(TAG::t_type{ 4.5 } == *TAG::m_1);
}

TYPED_TEST_P(SITest, NotEqual)
{
	using TAG = SITest<TypeParam >;
	EXPECT_TRUE(*TAG::m_1 != *TAG::m_2);
   EXPECT_TRUE(TAG::t_type{ 4.5 } != *TAG::m_2) << "Use to have three types now only have one";
   EXPECT_TRUE(*TAG::m_2 != TAG::t_type{ 4.5 });
}

TYPED_TEST_P(SITest, LessThan)
{
	using TAG = SITest<TypeParam >;
	*TAG::m_1 = TAG::t_type(4.55555);
	*TAG::m_2 = TAG::t_type(4.55556);
	EXPECT_TRUE(*TAG::m_1 < *TAG::m_2);
	EXPECT_TRUE(*TAG::m_3 < *TAG::m_4);
   EXPECT_TRUE(*TAG::m_3 < TAG::t_type(20) ) << "uses the constructor to convert the 20 to a UnitType";
   EXPECT_TRUE(TAG::t_type(1) < *TAG::m_3);
}

TYPED_TEST_P(SITest, GreaterThan)
{
	using TAG = SITest<TypeParam >;
	EXPECT_TRUE(*TAG::m_4 > *TAG::m_3);
   EXPECT_TRUE(TAG::t_type(20) > *TAG::m_3);
}

TYPED_TEST_P(SITest, GreaterThanEqual )
{
   using TAG = SITest<TypeParam >;
   EXPECT_TRUE(*TAG::m_4 >= *TAG::m_3);
   EXPECT_TRUE(TAG::t_type(20) >= *TAG::m_3);
   EXPECT_TRUE(TAG::t_type(3.0) >= *TAG::m_3);
}

TYPED_TEST_P(SITest, LessThanEqual )
{
   using TAG = SITest<TypeParam >;
   *TAG::m_1 = TAG::t_type(4.55555);
   *TAG::m_2 = TAG::t_type(4.55556);
   EXPECT_TRUE(*TAG::m_1 <= *TAG::m_2);
   EXPECT_TRUE(*TAG::m_3 <= *TAG::m_4);
   EXPECT_TRUE(*TAG::m_3 <= TAG::t_type(20) ) << "uses the constructor to convert the 20 to a UnitType";
   EXPECT_TRUE(TAG::t_type(1) <= *TAG::m_3);
   EXPECT_TRUE(TAG::t_type{ 3.0 } <= *TAG::m_3);
}

TYPED_TEST_P(SITest, Assignment)
{
	using TAG = SITest<TypeParam >;
	*TAG::m_1 = TAG::t_type(68.9);
	EXPECT_TRUE(*TAG::m_1 == 68.9) << "operator=(double) is no longer availible";

	*TAG::m_2 = *TAG::m_1;
	EXPECT_TRUE(*TAG::m_2 == 68.9);

	*TAG::m_2 = TAG::t_type(4.5);
	EXPECT_TRUE(*TAG::m_2 == 4.5);
}

TYPED_TEST_P(SITest, Addition)
{
	using TAG = SITest<TypeParam >;
	EXPECT_TRUE(*TAG::m_1 == *TAG::m_2 + *TAG::m_3);
	EXPECT_TRUE(*TAG::m_1 == *TAG::m_3 + *TAG::m_2);
	EXPECT_TRUE(*TAG::m_1 == *TAG::m_4 + *TAG::m_4);
	//CPPUNIT_ASSERT_DOUBLES_EQUAL( *m_1, *m_4 + *m_4, 0.00000001 ); 
}
TYPED_TEST_P(SITest, Addition_constexp) {
   using TAG = SITest<TypeParam >;
   using t_type = TAG::t_type;
   constexpr t_type a  { 2 };
   constexpr t_type b  { 3.0 };
   constexpr auto c = a + b;
   ASSERT_DOUBLE_EQ(c.amount(), 5.0);
}
TYPED_TEST_P(SITest, Subtraction_constexp) {
   using t_type = SITest<TypeParam >::t_type;
   constexpr t_type a{ 12 };
   constexpr t_type b{ 5.0 };
   constexpr auto c = a - b;
   ASSERT_DOUBLE_EQ(c.amount(), 7.0);
}
TYPED_TEST_P(SITest, AdditionAssignment)
{
	using TAG = SITest<TypeParam >;
	*TAG::m_2 += *TAG::m_3;
	EXPECT_TRUE(*TAG::m_1 == *TAG::m_2);
   *TAG::m_2 += TAG::t_type(3.0);
}
TYPED_TEST_P(SITest, Subtraction)
{
	using TAG = SITest<TypeParam >;
	EXPECT_TRUE(*TAG::m_1 - *TAG::m_2 == *TAG::m_3);
	EXPECT_TRUE(*TAG::m_3 == *TAG::m_1 - *TAG::m_2);
}
TYPED_TEST_P(SITest, SubtractionAssignment)
{
	using TAG = SITest<TypeParam >;
	*TAG::m_1 -= *TAG::m_2;
	EXPECT_TRUE(*TAG::m_1 == *TAG::m_3);
}
TYPED_TEST_P(SITest, Chaining)
{
	using TAG = SITest<TypeParam >;
	EXPECT_TRUE(*TAG::m_4 + *TAG::m_4 - *TAG::m_2 == *TAG::m_3);

	TAG::t_type u1(12.0);
	TAG::t_type u2(6.0);
	EXPECT_TRUE(u2 + u2 + u2 + u2 - u1 == u1);
	EXPECT_TRUE(u2 + u2 + u2 + u2 - u1 - u2 == u1 - u2);
	EXPECT_TRUE(TAG::t_type(2.0) + TAG::t_type(3.0) == TAG::t_type(5.0));
}

TYPED_TEST_P(SITest, DestructorNoThrow) {
   using TAG = SITest<TypeParam >;
   ASSERT_TRUE(std::is_destructible< TAG::t_type >::value);
   ASSERT_TRUE(std::is_nothrow_destructible< TAG::t_type >::value);
}

TYPED_TEST_P(SITest, IsMovable) {
   using TAG = SITest<TypeParam >::t_type;
   EXPECT_TRUE(std::is_move_assignable<TAG>::value);
   ASSERT_TRUE(std::is_move_constructible<TAG>::value);
}

TYPED_TEST_P(SITest, IsCopyable) {
   using TAG = SITest<TypeParam >::t_type;
   //EXPECT_TRUE( std::is_assignable<TAG&, TAG >::value );
   EXPECT_TRUE(std::is_copy_assignable<TAG>::value);
   EXPECT_TRUE(std::is_trivially_copy_assignable<TAG>::value);
}

TYPED_TEST_P(SITest, IsConstructible) 
{
   using TAG = SITest<TypeParam >::t_type;
   EXPECT_TRUE(std::is_constructible<TAG >::value );
   //EXPECT_TRUE( std::is_constructible<TAG, double >::value );
   EXPECT_TRUE(std::is_copy_constructible<TAG>::value);
   //EXPECT_TRUE(std::is_trivially_copy_constructible<TAG>::value);
   //EXPECT_TRUE(std::is_nothrow_copy_constructible<TAG>::value);
}

TYPED_TEST_P(SITest, isUnitType) {
   using TAG = SITest<TypeParam >::t_type;
   ASSERT_TRUE(SOU::is_UnitType<TAG>::value ) << "why is it wrong?";
   ASSERT_FALSE(SOU::is_UnitType<SITest<TypeParam >>::value);
   ASSERT_FALSE(SOU::is_UnitType<double>::value);
   ASSERT_FALSE(SOU::is_UnitType<unsigned>::value);
}


REGISTER_TYPED_TEST_CASE_P(SITest
	, SizeOf, Assignment, NotEqual, LessThan, LessThanEqual, GreaterThan, GreaterThanEqual, Comparison, Addition, Addition_constexp, AdditionAssignment, Subtraction, Subtraction_constexp, SubtractionAssignment, Chaining, DestructorNoThrow, IsMovable, IsCopyable, IsConstructible, isUnitType);

TEST(SITestSQ, Squaring)
{
	namespace AT = SOU::Time::AtomicUnit;
	using namespace Metric::AtomicUnit;
	typedef SOU::unitType< Meter, 0, AT::second, -1, gram, 1, SOU::NoDim, 0, SOU::NoDim > t_gramPsec;
	typedef SOU::unitType< Meter, 0, AT::second, -2, gram, 2, SOU::NoDim, 0, SOU::NoDim > t_gramPsecSQ;

	typedef SOU::MakeSQ<t_gramPsec>::type gramSQ;

	enum { b = SystemOfUnits::is_same< gramSQ, typename t_gramPsecSQ >::value };
	EXPECT_TRUE(b);

}

TEST(BasicSI, Size) {
	EXPECT_EQ(sizeof(double), sizeof(SOU::tNoUnit)) << "should be the same";
}

typedef Metric::AtomicUnit::Meter Meter;
typedef SOU::Time::AtomicUnit::second second;
typedef Metric::AtomicUnit::gram gram;
typedef SOU::MakeType< Meter, second, Metric::AtomicUnit::kilogram, Metric::AtomicUnit::kelvin, Metric::AtomicUnit::coulomb > t_Base;
//typedef SI::unitType< Meter, 1, second, 0, gram, 0 > t_Meter;
typedef t_Base::MakeDim<1,0,0,0,0>::type t_Meter;
typedef t_Base::MakeDim<2,0,0,0,0>::type t_MeterSq;
typedef t_Base::MakeDim<3,0,0,0,0>::type t_MeterCubed;

typedef ::testing::Types< Metric::t_meter, Metric::t_metersecond, Metric::t_second, Metric::t_velocity, Metric::t_gramPsec, t_MeterSq, t_MeterCubed > MyTypes;
INSTANTIATE_TYPED_TEST_CASE_P(My, SITest, MyTypes);

TEST( BasicSI, NoUnitValueZero ) {
   SOU::tNoUnit val( 0.0 );
   EXPECT_EQ( val.amount(), 0.0);
}

TEST(BasicSI, NoUnitValue) {
   SOU::tNoUnit val(6.0);
   EXPECT_EQ(val.amount(), 6.0);
}

TEST(BasicSI, Constexpr) {
   constexpr t_MeterSq const val(7.0);
   EXPECT_EQ(val.amount(), 7.0);
}

// TODO: change ASSERT_DOUBLE_EQ() to handle comparison of two different types.

TEST(BasicSI, InserterNoUnit) {
   SOU::tNoUnit val(9.78);
   std::stringstream strm;
   strm << val;
   EXPECT_EQ( strm.str(), std::string("9.78") );
}

TEST(BasicSI, IsConstructable) 
{
   EXPECT_TRUE(std::is_default_constructible<t_MeterSq>::value);
   EXPECT_TRUE(std::is_constructible<t_MeterSq >::value);
   //EXPECT_TRUE( std::is_constructible<t_MeterSq, t_MeterSq >::value );
   EXPECT_TRUE(std::is_copy_constructible<t_MeterSq>::value);
   //EXPECT_TRUE(std::is_trivially_copy_constructible<t_MeterSq>::value);
   //EXPECT_TRUE(std::is_nothrow_copy_constructible<t_MeterSq>::value);
}

TEST(BasicSI, IsPoly) {
   EXPECT_FALSE(std::is_polymorphic<t_MeterSq>::value);
}
TEST(BasicSI, IsClass) {
   EXPECT_TRUE(std::is_class<t_MeterSq>::value);
}
TEST(BasicSI, IsPOD) {
   EXPECT_FALSE(std::is_pod<t_Meter>::value) << "Why is this false?";
   EXPECT_TRUE(std::is_pod<t_Meter::Length>::value);
   EXPECT_TRUE(std::is_pod<t_Meter::Mass>::value);
   EXPECT_TRUE(std::is_pod<t_Meter::Time>::value);
   EXPECT_TRUE(std::is_pod<t_Meter::Tempeture>::value);
   EXPECT_TRUE(std::is_pod<t_Meter::Charge>::value);
}

// Copyright © 2005-2018 "Curt" Leslie L. Martin, All rights reserved.
// curt.leslie.lewis.martin@gmail.com
//
// Permission to use, copy, modify, and distribute this software for any
// purpose is hereby granted without fee, provided that this copyright and
// permissions notice appear in all copies and derivatives.
//
// This software is provided "as is" without express or implied warranty.
