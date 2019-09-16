 Introduction:
 The Systems Of Units (SOU) Library was created out the author's desire to solve a problem where
 known engineering and scientific unit types will not mix to produce the wrong result type.  The library
 automatically enforces Dimensional Homogeneity and completes unit conversions during compile time or
 will produce a compile time error if types are used incorrectly.

 Any physically meaningful equation (and any inequality) will have the same dimensions on its left and 
 right sides, a property known as dimensional homogeneity. Checking for dimensional homogeneity is a 
 common application of dimensional analysis, serving as a plausibility check on derived equations and 
 computations. It also serves as a guide and constraint in deriving equations that may describe a 
 physical system in the absence of a more rigorous derivation.

 The library provides strong type-checking of different unit types at compile time.  It does not wait for
 runtime to find errors the compiler will detect.

 When writing code to solve an engineering problem it is hard to find what the units are envolved in
 the equation and if the equation cancels out the incorrect units.  For example, what is the unit 
 for the following varible:
 @code double x = 3.0; @endcode
 Is it in feet or meters?  Is Knots or Kilometers per Hour?  Or is it in grams or Kelvin?
 If the types can be enforced at compile time where only meters would work with meters and
 grams would only work with grams.

 For example:
 @code meter x = 4.0; // meter is a typedef
 meter y = 3.0;
 meter xy = x + 3; @endcode
 The compiler will allow two different measurements that are meters to be summed toegethor.
 It will not allow the following:
 @code meter x = 4.0;
 feet y = 10;
 meter xy = x + y; // error @endcode
 However the following would work:
 @code meter xy = x + conversion_cast<meter>(y); @endcode
