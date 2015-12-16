#ifndef SI_ENGLISHTYPES_INCLUDE_H
#define SI_ENGLISHTYPES_INCLUDE_H
#include "EnglishBaseUnits.h" /// location of the english base atomic types.
#include "MetricBaseUnits.h"
#include "TimeAtomicUnits.h" /// The time units are used by both systems.
#include "SI.h"
#pragma once

namespace AT = SystemOfUnits::Time::AtomicUnit;

// contains units based on the tradional unit types
namespace English
{
   namespace AU = AtomicUnit;

   typedef Metric::AtomicUnit::kelvin K;
   typedef Metric::AtomicUnit::coulomb coulomb;

   /// Using the Type factory where all the English types have the same base unit types.
   typedef SOU::MakeType< AU::Foot, AT::second, AU::Slug, K , coulomb > MakeEnglish;

   typedef MakeEnglish::MakeDim<1, 0, 0,0,0>::type t_foot; /// Foot type
   typedef MakeEnglish::MakeDim<0, 1, 0,0,0>::type t_second; /// Second type (test should be made against Metric type)
   typedef MakeEnglish::MakeDim<0, 0, 1,0,0>::type t_slug; /// Slug type.  Mass unit for the old engish unit system
   typedef MakeEnglish::MakeDim<1,-1, 0,0,0>::type t_FPS;   /// Feet per second.  First order deriviative
   typedef MakeEnglish::MakeDim<1,-2, 0,0,0>::type t_FPSS; /// Feet per second second.  Second order derviative

   typedef SOU::unitType< AU::Mile, 1, AT::second, 0, AU::Slug, 0, K, 0, coulomb, 0 > t_mile; /// Mile Type
   typedef SOU::unitType< AU::Mile, 1, AT::second,-1, AU::Slug, 0, K, 0, coulomb, 0 > t_mps; /// Miles per Second Type
   typedef SOU::unitType< AU::Mile, 1, AT::hour, -1, AU::Slug, 0, K, 0, coulomb, 0 > t_mph;/// Miles per Hour Type

   typedef SOU::unitType< AU::Yard, 1, AT::hour, -1, AU::Slug, 0, K, 0, coulomb, 0 > t_yard; /// Yard Type

}
#endif
// Copyright © 2005-2015 "Curt" Leslie L. Martin, All rights reserved.
// curt.leslie.lewis.martin@gmail.com
//
// Permission to use, copy, modify, and distribute this software for any
// purpose is hereby granted without fee, provided that this copyright and
// permissions notice appear in all copies and derivatives.
//
// This software is provided "as is" without express or implied warranty.
