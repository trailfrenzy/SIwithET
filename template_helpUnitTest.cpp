// cpp file is created only to test with CPPUnit
#include <cppunit/extensions/HelperMacros.h>	// contains the help we need
#include "template_help.h"	/// The file we are testing.

class TheSameTypeTest : public CppUnit::TestFixture
{
public:
   void runTest()
   {
	   CPPUNIT_ASSERT( (SystemOfUnits::is_same<float, float>::value) );
	   CPPUNIT_ASSERT( (SystemOfUnits::is_same<int,int>::value ) );
      CPPUNIT_ASSERT( (SystemOfUnits::is_same<double, double>::value) );
      CPPUNIT_ASSERT( (!SystemOfUnits::is_same<int, double >::value) );
   }

	/// The test suite
   CPPUNIT_TEST_SUITE( TheSameTypeTest );
   CPPUNIT_TEST( runTest );
   CPPUNIT_TEST_SUITE_END();

};

CPPUNIT_TEST_SUITE_REGISTRATION( TheSameTypeTest );

class IF_Test : public CppUnit::TestFixture
{
public:
	void runTest()
	{
		CPPUNIT_ASSERT( 4 == 4);
		CPPUNIT_ASSERT( (SystemOfUnits::is_same< SystemOfUnits::IF<true,  int, double >::RET, int >::value) );
		CPPUNIT_ASSERT( (SystemOfUnits::is_same< SystemOfUnits::IF<false, int, double >::RET, double>::value) );
	}

	/// The test suite
	CPPUNIT_TEST_SUITE( IF_Test );
	CPPUNIT_TEST( runTest );
	CPPUNIT_TEST_SUITE_END();
};

CPPUNIT_TEST_SUITE_REGISTRATION( IF_Test );