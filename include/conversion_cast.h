/** Provides the unitType's a way to convert from one type to another with
   compile time error checking to check the dimensions.   Cannot convert from length to velocity.
   Is used like the a static_cast<> that is built into the language.

   For example:@code
   Metric::t_centimeter cent(20.0);
	Metric::t_meter meter = SOU::conversion_cast<Metric::t_meter>( cent ); @endcode

   The above is an example on how to convert from 20 centimeters to 0.2 meters.

*/
#ifndef SI_CONVERSION_CAST_H_INCLUDE
#define SI_CONVERSION_CAST_H_INCLUDE

#pragma once
#include "SI.h" /// need to know about
#include "boost/type_traits/is_same.hpp"
#include "boost/static_assert.hpp"
#include "boost/mpl/if.hpp"
#include "pow.h"	/// template that does the pow at compile time

namespace SystemOfUnits
{
	/** Template used to convert between different types that have the same diminsions.
	@param IN in is what will be converted
	@return OUT the new type
	*/
	template< typename OUT, typename IN > OUT conversion_cast( IN const &in )
	{
      /** Used in the static assertion to ensure that all types are of the same type.
          You would not want to compare meter^2 from feet^3.  The diminsions are not the same. */ 
		enum { eALLDIMS_THE_SAME = IN::eL==OUT::eL && IN::et==OUT::et && IN::eM==OUT::eM && IN::eQ==OUT::eQ };

      /// Use the incoming types as the base types.
		enum { eL = IN::eL, et = IN::et, eM = IN::eM, eQ = IN::eQ };

		boost::STATIC_ASSERTION_FAILURE<eALLDIMS_THE_SAME >;

		// set the value to the incoming scalor before correcting the value
		double out( in.amount() );

		using namespace helpers;

		// correct the length
		out *=
			P< MakeFrom<OUT::Length> >::thePower<eL>::toBase() // converts the outgoing to the base unit
			* P< IN::Length >::thePower<eL>::toBase();         // converts the incoming to the base unit

		// correct the time
		out *=
			P< MakeFrom<OUT::Time> >::thePower<et>::toBase()
			* P< IN::Time >::thePower<et>::toBase();

		// correct the mass
		out *=
			P< MakeFrom<OUT::Mass> >::thePower<eM>::toBase()
			* P< IN::Mass >::thePower<eM>::toBase();

      // need a correct the tempeture

      // correct the charge
      out *=
         P< MakeFrom<OUT::Charge> >::thePower<eQ>::toBase()
         * P< IN::Charge >::thePower<eQ>::toBase();

      // during the return the constructor from a scalar value will be used.
		return out;
	}
}
// Copyright © 2005-2015 "Curt" Leslie L. Martin, All rights reserved.
// curt.leslie.lewis.martin@gmail.com
//
// Permission to use, copy, modify, and distribute this software for any
// purpose is hereby granted without fee, provided that this copyright and
// permissions notice appear in all copies and derivatives.
//
// This software is provided "as is" without express or implied warranty.

#endif

