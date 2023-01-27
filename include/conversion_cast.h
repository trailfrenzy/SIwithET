/** Provides the UnitType's a way to convert from one type to another with
   compile time error checking to check the dimensions.  Enforces Dimensional Homogeneity even when casting from the English System of units to the Metric System of units.  Fuction converstion_cast<> will not violate Dimensional Homogeneity.
   Cannot convert from length to velocity.
   conversion_cast<> is used like the a static_cast<>.

   For example:@code
   Metric::t_centimeter cent(20.0);
	Metric::t_meter meter = SystemOfUnits::conversion_cast<Metric::t_meter>( cent ); @endcode

   The above is an example on how to convert from 20 centimeters to 0.2 meters.

*/
#ifndef SI_CONVERSION_CAST_H_INCLUDE
#define SI_CONVERSION_CAST_H_INCLUDE

#pragma once
#include "SI.h" /// need to know about
#include "template_help.h"
#include "pow.h"	/// template that does the pow at compile time

namespace SystemOfUnits
{
   /// function returns true if both inputs have the same dimensions, else will compiler error.  Was in conversion_cast<> but pulled it out to allow use by other users.
   template< typename LF, typename RT >
   constexpr bool dimensions_same_assert() noexcept
   {
      /** Used in the static assertion to ensure that all types are of the same type.
      You would not want to compare meter^2 from feet^3.  The dimensions are not the same. */
      static_assert(LF::eL == RT::eL, "Length not the same. See next line of error output for location.");
      static_assert(LF::et == RT::et, "Time not the same. See next line of error output for location.");
      static_assert(LF::eM == RT::eM, "Mass not the same. See next line of error output for location.");
      static_assert(LF::eT == RT::eT, "Temp not the same. See next line of error output for location.");
      static_assert(LF::eQ == RT::eQ, "Charge not the same. See next line of error output for location.");
	  static_assert(LF::eN == RT::eN, "Substance not the same. See next line of error output for location.");
	  static_assert(LF::eJ == RT::eJ, "Luminous not the same. See next line of error output for location.");
      return true;
   }

   /// Returns true if the two UnitTypes have the same diminsions.
   template< typename LF, typename RT >
   constexpr bool dimensions_same() noexcept
   {
      return (LF::eL == RT::eL && LF::et == RT::et && LF::eM == RT::eM && LF::eT == RT::eT && LF::eQ == RT::eQ && LF::eN == RT::eN && LF::eJ == RT::eJ);
   }

	/** Template used to convert between different types that have the same dimensions.
	UnitType conversion is done at compile time, while the conversion of a value may take place at runtime if not know at compile time.
	@param IN is the current UnitType converted from.
	@return OUT the new UnitType which is converted to.
	*/
	template< SystemOfUnits::UnitSpecies OUT, SystemOfUnits::UnitSpecies IN >
	constexpr OUT conversion_cast(IN const &in)
      noexcept(noexcept(OUT) && noexcept(IN))
	{
      static_assert( dimensions_same_assert< OUT, IN >(), "Dimensions of the two types are not the same");

		/// Use the incoming types as the base types.
		enum { eL = IN::eL, et = IN::et, eM = IN::eM, eT = IN::eT, eQ = IN::eQ, eN = IN::eN, eJ = IN::eJ };

		// set the value to the incoming scaler before correcting the value
      typename OUT::t_float out{ in.amount() };

		using namespace helpers;

		// correct the length
		if constexpr(0 != eL && !std::is_same_v< typename OUT::Length, typename IN::Length> ) {
			out *=
				P< MakeFrom< typename OUT::Length > >::thePower<eL>::toBase() // converts the outgoing to the base unit
				* P< typename IN::Length >::thePower<eL>::toBase();         // converts the incoming to the base unit
		}
		// correct the time
		if constexpr (0 != et && !std::is_same_v< typename OUT::Time, typename IN::Time> ) {
			out *=
				P< MakeFrom< typename OUT::Time> >::thePower<et>::toBase()
				* P< typename IN::Time >::thePower<et>::toBase();
		}
		// correct the mass
		if constexpr (0 != eM && !std::is_same_v< typename OUT::Mass, typename IN::Mass> ) {
			out *=
				P< MakeFrom< typename OUT::Mass> >::thePower<eM>::toBase()
				* P< typename IN::Mass >::thePower<eM>::toBase();
		}
		// need a correct the temperature
		if constexpr (eT == 1 && !std::is_same_v< typename OUT::Temperature, typename IN::Temperature>) {
			out =  IN::Temperature::toBase(out);  // to K
			out = OUT::Temperature::fromBase(out); // from K
		}
      //else if (eT == -1) {}  // TODO: look at this in the future.
		static_assert( eT== 0 || eT==1, "Temperature dimension may only be 1 or 0" );  // TODO: correct so it may be negitive 1.

		// correct the charge
		if constexpr (0 != eQ && !std::is_same_v< typename OUT::Charge, typename IN::Charge>) {
			out *=
				P< MakeFrom< typename OUT::Charge> >::thePower<eQ>::toBase()
				* P< typename IN::Charge >::thePower<eQ>::toBase();
		}

		// correct the Substance
		if constexpr (0 != eN && !std::is_same_v< typename OUT::Substance, typename IN::Substance>) {
			out *=
				P< MakeFrom< typename OUT::Substance> >::thePower<eN>::toBase()
				* P< typename IN::Substance >::thePower<eN>::toBase();
		}

		// correct the Luminous
		if constexpr (0 != eJ && !std::is_same_v< typename OUT::Luminous, typename IN::Luminous>) {
			out *=
				P< MakeFrom< typename OUT::Luminous> >::thePower<eJ>::toBase()
				* P< typename IN::Luminous >::thePower<eJ>::toBase();
		}

		// during the return the constructor from a scalar value will be used.
      return OUT{ out };
	}
}
// Copyright © 2005-2023 "Curt" Leslie L. Martin, All rights reserved.
// curt.leslie.lewis.martin@gmail.com
//
// Permission to use, copy, modify, and distribute this software for any
// purpose is hereby granted without fee, provided that this copyright and
// permissions notice appear in all copies and derivatives.
//
// This software is provided "as is" without express or implied warranty.

#endif