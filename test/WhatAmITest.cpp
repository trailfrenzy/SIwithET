// used to test the whatami method
//#include "cppunit/extensions/HelperMacros.h" // the macros and headers needed by CPPUnit
#include <gtest/gtest.h>
#include "SI.h"
#include "MetricTypes.h"
#include "WhatAmI.h"
#include "operators.h"
#include <sstream>
#include <string_view>

TEST(Diminsion, NoDim) {
	EXPECT_EQ("", SOU::Diminsion(SOU::tNoUnit(2.0) ));
}

TEST(Diminsion, LEN) {
	Metric::t_meter meter{ 444.5 };
	EXPECT_EQ("[L]", SOU::Diminsion(meter));
}
TEST(Diminsion, MASS) {
	Metric::t_gram gram{ 444.5 };
	EXPECT_EQ("[M]", SOU::Diminsion(gram));
}
TEST(Diminsion, TIME ) {
	Metric::t_second sec{ 444.5 };
	EXPECT_EQ("[T]", SOU::Diminsion(sec));
}

TEST(Diminsion, Inverse) {
	Metric::t_gram gram{ 444.5 };
	auto inv = 1.0 / gram;
	EXPECT_EQ("1/[M]", SOU::Diminsion(inv));
}

TEST(WhatAmITest, TestWithOneDim)
{
	/*
	This will be modified to reflect changes later when
	a template map is used.
	*/
	Metric::t_meter const meter(1.34578f);
	EXPECT_EQ(std::string("meter"), SOU::WhatAmI(meter));

	Metric::t_second sec(58903.3);
	EXPECT_EQ(std::string("second"), SOU::WhatAmI(sec));

	Metric::t_velocity vel(81.5);
	EXPECT_EQ(std::string_view( "meter*second^(-1)"), SOU::WhatAmI(vel));

	Metric::t_gramPsec massFlow(3.895);
	EXPECT_EQ(std::string_view("second^(-1)*gram"), SOU::WhatAmI(massFlow));
	EXPECT_TRUE(true);
}

TEST(UnitNameWchar, Basic)
{
   Metric::t_meter const meter(1.34578f);
   EXPECT_EQ(std::wstring(L"meter"), SOU::UnitName<wchar_t>(meter));

   Metric::t_second sec(58903.3);
   EXPECT_EQ(std::wstring(L"second"), SOU::UnitName<wchar_t>(sec));

   Metric::t_velocity vel(81.5);
   EXPECT_EQ(std::wstring_view(L"meter*second^(-1)"), SOU::UnitName<wchar_t>(vel));

   Metric::t_gramPsec massFlow(3.895);
   EXPECT_EQ(std::wstring_view(L"second^(-1)*gram"), SOU::UnitName<wchar_t>(massFlow));
}

/// function template is used by TestWithTwoDim()
/// @see TestWithTwoDim()
template< int SIZE > void MakeDimTest()
{
	namespace AU = Metric::AtomicUnit;
	typedef SOU::MakeType< AU::Meter, AT::second, AU::gram, AU::kelvin, AU::coulomb > AUMetric;

	// Length compound units
	typedef AUMetric::MakeDim< SIZE, 0, 0, 0, 0>::type t_meter; //< Meter type
	t_meter meter(4.2);

	// Produce the string a different way to test it.
	std::stringstream stream;
	stream << "meter^";
	stream << SIZE;
	//stream << " "; // << std::endl;
	std::string const str = stream.str();

	EXPECT_EQ(str, SOU::WhatAmI(meter));

}

TEST(WhatAmITest, TestWithTwoDim)
{

	namespace AU = Metric::AtomicUnit;
	typedef SOU::MakeType< AU::Meter, AT::second, AU::gram, AU::kelvin, AU::coulomb > AUMetric;

	// Length compound units
	typedef AUMetric::MakeDim<2, 0, 0, 0, 0>::type t_meterSq; //< Meter type
	t_meterSq meterSq(4.2);
	EXPECT_EQ(std::string("meter^2"), SOU::WhatAmI(meterSq));

	typedef AUMetric::MakeDim<3, 0, 0, 0, 0>::type t_meterCu; //< Meter type
	t_meterCu meterCu(4.2);
	EXPECT_EQ(std::string("meter^3"), SOU::WhatAmI(meterCu));
	// CPPUNIT_ASSERT_EQUAL( std::string("meter^2 "), SOU::WhatAmI(meterCu) );
}

TEST(WhatAmITest, TestMultipleDim)
{
	// a series of test used to determine how the dimensions work.
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

TEST(WhatAmITest, TestDouble)
{
	double val = 6.7888;
	EXPECT_EQ(SOU::WhatAmI(val), std::string(""));
}

TEST(Diminsion, OneDimPrint1) {
	SystemOfUnits::helpers::t_bufPair bufPair;
	std::string temp{ SystemOfUnits::helpers::OneDim<'L', 1>(bufPair).first.str() };
	EXPECT_EQ( temp , std::string("[L]") );
	temp = SystemOfUnits::helpers::OneDim<'M', -1 >(bufPair).second.str();
	EXPECT_EQ(temp, "[M]");
}
TEST(Diminsion, OneDimPrint2) {
	SystemOfUnits::helpers::t_bufPair bufPair;
	std::string temp = SystemOfUnits::helpers::OneDim<'L', 2>(bufPair).first.str();
	EXPECT_EQ(temp, "[L]^2");
	temp = SystemOfUnits::helpers::OneDim<'M', -3 >(bufPair).second.str();
	EXPECT_EQ(temp, "[M]^3");
}
TEST(Diminsion, Struct_Sym) {
   using t_X = SystemOfUnits::helpers::T_Symbol<'X'>;
   EXPECT_EQ('X', t_X::sym);
}

TEST(Dim, DISABLED_NoDiminsion) {
   //EXPECT_EQ( SystemOfUnits::Dim(SystemOfUnits::tNoUnit() ), std::string("") );
}

// Copyright © 2005-2015 "Curt" Leslie L. Martin, All rights reserved.
// curt.leslie.lewis.martin@gmail.com
//
// Permission to use, copy, modify, and distribute this software for any
// purpose is hereby granted without fee, provided that this copyright and
// permissions notice appear in all copies and derivatives.
//
// This software is provided "as is" without express or implied warranty.
