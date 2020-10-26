#include "Struct_Symbol.h"
#include <gtest/gtest.h>
#include "MetricBaseUnits.h"
#include "TimeAtomicUnits.h"
#include "Temperature.h"

TEST(Struct_Symbol, isLENGHT) {
   EXPECT_TRUE(SystemOfUnits::is_LENGTH< Metric::AtomicUnit::Meter >::value) << "Suppose to be Lenght";
   EXPECT_TRUE(SystemOfUnits::is_LENGTH< Metric::AtomicUnit::Centimeter >::value);
   EXPECT_FALSE(SystemOfUnits::is_LENGTH< SystemOfUnits::Time::AtomicUnit::second>::value);
}

TEST(Struct_Symbol, isTIME) {
   EXPECT_TRUE(SystemOfUnits::is_TIME< SystemOfUnits::Time::AtomicUnit::second>::value);
   EXPECT_TRUE(SystemOfUnits::is_TIME< SystemOfUnits::Time::AtomicUnit::hour>::value);
   EXPECT_FALSE(SystemOfUnits::is_TIME< Metric::AtomicUnit::Centimeter >::value);
}
TEST(Struct_Symbol, isMASS) {
   EXPECT_TRUE(SystemOfUnits::is_MASS< Metric::AtomicUnit::gram>::value);
   EXPECT_FALSE(SystemOfUnits::is_MASS< Metric::AtomicUnit::ampere>::value);
}
TEST(Struct_Symbol, isTEMPERATURE) {
   EXPECT_TRUE(SystemOfUnits::is_TEMPERATURE< SystemOfUnits::Temperature::kelvin>::value);
   EXPECT_TRUE(SystemOfUnits::is_TEMPERATURE< SystemOfUnits::Temperature::celsius>::value);
}
TEST(Struct_Symbol, isCURRENT) {
   EXPECT_TRUE(SystemOfUnits::is_CURRENT< Metric::AtomicUnit::ampere>::value);
   EXPECT_FALSE(SystemOfUnits::is_LENGTH< SystemOfUnits::Time::AtomicUnit::second>::value);
}