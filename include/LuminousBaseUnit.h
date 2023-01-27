#pragma once
#ifndef METRIC_BASE_UNIT_LUMINUS_INCLUDE_H
#include "Struct_Symbol.h"

namespace Metric::AtomicUnit
{
    struct Candela : SystemOfUnits::Luminous
    {
        enum : bool { IsBase = true };
        constexpr static char const* str() noexcept { return "candela"; }
        constexpr static double toBase() noexcept { return 1.0; }
        constexpr static double fromBase() noexcept { return 1.0; }
        using Base = Candela;
    };
}

#define METRIC_BASE_UNIT_LUMINUS_INCLUDE_H
#endif // !METRIC_BASE_UNIT_LUMINUS_INCLUDE_H

// Copyright © 2005-2023 "Curt" Leslie L. Martin, All rights reserved.
// curt.leslie.lewis.martin@gmail.com
//
// Permission to use, copy, modify, and distribute this software for any
// purpose is hereby granted without fee, provided that this copyright and
// permissions notice appear in all copies and derivatives.
//
// This software is provided "as is" without express or implied warranty.
