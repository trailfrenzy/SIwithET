// File contains the basic unit tests for SI.h
#include "SI.h"
#include "MetricTypes.h"
#include "template_help.h"
#include "ExpectUnitTest.h"
#include "Make_Squared.h"
#include <gtest/gtest.h>
#include <type_traits>
#include <sstream>
#include <string>
#include <memory>
#include <type_traits>

template< typename UNIT_TYPE >
class SITest : public testing::Test
{
protected:
	using p_type = std::unique_ptr<UNIT_TYPE>;
	p_type m_1;
	p_type m_2;
	p_type m_3;
	p_type m_4;

	using t_type = typename UNIT_TYPE;

	void SetUp()
	{
		m_1 = std::make_unique<t_type>(8.0);
		m_2 = std::make_unique<t_type>(5.0);
		m_3 = std::make_unique<t_type>(3.0);
		m_4 = std::make_unique<t_type>(4.0);
	}
};

TYPED_TEST_SUITE_P(SITest);

/// All types should be the same as a double
/// Size is needed to show that unitType<> is the same size as a double
TYPED_TEST_P(SITest, SizeOf)
{
	using TAG = SITest<TypeParam >;
	static_assert(sizeof(double) == sizeof(TAG::t_type), "was not 64 bit");
   static_assert(sizeof(double) == sizeof(long double), "if fail you are no longer on a long double is 64bit");
}

TYPED_TEST_P(SITest, Comparison)
{
	using TAG = SITest<TypeParam >;
	*TAG::m_1 = TAG::t_type(4.5);
	*TAG::m_2 = TAG::t_type(4.5);

	EXPECT_TRUE(*TAG::m_1 == *TAG::m_2);
	EXPECT_TRUE(TAG::m_1->amount() == 4.5);

	// testing with one side double the other side unitType
	EXPECT_TRUE(*TAG::m_1 == 4.5)  << "Use to have three different comparison operators, now only one";
   auto b = TAG::t_type( 4.5 ) == *TAG::m_1;
   EXPECT_TRUE(b);
}

TYPED_TEST_P(SITest, NotEqual)
{
	using TAG = SITest<TypeParam >;
	EXPECT_TRUE(*TAG::m_1 != *TAG::m_2);
   EXPECT_TRUE(TAG::t_type( 4.5 ) != *TAG::m_2) << "Use to have three types now only have one";
   EXPECT_TRUE(*TAG::m_2 != TAG::t_type( 4.5 ));
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
   EXPECT_TRUE(TAG::t_type( 3.0 ) <= *TAG::m_3);
}

TYPED_TEST_P(SITest, Assignment)
{
	using TAG = SITest<TypeParam >;
	*TAG::m_1 = TAG::t_type(68.9);
	EXPECT_TRUE(*TAG::m_1 == 68.9);

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
   using TAG = SITest<TypeParam>;
   constexpr TAG::t_type a{ 2 };
   constexpr TAG::t_type b{ 3.0 };
   constexpr auto c = a + b;
   ASSERT_DOUBLE_EQ(c.amount(), 5.0);
}
TYPED_TEST_P(SITest, Subtraction_constexp) {
   using TAG = SITest<TypeParam>;
   constexpr TAG::t_type a{ 12 };
   constexpr TAG::t_type b{ 5.0 };
   constexpr auto c = a - b;
   ASSERT_DOUBLE_EQ(c.amount(), 7.0);
}
TYPED_TEST_P(SITest, AdditionAssignment)
{
	using TAG = SITest<TypeParam>;
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

   typename TAG::t_type u1(12.0);
   typename TAG::t_type u2(6.0);
	EXPECT_TRUE(u2 + u2 + u2 + u2 - u1 == u1);
	EXPECT_TRUE(u2 + u2 + u2 + u2 - u1 - u2 == u1 - u2);
	EXPECT_TRUE(TAG::t_type(2.0) + TAG::t_type(3.0) == TAG::t_type(5.0));
}

