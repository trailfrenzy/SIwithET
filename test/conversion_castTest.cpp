/* NOTE:
	The purpose of this file is to test and validate that the conversion_cast inside of
	file conversion_cast.h works correctly.

	Do to the way that CPPUnit can be used, the the hole class is inside the cpp file and
	no header is needed for the tester.  A header could be used but to keep the class simpler
	the whole test is placed inside the cpp.

	Think of the this file as a contract for what file conversion_cast.h has.
*/
#include "SI.h"
#include "operators.h" // needed for multiplications
#include "MetricTypes.h"
#include "conversion_cast.h"
#include "pow.h"
#include "Make_Squared.h"
#include "ExpectUnitTest.h"
#include <gtest\gtest.h>

class conversion_castTest : public ::testing::Test
{
protected:
   Metric::t_centimeter m_cent { 0.0 };
public:
	//void SetUp() { m_cent = Metric::t_centimeter(0.0); }
private:
};

/// Test how well compile time exponential power template works.
/// @see SI::helpers::P::thePower
/// @see Metric::AtomicUnit
TEST_F(conversion_castTest, TestPow)
{
   using namespace SOU::helpers;

   static_assert(1.0e+010 == P< Metric::AtomicUnit::Centimeter >::thePower<-5>::toBase() /*, 0.0001*/);
   static_assert(1.0e+008 == P< Metric::AtomicUnit::Centimeter >::thePower<-4>::toBase()/*, 0.0001*/);
   static_assert(1.0e+006 == P< Metric::AtomicUnit::Centimeter >::thePower<-3>::toBase()/*, 0.0001*/);
   static_assert(1.0e+004 == P< Metric::AtomicUnit::Centimeter >::thePower<-2>::toBase());
   static_assert(100.0 == P< Metric::AtomicUnit::Centimeter >::thePower<-1>::toBase());
   static_assert(1.0 == P< Metric::AtomicUnit::Centimeter >::thePower<0>::toBase());
   static_assert(0.01 == P< Metric::AtomicUnit::Centimeter >::thePower<1>::toBase());
   static_assert(0.0001 == P< Metric::AtomicUnit::Centimeter >::thePower<2>::toBase());
   EXPECT_DOUBLE_EQ(1.0e-006, P< Metric::AtomicUnit::Centimeter >::thePower<3>::toBase() /*, 0.000001*/);
   EXPECT_DOUBLE_EQ(1.0e-008, P< Metric::AtomicUnit::Centimeter >::thePower<4>::toBase() /*, 0.000001*/);
   EXPECT_DOUBLE_EQ(1.0e-010, P< Metric::AtomicUnit::Centimeter >::thePower<5>::toBase() /*, 0.000001*/);
   EXPECT_DOUBLE_EQ(1.0e-012, P< Metric::AtomicUnit::Centimeter >::thePower<6>::toBase() /*, 0.000001*/);

   static_assert(10000.0 == P< SOU::MakeFrom<Metric::AtomicUnit::Centimeter> >::thePower<2>::toBase());
}

TEST_F(conversion_castTest, MakeFrom)
{
   static_assert( 1.0 == SOU::MakeFrom< Metric::AtomicUnit::kilogram >::toBase() );
   static_assert(1000 == SOU::MakeFrom<Metric::AtomicUnit::gram>::toBase());

   double out = 2.0;

   using OUT = Metric::t_gram;
   using IN = Metric::t_kilogram;
   enum {eM = 1};

   //EXPECT_DOUBLE_EQ(SOU::MakeFrom<OUT::Mass>::toBase(), 1000);
   static_assert(SOU::MakeFrom<OUT::Mass>::toBase() == 1000);

   //out *=
   //   SOU::helpers::P< SOU::MakeFrom<OUT::Mass> >::thePower<eM>::toBase()
   //   * SOU::helpers::P< IN::Mass >::thePower<eM>::toBase();

   out *= SOU::MakeFrom<OUT::Mass>::toBase() *  IN::Mass::toBase();

   EXPECT_DOUBLE_EQ(out, 2000);
}

/// Test basic length conversions
TEST_F(conversion_castTest, TestLength)
{
   constexpr Metric::t_centimeter const cent(20.0);
   constexpr Metric::t_meter const meter = SOU::conversion_cast<Metric::t_meter>(cent);
   static_assert(0.20 == meter, "shows all conversion_cast<> took place at compile time" );
   EXPECT_UNIT_EQ(0.20, meter ) << "Why did it fail?";
   //EXPECT_EQ(0.20, meter.amount());
   //EXPECT_TRUE(0.20 == meter);

   m_cent = Metric::t_centimeter(200.0);
   Metric::t_kilometer kilo = SOU::conversion_cast<Metric::t_kilometer>(m_cent);
   EXPECT_UNIT_EQ(0.002, kilo );

   m_cent = SOU::conversion_cast<Metric::t_centimeter>(meter);
}

/// Test Lengths when squared
TEST_F(conversion_castTest, TestLengthSquared)
{
   typedef SOU::MakeSQ< Metric::t_meter >::type t_meterSq;
   typedef SOU::MakeSQ< Metric::t_centimeter >::type t_centSq;
   t_centSq cent2{ 10000.0 };

   t_meterSq m2 = SOU::conversion_cast<t_meterSq>(cent2);

   EXPECT_UNIT_EQ(1.0, m2 );
   EXPECT_UNIT_EQ(1.0, m2)
      << "works since the inside of EXPECT_DOUBLE_EQ expects both to be the same type";
   //EXPECT_DOUBLE_EQ( 1.0, m2 );
}

