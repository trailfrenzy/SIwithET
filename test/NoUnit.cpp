#include "SI.h"
#include <gtest\gtest.h>
//#include "MetricTypes.h"

static_assert( !SOU::is_UnitType< SOU::NoUnit>::value , "NoUnit is suppose to be a UnitType" );
static_assert(SOU::is_UnitType< SOU::tNoUnit>::value, "tNoUnit is a UnitType");

TEST(NoUnit, Constructor_tNoUnit)
{
   SOU::tNoUnit noDim( 5.0 );
   SOU::tNoUnit noDim2(7.0f);
   SOU::tNoUnit noDim3(4);
   SOU::tNoUnit noDim4(5u);
}

TEST(NoUnit, Constructor_NoUnit)
{
   SOU::NoUnit noDim1(5.0);
   SOU::NoUnit noDim2(5.2f);

   SOU::NoUnit noDim3 = 4.5f;
   SOU::NoUnit noDim4 = 5;

   SOU::NoUnit noDim5(5ll);
   SOU::NoUnit noDim6(5u);
}

//TEST(NoUnit, AddtionScaler)
//{
//   SOU::NoUnit noDim1 = 6.0;
//   auto val = noDim1 + 7.0;
//}