TYPED_TEST_P(SITest, DestructorNoThrow) {
   using TAG = SITest<TypeParam >;
   static_assert(std::is_destructible< TAG::t_type >::value);
   static_assert(std::is_nothrow_destructible< TAG::t_type >::value);
}

TYPED_TEST_P(SITest, IsMovable) {
   using TAG = SITest<TypeParam>;
   static_assert(std::is_move_assignable_v<TAG::t_type>);
   static_assert(std::is_move_constructible<TAG::t_type>::value);
}

TYPED_TEST_P(SITest, IsCopyable) {
   // typename using TAG = SITest<TypeParam >::t_type;  TODO why dose this not work?
   using TAG = SITest<TypeParam>;
   static_assert( (std::is_assignable<TAG::t_type, TAG::t_type >::value) );

   static_assert(std::is_copy_assignable<TAG::t_type>::value);
   static_assert(std::is_trivially_copy_assignable<TAG::t_type>::value);
}

TYPED_TEST_P(SITest, IsConstructible) 
{
   using TAG = SITest<TypeParam>;
   static_assert(std::is_constructible<TAG::t_type>::value );
   static_assert( (std::is_constructible<TAG::t_type, long double >::value));
   static_assert(std::is_copy_constructible<TAG::t_type>::value);
   static_assert((std::is_trivially_copy_constructible<TAG::t_type>::value));
   static_assert((std::is_nothrow_copy_constructible<TAG::t_type>::value));
}

TYPED_TEST_P(SITest, isUnitType) {
   using TAG = SITest<TypeParam>;
   static_assert( SOU::is_UnitType<TAG::t_type>::value );
   static_assert(!SOU::is_UnitType<TAG>::value);
   static_assert(!SOU::is_UnitType<double>::value);
   static_assert(!SOU::is_UnitType<unsigned>::value);
}


REGISTER_TYPED_TEST_SUITE_P(SITest
	, SizeOf, Assignment, NotEqual, LessThan, LessThanEqual, GreaterThan, GreaterThanEqual, Comparison, Addition, Addition_constexp, AdditionAssignment, Subtraction, Subtraction_constexp, SubtractionAssignment, Chaining, DestructorNoThrow, IsMovable, IsCopyable, IsConstructible, isUnitType);

TEST(SITestSQ, Squaring)
{
	namespace AT = Metric::AtomicUnit;
	using namespace Metric::AtomicUnit;
	typedef SOU::unitType< Meter, 0, AT::second, -1, gram, 1, SOU::NoDim, 0, SOU::NoDim > t_gramPsec;
	typedef SOU::unitType< Meter, 0, AT::second, -2, gram, 2, SOU::NoDim, 0, SOU::NoDim > t_gramPsecSQ;

	typedef SOU::MakeSQ<t_gramPsec>::type gramSQ;

	enum { b = std::is_same< gramSQ, t_gramPsecSQ >::value };
	static_assert(b);
}

TEST(BasicSI, Size) {
	static_assert(sizeof(double) == sizeof(SOU::tNoUnit), "should be the same");
}

typedef Metric::AtomicUnit::Meter Meter;
typedef Metric::AtomicUnit::second second;
typedef Metric::AtomicUnit::gram gram;
typedef SOU::MakeType< Meter, second, Metric::AtomicUnit::kilogram, Metric::AtomicUnit::kelvin, Metric::AtomicUnit::ampere > t_Base;
//typedef SI::unitType< Meter, 1, second, 0, gram, 0 > t_Meter;
typedef t_Base::MakeDim<1,0,0,0,0>::type t_Meter;
typedef t_Base::MakeDim<2,0,0,0,0>::type t_MeterSq;
typedef t_Base::MakeDim<3,0,0,0,0>::type t_MeterCubed;

typedef ::testing::Types< Metric::t_meter, Metric::t_metersecond, Metric::t_second, Metric::t_velocity, Metric::t_gramPsec, t_MeterSq, t_MeterCubed > MyTypes;
INSTANTIATE_TYPED_TEST_SUITE_P(My, SITest, MyTypes);

TEST( BasicSI, NoUnitValueZero ) {
   SOU::tNoUnit val( 0.0 );
   EXPECT_EQ( val.amount(), 0.0);
}

