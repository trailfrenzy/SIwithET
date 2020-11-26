// used to test the WhatAmI() method
#include "WhatAmI.h"
#include "SI.h"
#include "MetricTypes.h"
#include "operators.h"
#include <sstream>
#include <string_view>
#include <gtest/gtest.h>
#include "ExpectUnitTest.h"

TEST(Diminsion, NoDim) {
	EXPECT_EQ("", SOU::Diminsion(SOU::tNoUnit(2.0) ));
}
TEST(Diminsion, Double) {
   double x = 3.5;
   EXPECT_EQ("", SOU::Diminsion(x));
   EXPECT_EQ("", SOU::Diminsion(4.5));
   EXPECT_EQ("", SOU::Diminsion(6.5f));
   EXPECT_EQ("", SOU::Diminsion(7u));
   // TODO add test for a float
}

TEST(Diminsion, LEN) {
	Metric::t_meter meter{ 444.5 };
	EXPECT_STREQ("[L]", SOU::Diminsion(meter).c_str() );
}
TEST(Diminsion, MassRule) {
	Metric::t_gram gram{ 444.5 };
	EXPECT_EQ("[M]", SOU::Diminsion(gram));
}
TEST(Diminsion, TimeRule ) {
	Metric::t_second sec{ 444.5 };
	EXPECT_EQ("[T]", SOU::Diminsion(sec));
}

TEST(Diminsion, Inverse) {
	Metric::t_gram gram{ 444.5 };
	auto inv = 1.0 / gram;
	EXPECT_EQ("1/[M]", SOU::Diminsion(inv));
}

TEST(Diminsion, InvSquared) {
   Metric::t_gram const gram{ 444.5 };
   auto inv = 1.0 / (gram*gram);
   EXPECT_EQ("1/[M]^2", SOU::Diminsion(inv));
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
	EXPECT_EQ(std::string_view( "meter/second"), SOU::WhatAmI(vel));

	Metric::t_gramPsec massFlow(3.895);
	EXPECT_EQ(std::string_view("kilogram/second"), SOU::WhatAmI(massFlow));
}

TEST(UnitNameWchar, Basic)
{
   Metric::t_meter const meter(1.34578f);
	EXPECT_STREQ( L"meter", SOU::UnitName<wchar_t>(meter).c_str() );

   Metric::t_second sec(58903.3);
   EXPECT_EQ(std::wstring(L"second"), SOU::UnitName<wchar_t>(sec));

   Metric::t_velocity vel(81.5);
   EXPECT_EQ(std::wstring_view(L"meter/second"), SOU::UnitName<wchar_t>(vel));

   Metric::t_gramPsec massFlow(3.895);
   EXPECT_EQ(std::wstring_view(L"kilogram/second"), SOU::UnitName<wchar_t>(massFlow));
}

TEST(UnitNameWchar, Dim) {
   Metric::t_meter const meter(1.34578f);
   EXPECT_EQ(std::wstring(L"[L]"), SOU::t_Diminsion<wchar_t>(meter));

   Metric::t_second sec(58903.3);
   EXPECT_EQ(std::wstring(L"[T]"), SOU::t_Diminsion<wchar_t>(sec));

   Metric::t_velocity vel(81.5);
   EXPECT_EQ(std::wstring_view(L"[L]/[T]"), SOU::t_Diminsion<wchar_t>(vel));

   Metric::t_gramPsec massFlow(3.895);
   EXPECT_EQ(std::wstring_view(L"[M]/[T]"), SOU::t_Diminsion<wchar_t>(massFlow));
}

/// function template is used by TestWithTwoDim()
/// @see TestWithTwoDim()
template< int SIZE > void MakeDimTest()
{
	namespace AU = Metric::AtomicUnit;
   enum:int{ eSIZE = SIZE };
   typedef SOU::UnitType< AU::Meter, eSIZE, AT::second, 0, AU::gram, 0, AU::kelvin, 0, AU::ampere, 0 > type;

	type meter(4.2);

	// Produce the string a different way to test it.
	std::stringstream stream;
	stream << "meter^" << SIZE;
	std::string const str = stream.str();

	EXPECT_EQ(str, SOU::WhatAmI(meter));
}

TEST(WhatAmITest, TestWithTwoDim)
{

	namespace AU = Metric::AtomicUnit;
	typedef SOU::MakeType< AU::Meter, AT::second, AU::gram, AU::kelvin, AU::ampere > AUMetric;

	// Length compound units
	typedef AUMetric::MakeDim<2, 0, 0, 0, 0>::type t_meterSq; //< Meter type
	t_meterSq meterSq(4.2);
	EXPECT_EQ(std::string("meter^2"), SOU::WhatAmI(meterSq));

	typedef AUMetric::MakeDim<3, 0, 0, 0, 0>::type t_meterCu; //< Meter type
	t_meterCu meterCu(4.2);
	EXPECT_EQ(std::string("meter^3"), SOU::WhatAmI(meterCu));
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

TEST(WhatAmITest, Inverse)
{
	using namespace SystemOfUnits::literals;

	auto res1 = 36.0 / 3.0_meter;
	//std::cout << "auto res1 = " << SOU::WhatAmI(res1) << '\n';
	EXPECT_UNIT_EQ(res1, 12.0) << "The type is " << SOU::WhatAmI(res1);

	EXPECT_EQ(SOU::WhatAmI(res1), "1/meter") << "Think about changing so it is like the dimensions";
}

TEST(WhatAmITest, NoDim )
{
	using namespace SystemOfUnits::literals;
	auto val = 40.0_meter / 5.0_meter;
	EXPECT_EQ("", SOU::WhatAmI(val) ) << "Test caused an error from erasing the last astrick if empty";
}



// Copyright © 2005-2020 "Curt" Leslie L. Martin, All rights reserved.
// curt.leslie.lewis.martin@gmail.com
//
// Permission to use, copy, modify, and distribute this software for any
// purpose is hereby granted without fee, provided that this copyright and
// permissions notice appear in all copies and derivatives.
//
// This software is provided "as is" without express or implied warranty.
