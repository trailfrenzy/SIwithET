/** Provides the unitType's a way to convert from one type to another with
   compile time error checking to check the dimensions.  Enforces Dimensional Homogeneity even when casting from the English System of units to the Metric System of units.  Fuction converstion_cast<> will not violate Dimensional Homogeneity.
   Cannot convert from length to velocity.
   conversion_cast<> is used like the a static_cast<>.

   For example:@code
   Metric::t_centimeter cent(20.0);
	Metric::t_meter meter = SOU::conversion_cast<Metric::t_meter>( cent ); @endcode

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
   /// function returns true if both inputs have the same dimensions, else will crash.  Was in conversion_cast<> but pulled it out.
   template< typename LF, typename RT >
   constexpr bool dimensions_same()
   {
      /** Used in the static assertion to ensure that all types are of the same type.
      You would not want to compare meter^2 from feet^3.  The dimensions are not the same. */
      static_assert(LF::eL == RT::eL, "Length not the same");
      static_assert(LF::et == RT::et, "Time not the same");
      static_assert(LF::eM == RT::eM, "Mass not the same");
      static_assert(LF::eT == RT::eT, "Temp not the same");
      static_assert(LF::eQ == RT::eQ, "charge not the same");
      return true;
   }

	/** Template used to convert between different types that have the same dimensions.
	@param IN in is what will be converted
	@return OUT the new type
	*/
	template< typename OUT, typename IN > OUT conversion_cast(IN const &in)
	{
      dimensions_same< OUT, IN >();

		/// Use the incoming types as the base types.
		enum { eL = IN::eL, et = IN::et, eM = IN::eM, eT = IN::eT, eQ = IN::eQ };

		// set the value to the incoming scaler before correcting the value
      double out{ in.amount() };

		using namespace helpers;

		// correct the length
		if (eL) {  // check to see if compiles out when zero
			out *=
				P< MakeFrom<OUT::Length> >::thePower<eL>::toBase() // converts the outgoing to the base unit
				* P< IN::Length >::thePower<eL>::toBase();         // converts the incoming to the base unit
		}
		// correct the time
		if (et) {
			out *=
				P< MakeFrom<OUT::Time> >::thePower<et>::toBase()
				* P< IN::Time >::thePower<et>::toBase();
		}
		// correct the mass
		if (eM) {
			out *=
				P< MakeFrom<OUT::Mass> >::thePower<eM>::toBase()
				* P< IN::Mass >::thePower<eM>::toBase();
		}
		// need a correct the temperature
		if (eT == 1) {
			out =  IN::Tempeture::toBase(out);  // to K
			out = OUT::Tempeture::fromBase(out); // from K
		}
      //else if (eT == -1) {}  // TODO: look at this in the future.
		static_assert( eT== 0 || eT==1, "Tempeture dimension may only be 1 or 0" ) ;  // TODO: correct so it may be negitive 1.

		// correct the charge
		if (eQ) {
			out *=
				P< MakeFrom<OUT::Charge> >::thePower<eQ>::toBase()
				* P< IN::Charge >::thePower<eQ>::toBase();
		}
		// during the return the constructor from a scalar value will be used.
      return OUT{ out };
	}
}
// Copyright © 2005-2018 "Curt" Leslie L. Martin, All rights reserved.
// curt.leslie.lewis.martin@gmail.com
//
// Permission to use, copy, modify, and distribute this software for any
// purpose is hereby granted without fee, provided that this copyright and
// permissions notice appear in all copies and derivatives.
//
// This software is provided "as is" without express or implied warranty.

#endif