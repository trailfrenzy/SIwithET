#include <gtest/gtest.h>
#include "Tempeture.h"
#include "MetricTypes.h"
#include "conversion_cast.h"

namespace AU = Metric::AU;
using AUMetric = Metric::AUMetric;

using t_Kelvin = AUMetric::MakeDim<0, 0, 0, 1, 0>::type;

using t_Far = SOU::unitType< AU::Meter, 0, AT::minute, 1, AU::gram, 0, SOU::Temperature::fahrenheit, 0, AU::coulomb, 0 >;
using t_Cel = SOU::unitType< AU::Meter, 0, AT::minute, 1, AU::gram, 0, SOU::Temperature::celsius, 0, AU::coulomb, 0 >;

TEST(Temperature, StartC) {
	t_Kelvin K(0.0);
	t_Cel C = SOU::conversion_cast<t_Cel>(K);
	EXPECT_NEAR(C.amount(), -273.15, 0.01) << "is it close?";
}