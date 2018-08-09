// cpp file is created only to test with CPPUnit
//#include <cppunit/extensions/HelperMacros.h>	// contains the help we need
#include <gtest/gtest.h>
#include "template_help.h"	/// The file we are testing.

//class TheSameTypeTest : public ::testing::Test //: public CppUnit::TestFixture
//{
//public:
//
//	/// The test suite
//   CPPUNIT_TEST_SUITE( TheSameTypeTest );
//   CPPUNIT_TEST( runTest );
//   CPPUNIT_TEST_SUITE_END();
//
//};
//
//CPPUNIT_TEST_SUITE_REGISTRATION( TheSameTypeTest );

TEST(helpUnitTest, TheSameTypeTest)  //void runTest()
{
	EXPECT_TRUE((SystemOfUnits::is_same<float, float>::value)) << "Using the built in types for test";
	EXPECT_TRUE((SystemOfUnits::is_same<int, int>::value));
	EXPECT_TRUE((SystemOfUnits::is_same<double, double>::value));
	EXPECT_FALSE((SystemOfUnits::is_same<int, double >::value));
}

TEST(helpUnitTest, IF_Test)
{
	EXPECT_TRUE(4 == 4) << "A test for my own sanity";
	EXPECT_TRUE((SystemOfUnits::is_same< SystemOfUnits::IF<true, int, double >::RET, int >::value));
	EXPECT_TRUE((SystemOfUnits::is_same< SystemOfUnits::IF<false, int, double >::RET, double>::value));
}


//class IF_Test : public CppUnit::TestFixture
//{
//public:
//	void runTest()
//	{
//		CPPUNIT_ASSERT( 4 == 4);
//		CPPUNIT_ASSERT( (SystemOfUnits::is_same< SystemOfUnits::IF<true,  int, double >::RET, int >::value) );
//		CPPUNIT_ASSERT( (SystemOfUnits::is_same< SystemOfUnits::IF<false, int, double >::RET, double>::value) );
//	}
//
//	/// The test suite
//	CPPUNIT_TEST_SUITE( IF_Test );
//	CPPUNIT_TEST( runTest );
//	CPPUNIT_TEST_SUITE_END();
//};
//
//CPPUNIT_TEST_SUITE_REGISTRATION( IF_Test );