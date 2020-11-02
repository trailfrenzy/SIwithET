#ifndef METRIC_TYPES_INCLUDE_H
#define METRIC_TYPES_INCLUDE_H
#pragma once
#include "SI.h"
#include "MetricBaseUnits.h"  ///< contains the AU units which are used in unitType
#include "TimeAtomicUnits.h"  ///< contains the time atomic units
#include "WhatAmI.h"

namespace AT = Metric::AtomicUnit;
/**
 @page page2 Metric Types

 @section MAD Predefined Metric types that can be used. A small selection of UDL (User Defined Literals)

*/
namespace Metric
{
   namespace AU = AtomicUnit;

   // TODO: change AU::gram to kilogram.
   /// Used in makeing other metric types.
   using AUMetric=SystemOfUnits::MakeType< AU::Meter, AT::second, AU::kilogram, AU::kelvin, AU::ampere >;

   /// Length compond units
   ///< Meter type
   using t_meter = AUMetric::MakeDim<1,0,0,0,0>::type;

   /// Kilometer type
   using t_kilometer = SystemOfUnits::unitType< AU::Kilometer, 1, AT::second, 0, AU::kilogram, 0,AU::kelvin,0, AU::ampere,0 >;

   /// Centimeter type
   using t_centimeter = SystemOfUnits::unitType< AU::Centimeter, 1, AT::second, 0, AU::kilogram, 0,AU::kelvin,0, AU::ampere,0 >;

   /// Milimeter type
   using t_milimeter = SystemOfUnits::unitType< AU::Milimeter, 1, AT::second, 0, AU::kilogram, 0,AU::kelvin,0, AU::ampere,0 >;
   
   /// Time compond units (TODO look at replacing with std::chronos)
   using t_second = AUMetric::MakeDim<0,1,0,0,0>::type; /// Seconds type
   using t_minute = SystemOfUnits::unitType< AU::Meter, 0, AT::minute, 1, AU::kilogram, 0,AU::kelvin,0, AU::ampere,0 >;
   using t_hour = SystemOfUnits::unitType< AU::Meter, 0, AT::hour,   1, AU::kilogram, 0,AU::kelvin,0, AU::ampere,0 >;

   /// Mass compond units
   using t_gram = SystemOfUnits::unitType< AU::Meter, 0, AT::second, 0, AU::gram, 1, AU::kelvin, 0, AU::ampere, 0 >; /// Gram type
   using t_miligram = SystemOfUnits::unitType< AU::Meter, 0, AT::second, 0, AU::miligram, 1,AU::kelvin,0, AU::ampere,0 >;
   using t_kilogram = SystemOfUnits::unitType< AU::Meter, 0, AT::second, 0, AU::kilogram, 1,AU::kelvin,0, AU::ampere,0 >;
   
   // 
   using t_metersecond = AUMetric::MakeDim<1,1,0,0,0>::type; /// Meter * second type

   // Velocity compound units
   using t_velocity = AUMetric::MakeDim<1,-1,0,0,0>::type;

   // Mass flow compound units
   using t_gramPsec = AUMetric::MakeDim<0,-1,1,0,0>::type;

} // end of namespace

// Metric UDL's (User Defined Literals)
inline constexpr auto operator"" _meter( long double d) noexcept
{
   return Metric::t_meter(d);
}

constexpr auto operator"" _kilogram(long double d) noexcept {
   return Metric::t_kilometer(d);
}

// Kilometer UDL (User Definded Literals)
constexpr auto operator"" _kilometer( long double d) noexcept
{ return Metric::t_kilometer{ static_cast<double>(d) }; }

constexpr auto operator"" _kph( long double d) noexcept
{
   using t_kilometerPerHour = SystemOfUnits::unitType< Metric::AU::Kilometer, 1, AT::hour, -1, Metric::AU::gram, 0, Metric::AU::kelvin, 0, Metric::AU::ampere, 0 >;
   return t_kilometerPerHour{ d };
}
constexpr auto operator"" _centimeter(long double d) noexcept
{ return Metric::t_centimeter{ d }; }
constexpr auto operator"" _milimeter(long double d) noexcept
{ return Metric::t_milimeter{ d }; }

// Copyright © 2005-2019 "Curt" Leslie L. Martin, All rights reserved.
// curt.leslie.lewis.martin@gmail.com
//
// Permission to use, copy, modify, and distribute this software for any
// purpose is hereby granted without fee, provided that this copyright and
// permissions notice appear in all copies and derivatives.
//
// This software is provided "as is" without express or implied warranty.

#endif