TEST(BasicSI, NoUnitValue) {
   SOU::tNoUnit val(6.0);
   EXPECT_EQ(val.amount(), 6.0);
}

TEST(BasicSI, Mult_float)
{
   t_Meter km = 3.0 * t_Meter(1.0);
   EXPECT_UNIT_EQ(km, 3.0);

   km = t_Meter(3.0) * 5.0;
   EXPECT_UNIT_EQ(km, 15.0);
}

TEST(BasicSI, Div_float)
{
   auto m = 9.0 / t_Meter(3.0);
   EXPECT_UNIT_EQ(m, 3.0);

   auto n = t_Meter(30.0) / 3.0;
   EXPECT_UNIT_EQ(n, 10.0);

   static_assert(std::is_same< decltype(n), t_Meter >::value, "using the built in operator/() not in operator.h");
}

//TEST(BasicSI, NULL_Value) {
//   t_Meter M;
//   M /= 2.0;
//
//   t_Meter M2(4.5);
//   M += M2;
//   M2 += M;
//
//   double t = 0.0 / 0.0;
//   //EXPECT_LT(0.0, M.amount());
//}


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

TEST(BasicSI, IsTrivial)
{
   static_assert(std::is_trivial<t_MeterSq>::value);
   static_assert(std::is_trivially_constructible<t_MeterSq>::value);
   static_assert(std::is_trivially_copy_constructible<t_MeterSq>::value);
   static_assert(std::is_trivially_copy_assignable<t_MeterSq>::value);
   static_assert(std::is_trivially_copyable<t_MeterSq>::value);
   static_assert(std::is_trivially_move_assignable<t_MeterSq>::value);
   static_assert(std::is_nothrow_copy_assignable<t_MeterSq>::value);
}

TEST(BasicSI, IsFloat)
{
   static_assert(!std::is_floating_point<t_MeterSq>::value,
   "Despite acting like a floating point type UnitType is not a floating point type. The question, do we want it be a floating point type by overloading std::is_floating_point<>? The author says no, but is open to the idea.");
}

TEST(BasicSI, IsAssignable)
{
   static_assert((std::is_assignable< t_MeterSq&, t_MeterSq >::value));
   static_assert((!std::is_assignable< t_MeterSq&, long double >::value, "do not allow an existing value to reassign"));
   static_assert((!std::is_assignable< t_MeterSq&, double >::value), "do not allow an existing value to reassign");
   static_assert((!std::is_assignable< t_MeterSq&, float >::value), "do not allow an existing value to reassign");
   static_assert((!std::is_assignable< t_MeterSq&, int >::value), "do not allow an existing value to reassign") ;
   static_assert((!std::is_assignable< t_MeterSq&, t_Meter >::value), "do not assign one type to another");

   static_assert(std::is_trivially_assignable< t_MeterSq&, t_MeterSq>::value);
   static_assert(!(std::is_trivially_assignable< t_MeterSq&, double>::value));
}

TEST(BasicSI, IsNothrowAssignable)
{
   static_assert(std::is_nothrow_assignable< t_MeterSq, t_MeterSq>::value);
}

TEST(BasicSI, IsConstructable) 
{
   static_assert(std::is_default_constructible<t_MeterSq>::value);
   static_assert(std::is_nothrow_default_constructible<t_Meter>::value);
   static_assert(std::is_constructible<t_MeterSq >::value);
   static_assert(std::is_nothrow_constructible<t_MeterCubed>::value);
}

TEST(BasicSI, IsCopyConstructible) {
   static_assert(std::is_copy_constructible<t_MeterSq>::value);
   static_assert(std::is_nothrow_copy_constructible<t_MeterSq>::value);
}

TEST(BasicSI, IsMovable) {
   static_assert(std::is_move_constructible<t_MeterSq>::value);
   static_assert(std::is_nothrow_move_constructible<t_MeterSq>::value);
}

