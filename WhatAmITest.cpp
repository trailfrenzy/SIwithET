// used to test the whatami method
#include <cppunit/extensions/HelperMacros.h> // the macros and headers needed by CPPUnit
#include "SI.h"
#include "MetricTypes.h"
#include "WhatAmI.h"
#include <strstream>

class WhatAmITest : public CppUnit::TestFixture
{
public:
   void setUp(){}
   void tearDown(){}
private:
   void TestWithOneDim()
   {
      /*
      This will be modified to reflect changes later when
      a template map is used.
      */
      Metric::t_meter meter(1.34578);
	  CPPUNIT_ASSERT_EQUAL( std::string("meter^1 "), SOU::WhatAmI(meter) );
      
      Metric::t_second sec(58903.3);
	  CPPUNIT_ASSERT_EQUAL( std::string("second^1 "), SOU::WhatAmI(sec) );
      
      Metric::t_velocity vel(81.5);
      CPPUNIT_ASSERT_EQUAL( std::string("meter^1 second^-1 "), SOU::WhatAmI(vel) );
      
      Metric::t_gramPsec massFlow(3.895);
      CPPUNIT_ASSERT_EQUAL( std::string("second^-1 gram^1 "), SOU::WhatAmI(massFlow) );
      
   }

   /// function template is used by TestWithTwoDim()
   /// @see TestWithTwoDim()
	template< int SIZE > void MakeDimTest()
	{
	   namespace AU = Metric::AtomicUnit;
	   typedef SOU::MakeType< AU::Meter, AT::second, AU::gram, AU::kelvin, AU::coulomb > AUMetric;

	   // Length compond units
	   typedef AUMetric::MakeDim< SIZE,0,0,0,0>::type t_meter; //< Meter type
	   t_meter meter(4.2);

      // Produce the string a different way to test it.
	   std::stringstream stream;
	   stream << "meter^";
      stream << SIZE;
      stream << " "; // << std::endl;
      std::string str = stream.str();

	   CPPUNIT_ASSERT_EQUAL( str, SOU::WhatAmI(meter) );

	}

   void TestWithTwoDim()
   {

	   namespace AU = Metric::AtomicUnit;
	   typedef SOU::MakeType< AU::Meter, AT::second, AU::gram, AU::kelvin, AU::coulomb > AUMetric;

	   // Length compond units
	   typedef AUMetric::MakeDim<2,0,0,0,0>::type t_meterSq; //< Meter type
	   t_meterSq meterSq(4.2);
	   CPPUNIT_ASSERT_EQUAL( std::string("meter^2 "), SOU::WhatAmI(meterSq) );

	   typedef AUMetric::MakeDim<3,0,0,0,0>::type t_meterCu; //< Meter type
	   t_meterCu meterCu(4.2);
	   CPPUNIT_ASSERT_EQUAL( std::string("meter^3 "), SOU::WhatAmI(meterCu) );
	   // CPPUNIT_ASSERT_EQUAL( std::string("meter^2 "), SOU::WhatAmI(meterCu) );

      // a series of test used to determine how the diminsions work.
  	   MakeDimTest<3>();
  	   MakeDimTest<4>();
  	   MakeDimTest<5>();
  	   MakeDimTest<6>();
  	   MakeDimTest<7>();
  	   MakeDimTest<9>();
  	   MakeDimTest<10>();
  	   MakeDimTest<33>();
  	   MakeDimTest<343>();
  	   MakeDimTest<3893>();

   }

   CPPUNIT_TEST_SUITE( WhatAmITest );
   CPPUNIT_TEST( TestWithOneDim );
   CPPUNIT_TEST( TestWithTwoDim );
   CPPUNIT_TEST_SUITE_END();
};

CPPUNIT_TEST_SUITE_REGISTRATION( WhatAmITest );

// Copyright © 2005-2015 "Curt" Leslie L. Martin, All rights reserved.
// curt.leslie.lewis.martin@gmail.com
//
// Permission to use, copy, modify, and distribute this software for any
// purpose is hereby granted without fee, provided that this copyright and
// permissions notice appear in all copies and derivatives.
//
// This software is provided "as is" without express or implied warranty.

