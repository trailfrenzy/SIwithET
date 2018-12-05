#include "SI.h"
#include "operators.h"
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

TEST(Inserter, ShowDimMeterCubed) {
   t_MeterCubed m3(10.11);

   std::stringstream strm;
   strm << SOU::dimension << m3;
   EXPECT_EQ(strm.str(), std::string("10.11 [L]^3"));
}

TEST(Inserter, ShowUnitMeterCubed) {
   t_MeterCubed m3(10.11);

   std::stringstream strm;
   strm << SOU::units << m3;
   EXPECT_EQ(strm.str(), std::string("10.11 meter^3"));
}

TEST(Inserter, ShowDimMeterCubed44) {
   t_MeterCubed m3(10.11);

   std::stringstream strm;
   strm << SOU::dimension << m3 << ' ' << 44;
   EXPECT_EQ(strm.str(), std::string("10.11 [L]^3 44"));
}

TEST(Inserter, ShowUnitMeterCubed44) {
   t_MeterCubed m3(10.11);

   std::stringstream strm;
   strm << SOU::units << m3 << ' ' << 44;
   EXPECT_EQ(strm.str(), std::string("10.11 meter^3 44"));
}

TEST(Inserter, ShowDimMeterSqDouble) {
   t_MeterSq m3(10.11);

   std::stringstream strm;
   strm << SOU::dimension << m3 << ' ' << 44.6666;
   EXPECT_EQ(strm.str(), std::string("10.11 [L]^2 44.6666"));
}

TEST(Inserter, ShowUnitMeterSqDouble) {
   t_MeterSq m3(10.11);

   std::stringstream strm;
   strm << SOU::units << m3 << ' ' << 44.6666;
   EXPECT_EQ(strm.str(), std::string("10.11 meter^2 44.6666"));
}

TEST(Inserter, ShowDimMeterSqCstring) {
   t_MeterSq m3(10.11);

   std::stringstream strm;
   strm << SOU::dimension << m3 << ' ' << "44.6666";
   EXPECT_EQ(strm.str(), std::string("10.11 [L]^2 44.6666"));
}

TEST(Inserter, ShowDimMeterSqString) {
   t_MeterSq m3(10.11);

   std::stringstream strm;
   strm << SOU::dimension << m3 << ' ' << std::string("44.6666");
   EXPECT_EQ(strm.str(), std::string("10.11 [L]^2 44.6666"));
}
// Copyright © 2005-2018 "Curt" Leslie L. Martin, All rights reserved.
// curt.leslie.lewis.martin@gmail.com
//
// Permission to use, copy, modify, and distribute this software for any
// purpose is hereby granted without fee, provided that this copyright and
// permissions notice appear in all copies and derivatives.
//
// This software is provided "as is" without express or implied warranty.
