#pragma once
#ifndef UNIT_TYPE_STREAM_INSERTERS_H
#define UNIT_TYPE_STREAM_INSERTERS_H
#include "SI.h"
#include "Dimension.h"

namespace SystemOfUnits
{
    /**
    @page 5 Stream Manipulator for SystemOfUnits::UnitType template to produce dimeninsions only for the type in the stream.
    The template for the manipulator class is based from "Advanced Metaprogramming in Classic C++" page 464 by Davide Di Gennaro ©2015. ISBN 978-1-4842-1011-6.

    Stream manipulators are one of the least known and more expressive pieces of the C++ Standard  They are simply functions which take a stream as an argument.  Since their signature is fixed, streams have a special insertion operator to run them.

    @code t_metricCube m3 = 8.2;
    std::cout << ShowDim << m3 << '\n';
    @endcode

    The output is: @code "8.2 [L]^3" @endcode

    All insertions after @code ShowDim @endcode atcually calls to @code ShowDim_t::operator<< @endcode, not to std::ostream.
    The code generates a unique signature for the manipulator with the proxy itself.  The effect of the manipulator insertion is lost after the next insertion.
    */
    /// Stream Manipulator class ShowDim_t.  
    template< class TOUT >
    class ShowDim_t
    {
        TOUT& out;  /// TOUT can be std::cout, std::ofstream, std::stringstream, or anyother stream which uses insertors.
    public:
        ShowDim_t(TOUT& r) : out(r) {}

        /// pass by value instead of reference for built in types.
        template< Arithmetic A> ShowDim_t& operator<<(A a) { out << a; return *this; }

        /// Used by the UnitType to display the acutal diminsion
        template< UnitSpecies S > ShowDim_t& operator<<(S val)
        {
            using t_unit = S; // SystemOfUnits::UnitType<L, iL, t, it, M, iM, T, iT, Q, iQ>;
            using t_char = typename TOUT::char_type;  // will not compile if TOUT does not have char_type.
            // WAS the following: out << val << ' ' << t_Diminsion<t_char, t_unit>(val);
            out << val << ' ' << SystemOfUnits::Dim(val);
            return *this;
        }

        /// Used by any type besides UnitType and Arithmetic types
        template< typename T > ShowDim_t& operator<<(const T& val)
        {
            out << val;
            return *this;
        }

        /// converts the class to the stream implicitly. Is the last function called by the stream when the Manipulator is used.
        operator TOUT& () const { return out; }
    };

    /// Actual Manipulator used in the stream. The word "dimension" is more universally accepted in other languages besides English.  Replacement for ShowDim. Use of "dimension" is better than "dim" or "ShowDim".  
    template< class TOUT > inline auto dimension() -> ShowDim_t<TOUT>* { return 0; }

}

/// function is used to impliment the stream manipulator SystemOfUnits::UnitType dimensions.  
template< class TOUT >
inline auto operator<<(TOUT& out, SystemOfUnits::ShowDim_t<TOUT>* (*)()) // -> SystemOfUnits::ShowDim_t<TOUT>
{
    return SystemOfUnits::ShowDim_t<TOUT>(out);
}


#endif // !UNIT_TYPE_STREAM_INSERTERS_H

// Copyright © 2005-2023 "Curt" Leslie L. Martin, All rights reserved.
// curt.leslie.lewis.martin@gmail.com
//
// Permission to use, copy, modify, and distribute this software for any
// purpose is hereby granted without fee, provided that this copyright and
// permissions notice appear in all copies and derivatives.
//
// This software is provided "as is" without express or implied warranty.
