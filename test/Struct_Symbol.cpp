#include "Struct_Symbol.h"
#include <gtest/gtest.h>
#include "MetricBaseUnits.h"
#include "TimeAtomicUnits.h"
#include "Temperature.h"

TEST(Struct_Symbol, SizeOf)
{
   static_assert(sizeof(Metric::AtomicUnit::Meter) == 1);
   static_assert(sizeof(Metric::AtomicUnit::ampere) == 1);
}

TEST(Struct_Symbol, isLENGHT) {
   EXPECT_TRUE(SystemOfUnits::is_Length< Metric::AtomicUnit::Meter >::value);
   static_assert(SystemOfUnits::is_Length< Metric::AtomicUnit::Meter >::value, "Suppose to be Lenght");

   EXPECT_TRUE(SystemOfUnits::is_Length< Metric::AtomicUnit::Centimeter >::value);
   EXPECT_FALSE(SystemOfUnits::is_Length< Metric::AtomicUnit::second>::value);
   static_assert(!SystemOfUnits::is_Length< Metric::AtomicUnit::second>::value);
}

TEST(Struct_Symbol, isTIME) {
   EXPECT_TRUE(SystemOfUnits::is_Time< Metric::AtomicUnit::second>::value);
   EXPECT_TRUE(SystemOfUnits::is_Time< Metric::AtomicUnit::hour>::value);
   EXPECT_FALSE(SystemOfUnits::is_Time< Metric::AtomicUnit::Centimeter >::value);
}
TEST(Struct_Symbol, isMASS) {
   EXPECT_TRUE(SystemOfUnits::is_Mass< Metric::AtomicUnit::gram>::value);
   EXPECT_FALSE(SystemOfUnits::is_Mass< Metric::AtomicUnit::ampere>::value);
}
TEST(Struct_Symbol, isTEMPERATURE) {
   EXPECT_TRUE(SystemOfUnits::is_Temperature< Metric::AtomicUnit::kelvin>::value);
   EXPECT_TRUE(SystemOfUnits::is_Temperature< Metric::AtomicUnit::celsius>::value);
}
TEST(Struct_Symbol, isCURRENT) {
   EXPECT_TRUE(SystemOfUnits::is_Current< Metric::AtomicUnit::ampere>::value);
   EXPECT_FALSE(SystemOfUnits::is_Length< Metric::AtomicUnit::second>::value);
}

TEST(Struct_Symbol, is_SymbolForDimensionTest)
{
   static_assert(std::is_base_of< SystemOfUnits::helpers::SymbolForDimension<'L'>, Metric::AtomicUnit::Meter>::value);
   static_assert( SystemOfUnits::helpers::is_SymbolForDimension< Metric::AtomicUnit::Meter >::value );
   static_assert(SystemOfUnits::helpers::is_SymbolForDimension< SystemOfUnits::AtomicUnit::celsius >::value);
   static_assert( !SystemOfUnits::helpers::is_SymbolForDimension< double >::value);
}