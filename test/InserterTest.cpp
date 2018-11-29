#include "SI.h"
#include <gtest/gtest.h>
#include <sstream>
#include "MetricTypes.h"

typedef Metric::AtomicUnit::Meter Meter;
typedef SOU::Time::AtomicUnit::second second;
typedef Metric::AtomicUnit::gram gram;
typedef SOU::MakeType< Meter, second, Metric::AtomicUnit::kilogram, Metric::AtomicUnit::kelvin, Metric::AtomicUnit::coulomb > t_Base;
typedef t_Base::MakeDim<2, 0, 0, 0, 0>::type t_MeterSq;
typedef t_Base::MakeDim<3, 0, 0, 0, 0>::type t_MeterCubed;

TEST(Inserter, MeterCubed) {
   t_MeterCubed m3(10.11);

   std::stringstream strm;
   strm << m3;
   EXPECT_EQ(strm.str(), std::string("10.11"));
}

