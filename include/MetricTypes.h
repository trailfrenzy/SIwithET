#ifndef METRIC_TYPES_INCLUDE_H
#define METRIC_TYPES_INCLUDE_H
#pragma once
#include "SI.h"
#include "MetricBaseUnits.h"  ///< contains the AU units which are used in unitType
#include "TimeAtomicUnits.h"  ///< contains the time atomic units

namespace AT = SOU::Time::AtomicUnit;
/**
 @page page2 Metric Types

 @section MAD Predefined Metric types that can be used.

*/
namespace Metric
{
   namespace AU = AtomicUnit;

   typedef SOU::MakeType< AU::Meter, AT::second, AU::gram, AU::kelvin, AU::coulomb > AUMetric;

   /// Length compond units
   typedef AUMetric::MakeDim<1,0,0,0,0>::type t_meter; ///< Meter type
   typedef SOU::unitType< AU::Kilometer, 1, AT::second, 0, AU::gram, 0,AU::kelvin,0, AU::coulomb,0 > t_kilometer; /// Kilometer type
   typedef SOU::unitType< AU::Centimeter, 1, AT::second, 0, AU::gram, 0,AU::kelvin,0, AU::coulomb,0 > t_centimeter; /// Centimeter type
   typedef SOU::unitType< AU::Milimeter, 1, AT::second, 0, AU::gram, 0,AU::kelvin,0, AU::coulomb,0 > t_milimeter; /// Milimeter type
   
   /// Time compond units
   typedef AUMetric::MakeDim<0,1,0,0,0>::type t_second; /// Seconds type
   typedef SOU::unitType< AU::Meter, 0, AT::minute, 1, AU::gram, 0,AU::kelvin,0, AU::coulomb,0 > t_minute;
   typedef SOU::unitType< AU::Meter, 0, AT::hour,   1, AU::gram, 0,AU::kelvin,0, AU::coulomb,0 > t_hour;

   /// Mass compond units
   typedef AUMetric::MakeDim<0,0,1,0,0>::type t_gram; /// Gram type
   typedef SOU::unitType< AU::Meter, 0, AT::second, 0, AU::miligram, 1,AU::kelvin,0, AU::coulomb,0 > t_miligram;
   typedef SOU::unitType< AU::Meter, 0, AT::second, 0, AU::kilogram, 1,AU::kelvin,0, AU::coulomb,0 > t_kilogram;
   
   // 
   typedef AUMetric::MakeDim<1,1,0,0,0>::type t_metersecond; /// Meter * second type

// Velocity compound units
   typedef AUMetric::MakeDim<1,-1,0,0,0>::type t_velocity;

   // Mass flow compound units
   typedef AUMetric::MakeDim<0,-1,1,0,0>::type t_gramPsec;

} // end of namespace

// Metric UDL's (User Defined Literals)
constexpr Metric::t_meter operator"" _meter( long double d)
{
   return Metric::t_meter(d);
}

// Kilometer UDL
constexpr Metric::t_kilometer operator"" _kilometer( long double d) { return Metric::t_kilometer{ static_cast<double>(d) }; }

constexpr auto operator"" _kph( long double d)
{
   typedef SOU::unitType< Metric::AU::Kilometer, 1, AT::hour, -1, Metric::AU::gram, 0, Metric::AU::kelvin, 0, Metric::AU::coulomb, 0 > t_kilometerPerHour;
   return t_kilometerPerHour{ d };
}
constexpr Metric::t_centimeter operator"" _centimeter(long double d) { return Metric::t_centimeter{ d }; }
constexpr Metric::t_milimeter operator"" _milimeter(long double d) { return Metric::t_milimeter{ d }; }

// Copyright © 2005-2019 "Curt" Leslie L. Martin, All rights reserved.
// curt.leslie.lewis.martin@gmail.com
//
// Permission to use, copy, modify, and distribute this software for any
// purpose is hereby granted without fee, provided that this copyright and
// permissions notice appear in all copies and derivatives.
//
// This software is provided "as is" without express or implied warranty.

#endif