/// Test time conversions
TEST_F(conversion_castTest, TestTime)
{
   Metric::t_hour hr(2.0);
   Metric::t_minute min = SOU::conversion_cast<Metric::t_minute>(hr);
   EXPECT_UNIT_EQ(120.0, min );

   // hour to sec
   Metric::t_second sec = SOU::conversion_cast<Metric::t_second>(hr);
   EXPECT_UNIT_EQ(2.0*60.0*60.0, sec );

   // sec to hour
   sec = Metric::t_second(22.0) * 60.0 * 60.0;
   hr = SOU::conversion_cast<Metric::t_hour>(sec);
   EXPECT_UNIT_EQ(22.0, hr );
}

/// Test Time squared.  Also to see how well conversion_cast<> works with squared diminsions.
TEST_F(conversion_castTest, TestTimeSq)
{
   typedef SOU::MakeSQ<Metric::t_second>::type t_secSq;
   typedef SOU::MakeSQ<Metric::t_minute>::type t_minSq;

   t_minSq minSq{ 2.0 };
   t_secSq secSq = SOU::conversion_cast<t_secSq>(minSq);
   EXPECT_UNIT_EQ(7200.0, secSq );
}

/// Test the inverse time.
TEST_F(conversion_castTest, TestInverseTimeSq)
{
   typedef Metric::AUMetric::MakeDim<1, -2, 0, 0, 0>::type ACCinM;
   typedef SOU::UnitType
      < Metric::AtomicUnit::Kilometer, 1
      , Metric::AtomicUnit::second, -2
      , Metric::AtomicUnit::gram, 0
      , Metric::AtomicUnit::kelvin, 0
      , Metric::AtomicUnit::ampere, 0
      > ACCinKM;

   ACCinKM accKM1{ 2.0 };
   ACCinM  accM1 = SOU::conversion_cast<ACCinM>(accKM1);
   EXPECT_UNIT_EQ(2000.0, accM1 /*, 0.00001*/);

}

/// Test the Mass

TEST_F(conversion_castTest, Kilogram2gram)
{
   Metric::t_kilogram kg(1);

   auto g = SOU::conversion_cast<Metric::t_gram>(kg);
   EXPECT_UNIT_EQ(g, 1000.0);
}

TEST_F(conversion_castTest, TestMass)
{
   Metric::t_gram g(400.0);
   Metric::t_kilogram kg = SOU::conversion_cast<Metric::t_kilogram>(g);
   EXPECT_UNIT_EQ(0.4, kg);
}

/// Test Mass Squared
TEST_F(conversion_castTest, TestMassSq)
{
   typedef SOU::MakeSQ< Metric::t_gram >::type t_gramSq;
   typedef SOU::MakeSQ< Metric::t_kilogram >::type t_kiloSq;
   t_kiloSq kiloSq{ 1.0 };
   t_gramSq gramSq = SOU::conversion_cast<t_gramSq>(kiloSq);
   EXPECT_UNIT_EQ(1e6, gramSq );
}

/// Test where the dimensions are the wrong size for a conversion.  Test should be a failure.
TEST_F(conversion_castTest, TestWrongDim)
{
   using namespace SOU;
   namespace AU = Metric::AtomicUnit;

   typedef SOU::UnitType< AU::Meter, 1, AT::minute, 1, AU::gram, 0, AU::kelvin, 0, AU::ampere, 0 > t_ms;
   typedef SOU::UnitType< AU::Meter, 1, AT::minute, 0, AU::gram, 0, AU::kelvin, 0, AU::ampere, 0 > t_m;

   typedef t_m IN;
   typedef t_ms OUT;
   enum { eALLDIMS_THE_SAME = IN::eL == OUT::eL && IN::et == OUT::et && IN::eM == OUT::eM };
   static_assert(!eALLDIMS_THE_SAME);

   //t_m m = 9.0;
   //t_ms ms = conversion_cast< t_ms >( m );
}

TEST_F(conversion_castTest, constexpr_test)
{
   constexpr Metric::t_centimeter cent(20.0);
   constexpr Metric::t_meter      meter = SOU::conversion_cast<Metric::t_meter>(cent);
   static_assert(SOU::conversion_cast<Metric::t_meter>(cent).amount() == 0.20
      , "shows conversion_cast<> supports compile time equations");
}

TEST(reinterpit_cast, DoesItWork) {
   Metric::t_centimeter cent{ 100.0 };
   EXPECT_UNIT_EQ(cent, 100.0);
   //Metric::t_kilogram kg = reinterpret_cast<double>(cent);
   //Metric::t_kilogram kg = reinterpret_cast<Metric::t_kilogram>(cent);

   SUCCEED() << "Does not allow reinterpret_cast<> to work.  Test commented out.";
}

TEST_F(conversion_castTest, failedTest)
{
   typedef SOU::MakeSQ< Metric::t_gram >::type t_gramSq;
   t_gramSq kiloSq{ 1.0 };

   EXPECT_UNIT_EQ(2.0, kiloSq) << "Unhappy message goes here " << kiloSq << " and continue with more";

   EXPECT_UNIT_EQ(kiloSq, 3.0);

   EXPECT_UNIT_EQ(kiloSq, 1.0);

}

// Copyright � 2005-2019 "Curt" Leslie L. Martin, All rights reserved.
// curt.leslie.lewis.martin@gmail.com
//
// Permission to use, copy, modify, and distribute this software for any
// purpose is hereby granted without fee, provided that this copyright and
// permissions notice appear in all copies and derivatives.
//
// This software is provided "as is" without express or implied warranty.
