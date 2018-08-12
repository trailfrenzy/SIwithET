/// Brief description.
/** Detailed description. */

// Copyright © 2005-2015 "Curt" Leslie L. Martin, All rights reserved.
// curt.leslie.lewis.martin@gmail.com
//
// Permission to use, copy, modify, and distribute this software for any
// purpose is hereby granted without fee, provided that this copyright and
// permissions notice appear in all copies and derivatives.
//
// This software is provided "as is" without express or implied warranty.

#include <gtest/gtest.h>   // $(SolutionDir)\..\..\googletest\googletest\include

int main(int argc, char **argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}