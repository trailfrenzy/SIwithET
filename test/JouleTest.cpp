﻿
#include <gtest/gtest.h>
#include "MetricTypes.h"
#include "WhatAmI.h"
/*
The joule is a derived unit of energy in the International System of Units. It is equal to the energy transferred to an object when a force of one newton acts on that object in the direction of its motion through a distance of one metre. Wikipedia
SI base units: kg⋅m2⋅s−2
Unit system: SI derived unit
Unit of: Energy
CGS units: 1×107 erg
1 J in: is equal to
Named after: James Prescott Joule
*/


using t_Joule = Metric::AUMetric::MakeDim<2, -2, 1, 0, 0>::type;

TEST(Diminsion, Joule) {
	t_Joule joule{ 45.033 };
	EXPECT_EQ(SystemOfUnits::Diminsion(joule), "L^2·t^-2·M");
	//EXPECT_TRUE(SystemOfUnits::Diminsion(joule) == std::string("L^2⋅t^-2⋅M"));
}

/*
The newton (symbol: N) is the International System of Units (SI) derived unit of force. It is named after Isaac Newton in recognition of his work on classical ...
SI base units‎: ‎1 kg⋅m⋅s−2	Unit of‎: ‎Force
Unit system‎: ‎SI derived unit	1 N in‎: ‎is equal to
*/
using t_Newton = Metric::AUMetric::MakeDim<1, -2, 1, 0, 0 >::type;