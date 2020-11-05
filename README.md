 # Introduction:
 
 The **Systems Of Units (SOU)** Library was created out the author's desire to solve a problem with C++ strong type definitions where
 known engineering and scientific unit types will not mix to produce the wrong result type.  The library
 automatically enforces the Principle of Dimensional Homogeneity through strong type definitions and completes unit conversions during compile time or
 will produce a compile time error if types are used incorrectly.  Violating the Principle of Dimensional Homogeneity
 will force a compliation error.  The end result is all strong types are the same size as built in types such as float or double during runtime.

The **SOU** library has evovled over the years with the use of C++ language updates.  This current version takes advantage of the concepts offered in C++20.  Future plans for the code include the use of modules.

**Homogeneity Principle of Dimensional Analysis Principle of Homogeneity states that dimensions of each of the terms of a dimensional equation on both sides should be the same. This principle is helpful because it helps us convert the units from one form to another.**

## Dimensional Analysis
We quantify the size and shape of things using Dimensional Analysis. It helps us study the nature of objects mathematically. It involves lengths and angles as well as geometrical properties such as flatness and straightness. The basic concept of dimension is that we can add and subtract only those quantities that have the same dimensions. Similarly, two physical quantities are equal if they have the same dimensions.

## Dimensional Analysis Explained
The study of the relationship between physical quantities with the help of dimensions and units of measurement is termed as dimensional analysis. Dimensional analysis is essential because it keeps the units the same, helping us perform mathematical calculations smoothly. 

Any physically meaningful equation (and any inequality) will have the same dimensions on its left and 
 right sides, a property known as dimensional homogeneity. Checking for dimensional homogeneity is a 
 common application of dimensional analysis, serving as a plausibility check on derived equations and 
 computations. It also serves as a guide and constraint in deriving equations that may describe a 
 physical system in the absence of a more rigorous derivation.

 The library provides strong type-checking of different unit types at compile time.  It does not wait for
 runtime to find errors from dimensional homogenity but will force the compiler to find these violations.

 When writing code to solve an engineering problem it is hard to find what the units are envolved in
 the equation and if the equation cancels out the incorrect units.  For example, what is the unit 
 for the following varible:

 `double x = 3.0;`
 
Is it in feet or meters?  Is Knots or Kilometers per Hour?  Or is it in grams or Kelvin?
 If the types can be enforced at compile time where only meters would work with meters and
 grams would only work with grams.

 For example:

 `Meter x = 4.0; // Meter is a strong typedef`

 `Meter y = 3.0;`

 `Meter xy = x + 3;  // 3 is a built in type (will force compliation error)`

 The compiler will allow two different measurements that are meters to be summed toegethor.
 It will not allow the following:

 `Meter m = 4.0;`
 
`Feet ft = 10;`

 `meter xy = m + ft; // will force a compliation error`

 However the following will compile:

 `meter xy = m + conversion_cast<Meter>(ft);`

## The International System of Units (SI)

The recommended practical system of units of measurement is the International System of Units *(Système International d'Unités)*, with the international abbreviation SI.  The SI is defined by the [SI Brochure](https://www.bipm.org/en/publications/si-brochure/), which is published by the BIPM (Bureau International des Poids et Measures).

SI has 7 base units (time, length, mass, electric current, thermodynamic temperature, amount of susbance, luminous intensity).  The [base units](https://www.bipm.org/en/measurement-units/) are defined here in more detail.  The current version of the **System Of Units (SOU)** library only represents 5 of 7 base units (time, length, mass electric current, thermodynamic temperature) with the other two planned for future releases of the library.

# Use of the SOU Library
SOU is open software with a "as is" without express or implied warranty license.

The library is all headers and requires not libraries to install. If using the test code which has its own seperate compliation units will requires the Google Test Framework.

To first use the library include the following file:

`#include "SystemOfUnits.h"  // inside the include directory`

Include which Measurment system you desire. The library currently only provides two, Metric and US-Standard.

For the Metric System:

`#include "MetricTypes.h"  // the type prefered by the author`

For the US Standard:

`#include "EnglishTypes.h"`

Both libraries include sets of predifined types for use with a C++20 compiler.

A users first unit types may looke something like this:
`Metric::t_meter m = 4.0;`

`Metric::t_second s = 12.0;`

`auto ms = m/s;`

To print out the display for our meter per seccond varible the following is needed:

`std::cout <<  SOU::units << ms << '\n'; `

**"3 meter*second^(-1)"**

While at the same time the following is supported as a compile time check:

`static_assert(!std::is_same<decltype(s), decltype(m)>::value);`

`static_assert(!std::is_same<decltype(ms), decltype(m)>::value);`

`static_assert(!std::is_same<decltype(ms), decltype(s)>::value);`
 
While at the same time the Meter per Second type is the same size as a double:

`   static_assert(sizeof(ms) == sizeof(double));`

## Creating your own Unit Types

The easist way for a user to create their own unit type is to use the `MakeDim<>` template provided in each of the libraries.  For example to make the SI Unit of Force, the Newton, the following is used:

`using t_Newton = t_MakeType::MakeDim<1, -2, 1, 0, 0 >::type;`

To create the SI Unit of Energy, the Joule, the following is used:

`using t_Joule = t_MakeType::MakeDim<2, -2, 1, 0, 0>::type;`

Or another option is to let the compiler create the Joule type for you:

`	constexpr Metric::t_meter m{ 5.0 };`

`	constexpr Metric::t_second s(0.5);`

`	constexpr Metric::t_kilogram kg{ 4.0 };`

`	auto const joule = m * m * kg / (s * s);`

The possibilities are endless in the use of this library.

## Derived Units and User Derived Literals (UDL)

Derived Units are constructed as products of powers of the base units.
Anoter simple way to use a unit type is through C++ UDLs offered in header file `DerivedUnits.h`.

For example to automatically create a Joule for use with the above mentioned header add the following in your code:

`using namesapce SystemOfUnits::literals;`

`auto joule = 400.0_joule; \\ automatically creates a Joule from the header DerivedUnits.h`

## Writing functions which have a UnitType for an argument

For some reason was unable to use concepts as function arguments using VS C++20.
the following worked as a function using UnitTypes for arguments.

`template <SystemOfUnits::UnitSpecies T, SystemOfUnits::UnitSpecies U> `

`auto SomeFunction(T t, U u){`

`   return t * u;  // do a lot more but simple for the example.`

`}`





