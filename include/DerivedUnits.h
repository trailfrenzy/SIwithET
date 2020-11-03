#ifndef SYSTEM_OF_UNITS_DERIVED_UNITS_H
#define SYSTEM_OF_UNITS_DERIVED_UNITS_H
#include "SI.h"

namespace SystemOfUnits
{
   /// <summary>
   /// all the literals live in this namespace.  Users have the option of using all the literals with
   /// using namespace SystemOfUnits::literals;
   /// or by using specific literals with:\
   /// using SystemOfUnits::literals::operator ""_newton;
   namespace literals
   {
      /// frequency
      inline auto operator"" _hertz(long double d) noexcept
      {
         static constexpr char const name_str[] = "hertz";
         using Type = Metric::AUMetric::MakeDim<0, -1, 0, 0, 0>::type;

         return SystemOfUnits::CoherentUnit<Type, name_str >(d);
      }

      /// force
      inline auto operator"" _newton(long double d) noexcept
      {
         static constexpr char const name_str[] = "newton";
         using Type = Metric::AUMetric::MakeDim<1, -2, 1, 0, 0>::type;

         return SystemOfUnits::CoherentUnit<Type, name_str >(d);
      }

      /// pressure, stress
      inline auto operator"" _pascal(long double d) noexcept
      {
         static constexpr char const name_str[] = "pascal";
         using Type = Metric::AUMetric::MakeDim<-1, -2, 1, 0, 0>::type;

         return SystemOfUnits::CoherentUnit<Type, name_str >(d);
      }

      /// energy, work, amount of heat
      inline auto operator"" _joule(long double d) noexcept
      {
         static constexpr char const name_str[] = "joule";
         using Type = Metric::AUMetric::MakeDim< 2, -2, 1, 0, 0>::type;

         return SystemOfUnits::CoherentUnit<Type, name_str >(d);
      }

      // TODO: add others from Table 4. Derived units "The international System of Units"


      // move to MetricTypes when done testing. With the char const [] inside the function cannot be constexpr
      inline auto operator"" _watt(long double d) noexcept
      {
         static constexpr char const name_str[] = "watt";
         using Watt = Metric::AUMetric::MakeDim<2, -3, 1, 0, 0>::type;

         return SystemOfUnits::CoherentUnit<Watt, name_str >(d);
      }

      /// electric charge
      inline auto operator"" _coulomb(long double d) noexcept
      {
         static constexpr char const name_str[] = "coulomb";
         using Type = Metric::AUMetric::MakeDim< 0, 1, 0, 0, 1>::type;

         return SystemOfUnits::CoherentUnit<Type, name_str >(d);
      }

      // electric current
      inline auto operator"" _ampere(long double d)noexcept
      {
         static constexpr char const name_str[] = "ampere";

         using Type = Metric::AUMetric::MakeDim< 0, 0, 0, 0, 1>::type;

         return SystemOfUnits::CoherentUnit<Type, name_str >(d);
      }

      /// electric potential difference 
      inline auto operator"" _volt(long double d) noexcept
      {
         static constexpr char const name_str[] = "volt";
         using Type = Metric::AUMetric::MakeDim< 2, -3, 1, 0, -1>::type;

         return SystemOfUnits::CoherentUnit<Type, name_str >(d);
      }

      /// capacitance
      inline auto operator"" _farad(long double d) noexcept
      {
         static constexpr char const name_str[] = "farad";
         using Type = Metric::AUMetric::MakeDim< -2, 4, -1, 0, 2>::type;

         return SystemOfUnits::CoherentUnit<Type, name_str >(d);
      }

      /// electric resistance
      inline auto operator"" _ohm(long double d) noexcept
      {
         static constexpr char const name_str[] = "ohm";
         using Type = Metric::AUMetric::MakeDim< 2, -3, 1, 0, -2>::type;

         return SystemOfUnits::CoherentUnit<Type, name_str >(d);
      }

      /// electric conductance
      inline auto operator"" _siemens(long double d) noexcept
      {
         static constexpr char const name_str[] = "siemens";
         using Type = Metric::AUMetric::MakeDim< -2, 3, -1, 0, 2>::type;

         return SystemOfUnits::CoherentUnit<Type, name_str >(d);
      }

      /// magnetic flux
      inline auto operator"" _weber(long double d) noexcept
      {
         static constexpr char const name_str[] = "weber";
         using Type = Metric::AUMetric::MakeDim< 2, -2, 1, 0, -1>::type;

         return SystemOfUnits::CoherentUnit<Type, name_str >(d);
      }

      /// magnetic flux density
      inline auto operator"" _tesla(long double d) noexcept
      {
         static constexpr char const name_str[] = "tesla";
         using Type = Metric::AUMetric::MakeDim< 0, -2, 1, 0, -1>::type;

         return SystemOfUnits::CoherentUnit<Type, name_str >(d);
      }

      /// inductance
      inline auto operator"" _henry(long double d) noexcept
      {
         static constexpr char const name_str[] = "henry";
         using Type = Metric::AUMetric::MakeDim< 2, -2, 1, 0, -2>::type;

         return SystemOfUnits::CoherentUnit<Type, name_str >(d);
      }
   }
}

#endif
