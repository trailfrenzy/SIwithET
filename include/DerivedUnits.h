#ifndef SYSTEM_OF_UNITS_DERIVED_UNITS_H
#define SYSTEM_OF_UNITS_DERIVED_UNITS_H
#include "SI.h"

namespace SystemOfUnits
{
}

/// frequency
auto operator"" _hertz(long double d) noexcept
{
   static constexpr char const name_str[] = "hertz";
   using Type = Metric::AUMetric::MakeDim<0, -1, 0, 0, 0>::type;

   return SystemOfUnits::CoherentUnit<Type, name_str >(d);
}

/// force
auto operator"" _newton(long double d) noexcept
{
   static constexpr char const name_str[] = "newton";
   using Type = Metric::AUMetric::MakeDim<1, -2, 1, 0, 0>::type;

   return SystemOfUnits::CoherentUnit<Type, name_str >(d);
}

/// pressure, stress
auto operator"" _pascal(long double d) noexcept
{
   static constexpr char const name_str[] = "pascal";
   using Type = Metric::AUMetric::MakeDim<-1, -2, 1, 0, 0>::type;

   return SystemOfUnits::CoherentUnit<Type, name_str >(d);
}

/// energy, work, amount of heate
auto operator"" _joule(long double d) noexcept
{
   static constexpr char const name_str[] = "joule";
   using Type = Metric::AUMetric::MakeDim< 2, -2, 1, 0, 0>::type;

   return SystemOfUnits::CoherentUnit<Type, name_str >(d);
}

// TODO: add others from Table 4. Derived units "The international System of Units"


// move to MetricTypes when done testing. With the char const [] inside the function cannot be constexpr
auto operator"" _watt(long double d) noexcept
{
   static constexpr char const name_str[] = "watt";
   using Watt = Metric::AUMetric::MakeDim<2, -3, 1, 0, 0>::type;

   return SystemOfUnits::CoherentUnit<Watt, name_str >(d);
}

#endif
