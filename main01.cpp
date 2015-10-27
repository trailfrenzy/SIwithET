/// Brief description.
/** Detailed description. */

#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/CompilerOutputter.h> 


/// The main() that is used to test.
int main(int argc, char** argv)
{
   // if command line contains "-selftest" then this is the post build check
   // => the output must be in the compiler error format.
   bool const selfTest = (argc > 1)  &&  
                   (std::string("-selftest") == argv[1]);

  CppUnit::TextUi::TestRunner runner;
  CppUnit::TestFactoryRegistry &registry = CppUnit::TestFactoryRegistry::getRegistry();
  runner.addTest( registry.makeTest() );

  if( selfTest )
  { 
      CppUnit::CompilerOutputter *outer = 
         new CppUnit::CompilerOutputter( &runner.result(), std::cerr );

      // set the format for the outer
      outer->setLocationFormat("%p(%l):" );

     // Change the default outputter to a compiler error format outputter
     // The test runner owns the new outputter.
     runner.setOutputter( outer );
  }

  bool const wasSucessful = runner.run( "", !selfTest );
  return wasSucessful ? 0 : 1;
}

// Copyright © 2005-2015 "Curt" Leslie L. Martin, All rights reserved.
// curt.leslie.lewis.martin@gmail.com
//
// Permission to use, copy, modify, and distribute this software for any
// purpose is hereby granted without fee, provided that this copyright and
// permissions notice appear in all copies and derivatives.
//
// This software is provided "as is" without express or implied warranty.

