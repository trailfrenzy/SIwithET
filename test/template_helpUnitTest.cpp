// cpp file is created only to use with Google Test Framework.
#include "template_help.h"	/// The file we are testing.
#include "MetricTypes.h"
#include <gtest/gtest.h>
#include <tuple>


TEST(helpUnitTest, IF_Test)
{
	static_assert((std::is_same< SystemOfUnits::IF<true, int, double >::RET, int >::value));
	static_assert((std::is_same< SystemOfUnits::IF<false, int, double >::RET, double>::value));
}

TEST(helpUnitTest, MetricMeter) {
	static_assert( !std::is_same<Metric::t_meter, Metric::t_centimeter>::value);
}
TEST(helpUnitTest, MetricGram) {
	static_assert(!std::is_same<Metric::t_gram, Metric::t_kilogram>::value);
}

using t_MakeType = SOU::MakeType< Metric::AtomicUnit::Meter, AT::second, Metric::AtomicUnit::kilogram, Metric::AtomicUnit::kelvin, Metric::AtomicUnit::ampere >;
using t_Joule = t_MakeType::MakeDim<2, -2, 1, 0, 0>::type;

TEST(Sort, DISABLED_UseTuple) { 
	GTEST_FAIL() << "Ignored since the tuple_selection_sort<> is not working. Asked https://codereview.stackexchange.com if the code has worked with the MS-VC compilers.";
	using namespace SystemOfUnits;
	using t_L = TL::Atom< t_Joule::eL, t_Joule::Length >;
	using t_M = TL::Atom< t_Joule::eM, t_Joule::Mass >;
	using t_time = TL::Atom< t_Joule::et, t_Joule::Time >;
	using t_T = TL::Atom< t_Joule::eT, t_Joule::Temperature >;
	using t_Q = TL::Atom< t_Joule::eQ, t_Joule::Charge >;
	using input_tuple_t = std::tuple< t_L, t_M, t_time, t_T, t_Q >;

	//using result_tuple_t = TL::tuple_selection_sort< TL::descending, input_tuple_t>::type;

}