TEST(BasicSI, IsPoly) {
   static_assert(!std::is_polymorphic<t_MeterSq>::value);
}
TEST(BasicSI, IsClass) {
   static_assert(std::is_class<t_MeterSq>::value);
}
TEST(BasicSI, IsPOD) {
   static_assert(std::is_standard_layout<t_Meter>::value, "Ensure default constructor is default");
   static_assert(std::is_standard_layout<t_MeterSq>::value);
   static_assert(std::is_standard_layout<t_Meter::Length>::value);
   static_assert(std::is_standard_layout<t_Meter::Mass>::value);
   static_assert(std::is_standard_layout<t_Meter::Time>::value);
   static_assert(std::is_standard_layout<t_Meter::Temperature>::value);
   static_assert(std::is_standard_layout<t_Meter::Charge>::value);
}

static constexpr char const name[] = "Watt";
using Watt = Metric::AUMetric::MakeDim<2, -3, 1, 0, 0>::type;
using t_nameWatt = SystemOfUnits::CoherentUnit<Watt, name >;

TEST(BasicSI, IsSIwithDim)
{
   EXPECT_FALSE(SystemOfUnits::is_CoherentUnit<double>::value);
   static_assert(!SystemOfUnits::is_CoherentUnit<t_Base>::value, "t_Base is UnitType not a CoherentUnit");

   static_assert(SystemOfUnits::is_CoherentUnit< t_nameWatt>::value);
}


TEST(Exception, T_Symbols) {
   static_assert(noexcept(SOU::ElectricCurrent() ));
   static_assert(noexcept(SOU::Length() ));
   static_assert(noexcept(SOU::Mass() ));
   static_assert(noexcept(SOU::Temperature()));
}

TEST(Exception, Basic){
   static_assert( noexcept( Metric::AtomicUnit::Meter()));
   static_assert(noexcept(Metric::AtomicUnit::Centimeter()));
   static_assert(noexcept(Metric::AtomicUnit::ampere()));
   static_assert(noexcept(Metric::AtomicUnit::gram()));
   static_assert(noexcept(Metric::AtomicUnit::kelvin()));
   static_assert(noexcept(Metric::AtomicUnit::kilogram()));
   static_assert(noexcept(Metric::AtomicUnit::Kilometer()));
   static_assert(noexcept(Metric::AtomicUnit::miligram()));
}

TEST(Exception, Units){
   static_assert(noexcept(Metric::t_centimeter()));
   static_assert(noexcept(Metric::t_gram()));
   static_assert(noexcept(Metric::t_gramPsec()));
   static_assert(noexcept(Metric::t_hour()));
   static_assert(noexcept(Metric::t_kilogram()));
   static_assert(noexcept(Metric::t_kilometer()));
   static_assert(noexcept(Metric::t_meter()));
   static_assert(noexcept(Metric::t_metersecond()));

}

TEST(Exception, DimTypes)
{
   static_assert(noexcept( t_Meter::Length()) );
   static_assert(noexcept( t_Meter::Mass()) );
   static_assert(noexcept( t_Meter::Time()));
   static_assert(noexcept(t_Meter::Temperature()));
   static_assert(noexcept(t_Meter::Charge()));
}

TEST(BasicSI, Concepts_CompileError )
{
   namespace AT = Metric::AtomicUnit;
   using namespace Metric::AtomicUnit;

   // supposed to cause a compile error here!  Concept is not implimented correctly if compiles.
   /*
   typedef SOU::unitType< Meter, 0, AT::second, -1, Meter, 1, SOU::NoDim, 0, SOU::NoDim > t_gramPsec;
   */
   //t_gramPsec gramO{ 4.0 };

   typedef SOU::unitType< Meter, 0, AT::second, -2, gram, 2, SOU::NoDim, 0, SOU::NoDim > t_gramPsecSQ;

}

// Copyright © 2005-2020 "Curt" Leslie L. Martin, All rights reserved.
// curt.leslie.lewis.martin@gmail.com
//
// Permission to use, copy, modify, and distribute this software for any
// purpose is hereby granted without fee, provided that this copyright and
// permissions notice appear in all copies and derivatives.
//
// This software is provided "as is" without express or implied warranty.
