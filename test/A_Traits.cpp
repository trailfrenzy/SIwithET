#include <gtest/gtest.h>
#include "SI.h"
#include "MetricTypes.h"
#include "operators.h"

typedef Metric::t_meter t_Meter;

//TEST(A_Traits, Mul_Reslut_builtins)
//{
//   static_assert(std::is_arithmetic<double>::value);
//   using type1 = SOU::operators::A_Trait< t_Meter, SOU::tNoUnit>;
//   //static_assert(type1::trait_type == SOU::operators::trait_UA, "Is the UnitType with Arithmetic");
//   //static_assert(sizeof(type1) == 1u);
//   // static_assert(type1::trait_type == SOU::operators::trait_UU, "Will fail since wrong type");
//
//   using type2 = SOU::operators::A_Trait< SOU::tNoUnit, t_Meter >;
//   //static_assert(type2::trait_type == SOU::operators::trait_AU);
//
//   using type3 = SOU::operators::A_Trait< t_Meter, t_Meter >;
//   //static_assert(type3::trait_type == SOU::operators::trait_UU);
//
//   constexpr Metric::t_meter meter( 5.0 );
//
//   SOU::operators::Mul_Result<t_Meter, SOU::tNoUnit> mulReult(meter, SOU::tNoUnit(4.0) );
//   static_assert( std::is_same< decltype(mulReult.result()), t_Meter>::value );
//
//   EXPECT_EQ(mulReult.result().amount(), 20.0);
//
//}

//TEST(A_Traits, Mul_operator_3rdIF)
//{
//   constexpr Metric::t_meter meter(5.0);
//
//   auto prod = operator*<t_Meter, double>(meter, 4.0);
//   static_assert(std::is_same<decltype(prod), t_Meter>::value);
//}

//TEST(A_Traits, Mul_operator_2ndIf)
//{
//   constexpr Metric::t_meter meter(5.0);
//
//   std::cout << SOU::Diminsion( meter) << '\n';
//   std::cout << SOU::WhatAmI(meter) << '\n';
//
//   auto prod = operator*< double, t_Meter>(4.0, meter);
//   std::cout << SOU::Diminsion( prod) << '\n';
//   std::cout << SOU::WhatAmI(prod) << '\n';
//
//   //static_assert(std::is_same<decltype(prod), t_Meter>::value, "You would think this is the same as above");
//
//   //Metric::t_meter next = meter * 5.0;
//
//   //SOU::operators::Mul_Result< t_Meter, t_Meter > mResult;
//
//}

// Copyright © 2005-2020 "Curt" Leslie L. Martin, All rights reserved.
// curt.leslie.lewis.martin@gmail.com
//
// Permission to use, copy, modify, and distribute this software for any
// purpose is hereby granted without fee, provided that this copyright and
// permissions notice appear in all copies and derivatives.
//
// This software is provided "as is" without express or implied warranty.

