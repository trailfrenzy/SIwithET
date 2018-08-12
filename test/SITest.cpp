

//#include <cppunit/extensions/HelperMacros.h> // the macros and headers needed by CPPUnit
#include <gtest/gtest.h>
#include "SI.h"
#include "MetricTypes.h"
//#include "boost/type_traits/is_same.hpp"  // used by SITestSQ
#include "template_help.h"

template< class UNIT_TYPE >
class SITest : public testing::Test //: public CppUnit::TestFixture
{
	//CPPUNIT_TEST_SUITE( SITest );
	//CPPUNIT_TEST( Assignment );
	//CPPUNIT_TEST( NotEqual );
	//CPPUNIT_TEST( LessThan );
	//CPPUNIT_TEST( GreaterThan );
	//CPPUNIT_TEST( Comparison );
	//CPPUNIT_TEST( Addition );
	//CPPUNIT_TEST( AdditionAssignment );
	//CPPUNIT_TEST( Subtraction );
	//CPPUNIT_TEST( SubtractionAssignment );
	//CPPUNIT_TEST( Chaining );
	////CPPUNIT_TEST( Squaring );
	//CPPUNIT_TEST_SUITE_END();

protected:
	UNIT_TYPE * m_1;
	UNIT_TYPE * m_2;
	UNIT_TYPE const * m_3;
	UNIT_TYPE const * m_4;

public:
	using t_type = UNIT_TYPE;
	void SetUp()
	{
		m_1 = new UNIT_TYPE(8.0);
		m_2 = new UNIT_TYPE(5.0);
		m_3 = new UNIT_TYPE(3.0);
		m_4 = new UNIT_TYPE(4.0);
	}

	void TearDown()
	{
		delete m_1;
		delete m_2;
		delete m_3;
		delete m_4;
	}
private:
};

TYPED_TEST_CASE_P(SITest);

/// All types should be the same as a double
TYPED_TEST_P(SITest, SizeOf)
{
	using TAG = SITest<TypeParam >;
	EXPECT_TRUE(sizeof(double) == sizeof(TAG::t_type)) << "was not 64 bit";
}

TYPED_TEST_P(SITest, Comparison)
{
	using TAG = SITest<TypeParam >;
	//using namespace SI;
	*TAG::m_1 = TAG::t_type(4.5);
	*TAG::m_2 = TAG::t_type(4.5);

	EXPECT_TRUE(*TAG::m_1 == *TAG::m_2);
	EXPECT_TRUE(TAG::m_1->amount() == 4.5);

	// testing with one side double the other side unitType
	EXPECT_TRUE(*TAG::m_1 == 4.5);
	EXPECT_TRUE(4.5 == *TAG::m_1);
}

TYPED_TEST_P(SITest, NotEqual)
{
	using TAG = SITest<TypeParam >;
	EXPECT_TRUE(*TAG::m_1 != *TAG::m_2);
	EXPECT_TRUE(4.5 != *TAG::m_2);
	EXPECT_TRUE(*TAG::m_2 != 4.5);
}

TYPED_TEST_P(SITest, LessThan)
{
	using TAG = SITest<TypeParam >;
	*TAG::m_1 = TAG::t_type(4.55555);
	*TAG::m_2 = TAG::t_type(4.55556);
	EXPECT_TRUE(*TAG::m_1 < *TAG::m_2);
	EXPECT_TRUE(*TAG::m_3 < *TAG::m_4);
}

TYPED_TEST_P(SITest, GreaterThan)
{
	using TAG = SITest<TypeParam >;
	EXPECT_TRUE(*TAG::m_4 > *TAG::m_3);
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
TYPED_TEST_P(SITest, AdditionAssignment)
{
	using TAG = SITest<TypeParam >;
	*TAG::m_2 += *TAG::m_3;
	EXPECT_TRUE(*TAG::m_1 == *TAG::m_2);
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

REGISTER_TYPED_TEST_CASE_P(SITest
	, SizeOf, Assignment, NotEqual, LessThan, GreaterThan, Comparison, Addition, AdditionAssignment, Subtraction, SubtractionAssignment, Chaining );


//};

   TEST(SITestSQ, Squaring )
   {
      namespace AT = SOU::Time::AtomicUnit;
      using namespace Metric::AtomicUnit;
      typedef SOU::unitType< Meter, 0, AT::second,-1, gram, 1, SOU::NoDim,0,SOU::NoDim > t_gramPsec;
      typedef SOU::unitType< Meter, 0, AT::second,-2, gram, 2, SOU::NoDim,0,SOU::NoDim > t_gramPsecSQ;

      typedef SOU::MakeSQ<t_gramPsec>::type gramSQ;

	  enum { b = SystemOfUnits::is_same< gramSQ, typename t_gramPsecSQ >::value };
	  EXPECT_TRUE( b );
      
   }

   /// Size is needed to show that unitType<> is the same size as a double
   TEST(SITestSQ, TestSize )
   {
	   EXPECT_TRUE( sizeof(double) == sizeof( Metric::t_meter ) );
   }


//CPPUNIT_TEST_SUITE_REGISTRATION( SITest<Metric::t_meter> );
//CPPUNIT_TEST_SUITE_REGISTRATION( SITest<Metric::t_metersecond> );
//CPPUNIT_TEST_SUITE_REGISTRATION( SITest<Metric::t_second> );
//CPPUNIT_TEST_SUITE_REGISTRATION( SITest<Metric::t_velocity> );
//CPPUNIT_TEST_SUITE_REGISTRATION( SITest<Metric::t_gramPsec> );
//CPPUNIT_TEST_SUITE_REGISTRATION( SITestSQ );

typedef Metric::AtomicUnit::Meter Meter;
typedef SOU::Time::AtomicUnit::second second;
typedef Metric::AtomicUnit::gram gram;
typedef SOU::MakeType< Meter, second, Metric::AtomicUnit::kilogram, Metric::AtomicUnit::kelvin, Metric::AtomicUnit::coulomb > t_Base;
//typedef SI::unitType< Meter, 1, second, 0, gram, 0 > t_Meter;
//typedef t_Base::MakeDim<1,0,0,0,0>::type t_Meter;

typedef t_Base::MakeDim<2,0,0,0,0>::type t_MeterSq;
typedef t_Base::MakeDim<3,0,0,0,0>::type t_MeterCubed;

typedef ::testing::Types< Metric::t_meter, Metric::t_metersecond, Metric::t_second, Metric::t_velocity, Metric::t_gramPsec, t_MeterSq, t_MeterCubed > MyTypes;
INSTANTIATE_TYPED_TEST_CASE_P(My, SITest, MyTypes);

//CPPUNIT_TEST_SUITE_REGISTRATION( SITest<t_MeterSq> );
//CPPUNIT_TEST_SUITE_REGISTRATION( SITest<t_MeterCubed>);

// Copyright © 2005-2015 "Curt" Leslie L. Martin, All rights reserved.
// curt.leslie.lewis.martin@gmail.com
//
// Permission to use, copy, modify, and distribute this software for any
// purpose is hereby granted without fee, provided that this copyright and
// permissions notice appear in all copies and derivatives.
//
// This software is provided "as is" without express or implied warranty.
