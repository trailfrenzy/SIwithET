// File is used to test a MetaSorting feature used by Diminsion of units.  See namespace SystemOfUnits below. Removed code from WhatAmI.h until code is ready for production.
#include <gtest/gtest.h>
#include <type_traits>
#include "list.hpp"
#include "Struct_Symbol.h"
#include "WhatAmI.h"
#include "MetricBaseUnits.h"
#include "MetricTypes.h"

template< int D > struct t_Test 
{ 
   enum { DIM = D }; 
   template< typename OUT> friend static OUT &operator<<(OUT &out, t_Test<D> )
   {
      return out << DIM;
   }
};

// used for compile time sorting test.
using myList = Meta::LIST6<t_Test<10>, t_Test<23>, t_Test<4>, t_Test<2>, t_Test<9>, t_Test<-2> >::TYPE ;
static_assert(myList::LENGTH == 6, "Replace a run time test");


TEST(MetaList, UnSortedInt) {
   std::stringstream strm;
   Meta::ListPrinter<myList>::print(strm);
   EXPECT_EQ( strm.str(), "10, 23, 4, 2, 9, -2");
}

TEST(MetaList, SortedInt) {
   std::stringstream strm;
   Meta::ListPrinter< Meta::SORT< Meta::DIM_GT, myList>::TYPE >::print(strm);
   EXPECT_EQ(strm.str(), "23, 10, 9, 4, 2, -2") << "an example of sort at compile time";
}

TEST(MetaList, SortWithNeg) {
   using t_List = Meta::LIST5<t_Test<-10>, t_Test<23>, t_Test<4>, t_Test<2>, t_Test<9> >::TYPE;
   using t_Sorted = Meta::SORT<Meta::DIM_GT, t_List>::TYPE;
   using t_Last = Meta::At<t_Sorted, 4 >::RET;
   EXPECT_EQ(t_Last::DIM, -10);
   using t_front = Meta::At<t_Sorted, 0>::RET;
   static_assert(t_front::DIM == 23);
   static_assert(Meta::At<t_Sorted, 1>::RET::DIM == 9, "Can look at them at compile time.");
}

TEST(MetaList, ListAtZero ) {
   using t_Sorted = Meta::SORT<Meta::DIM_GT, myList>::TYPE;
   using t_num0 = Meta::At< t_Sorted, 0 >::RET;
   EXPECT_EQ(t_num0::DIM, 23);
   using t_numUn = Meta::At< myList, 0 >::RET;
   EXPECT_EQ(t_numUn::DIM, 10) << "before the sort";
}

// used several places below.
using t_MakeType = SOU::MakeType< Metric::AtomicUnit::Meter, AT::second, Metric::AtomicUnit::kilogram, Metric::AtomicUnit::kelvin, Metric::AtomicUnit::ampere >;

namespace SystemOfUnits
{
   namespace helpers
   {
      /// Solidus is the name of the slash
      using SOLIDUS = SystemOfUnits::helpers::SymbolForDimension<'/'>;

      struct base_SingleDim {};

      template< Dimensional T, int D, typename char_type = char > 
      struct t_SingleDim : public base_SingleDim
      {
         using t_BaseUnit = T;
         enum:int { DIM = D };
         enum:char unsigned { CHAR = t_BaseUnit::sym };
         using Tstring = typename std::basic_string<char_type>;

         /// Produces a string of a dimension and absolute.
         static auto c_str() noexcept(noexcept(Tstring() ) && noexcept(t_BaseUnit))-> Tstring
         {
            if constexpr (CHAR == SOLIDUS::sym) { return { CHAR }; }
            else if constexpr (DIM == 0) { return ""; } // if DIM==0 then its is dimensionless.
            else if constexpr (DIM == 1 || DIM == -1) 
            {
               return { '[', static_cast<char_type>(CHAR) ,']' };
            }
            else // greater than one add a '^' carrot
            {
               enum { absDIM = (DIM < 0) ? -1 * DIM : DIM };
               return { '[', CHAR, ']', '^', '0' + absDIM };
            }
         }
      };

      /// Added to the sorted List to display.
      using t_SingleSolidus = t_SingleDim< SOLIDUS, 0 >;

      template< typename T >
      struct is_SingleDim
      {
         constexpr static bool value = std::is_base_of< base_SingleDim, T > ::value;
      };

      template<typename T> concept SingleDimRule = is_SingleDim<T>::value;

   } // end of namespace helpers

   using t_test1 = SystemOfUnits::helpers::t_SingleDim< Metric::AtomicUnit::Meter, 2 >;
   static_assert(t_test1::DIM == 2, "Needs to match the above");
   static_assert(t_test1::CHAR == 'L');

   using t_test3 = SystemOfUnits::helpers::t_SingleDim< Metric::t_meter::Length, 2 >;
   static_assert(t_test3::DIM == 2, "Needs to match the above");

   using t_Grav = t_MakeType::MakeDim< 3, -2, -1, 0, 0 >::type;

   static_assert(std::is_constructible_v<t_Grav>);

   using t_test2 = SystemOfUnits::helpers::t_SingleDim< t_Grav::Length, t_Grav::eL >;
   using t_test4 = SystemOfUnits::helpers::t_SingleDim< t_Grav::Time, t_Grav::et >;
   using t_testMass = SystemOfUnits::helpers::t_SingleDim< t_Grav::Mass, t_Grav::eM >;
   using t_testTemp = SystemOfUnits::helpers::t_SingleDim< t_Grav::Temperature, t_Grav::eT >;
   using t_testCharge = SystemOfUnits::helpers::t_SingleDim< t_Grav::Charge, t_Grav::eQ>;
   static_assert(t_test2::DIM == t_Grav::eL);

   /// Used in sorting the dimensions below.
   template <helpers::SingleDimRule a, helpers::SingleDimRule b>
   struct ORD {
      enum :bool { VALUE = a::DIM > b::DIM };
   };

   template< UnitSpecies T > 
   inline std::string Dim(T const )
   {
       static_assert(SystemOfUnits::is_UnitType<T>::value, "Why is this not true! The concept failed");

      if constexpr (0 == T::eL && 0 == T::eM && 0 == T::et && 0 == T::eT && 0 == T::eQ) return ""; // no dim, bale out fast!
      else
      {
         using SystemOfUnits::helpers::t_SingleDim;
         using TYPE = T;

         static_assert(TYPE::Length::sym == 'L');
         using t_SingleLen = t_SingleDim< typename TYPE::Length, TYPE::eL>;
         using t_SingleTime = t_SingleDim< typename TYPE::Time, TYPE::et>;
         using t_SingleMass = t_SingleDim< typename TYPE::Mass, T::eM>;
         using t_SingleCharge = t_SingleDim< typename TYPE::Charge, TYPE::eQ >;
         using t_SingleTemp = t_SingleDim< typename TYPE::Temperature, T::eT>;

         using t_List = Meta::LIST6< t_SingleLen,  t_SingleTime,  t_SingleMass,  t_SingleTemp,  t_SingleCharge, helpers::t_SingleSolidus >::TYPE;

         using t_Sorted = typename Meta::SORT<ORD, t_List >::TYPE;
         
         using DIM0 = typename Meta::At<  t_Sorted, 0 >::RET;
         using DIM1 = typename Meta::At<  t_Sorted, 1 >::RET;
         using DIM2 = typename Meta::At<  t_Sorted, 2 >::RET;
         using DIM3 = typename Meta::At<  t_Sorted, 3 >::RET;
         using DIM4 = typename Meta::At<  t_Sorted, 4 >::RET;
         using DIM5 = typename Meta::At<  t_Sorted, 5 >::RET;

         enum :bool { isFrontNeg = DIM0::DIM <= 0, isLastNeg = DIM5::DIM < 0 };

         std::string retStr;

         if constexpr (isFrontNeg)
         {
             retStr += '1';
             retStr += DIM0::c_str();
             retStr += DIM1::c_str();
             retStr += DIM2::c_str();
             retStr += DIM3::c_str();
             retStr += DIM4::c_str();
             retStr += DIM5::c_str();
         }
         else if constexpr (not isFrontNeg and isLastNeg)
         {
             // has a '\' Solidus in string
             retStr += DIM0::c_str();
             retStr += DIM1::c_str();
             retStr += DIM2::c_str();
             retStr += DIM3::c_str();
             retStr += DIM4::c_str();
             retStr += DIM5::c_str();
         }
         else
         {
             // No '/' Solidus in the string.
             retStr += DIM0::c_str();
             if constexpr (DIM1::DIM ) retStr += DIM1::c_str();
             if constexpr (DIM2::DIM )retStr += DIM2::c_str();
             if constexpr (DIM3::DIM )retStr += DIM3::c_str();
             if constexpr (DIM4::DIM )retStr += DIM4::c_str();
             if constexpr (DIM5::DIM )retStr += DIM5::c_str();
         }
         return retStr;
      }
   };

}

using t_Joule = t_MakeType::MakeDim<2, -2, 1, 0, 0>::type;
using t_kilogram = t_MakeType::MakeDim<0, 0, 1, 0, 0>::type;

TEST(Dim, ListSort)
{
    using SystemOfUnits::helpers::t_SingleDim;
    using TYPE = t_Joule;

    using t_SingleLen = t_SingleDim< typename TYPE::Length, TYPE::eL>;
    using t_SingleTime = t_SingleDim< typename TYPE::Time, TYPE::et>;
    using t_SingleMass = t_SingleDim< typename TYPE::Mass, TYPE::eM>;
    using t_SingleCharge = t_SingleDim< typename TYPE::Charge, TYPE::eQ >;
    using t_SingleTemp = t_SingleDim< typename TYPE::Temperature, TYPE::eT>;

    using t_List = Meta::LIST6< t_SingleLen, t_SingleTime, t_SingleMass, t_SingleTemp, t_SingleCharge, SystemOfUnits::helpers::t_SingleSolidus >::TYPE;

    using t_Sorted = typename Meta::SORT<SystemOfUnits::ORD, t_List >::TYPE;

    static_assert(Meta::At<t_Sorted, 0>::RET::DIM == 2);
    static_assert(Meta::At<t_Sorted, 1>::RET::DIM == 1);
    static_assert(Meta::At<t_Sorted, 2>::RET::DIM == 0);
    static_assert(Meta::At<t_Sorted, 3>::RET::DIM == 0);
    static_assert(Meta::At<t_Sorted, 4>::RET::DIM == 0);
    static_assert(Meta::At<t_Sorted, 5>::RET::DIM == -2);
}

using LENGTH = SystemOfUnits::helpers::SymbolForDimension<'L'>;
using MassRule = SystemOfUnits::helpers::SymbolForDimension<'M'>;
using Len1 = SystemOfUnits::helpers::t_SingleDim< LENGTH, 1 >;
static_assert(Len1::DIM == 1);
static_assert(Len1::CHAR == 'L');

TEST(MetaList, PrintSymbol) {
   EXPECT_EQ(std::string("[L]"), LENGTH::Symstr() ) << "Ensure base print works";
   EXPECT_EQ(std::string("[M]"), MassRule::Symstr());
}

TEST(MetaList, PrintSymbolWchar) {
   EXPECT_EQ(std::wstring(L"[L]"), LENGTH::Symstr<wchar_t>() ) << "Ensure base print works";
   EXPECT_EQ(std::wstring(L"[M]"), MassRule::Symstr<wchar_t>());
}

TEST( MetaList, PrintBaseDim) {
   EXPECT_EQ(std::string("[L]"), Len1::t_BaseUnit::Symstr());
   EXPECT_EQ(std::string("[L]"), Len1::c_str());
}

TEST(MetaList, ListAtFirst) {
   using t_Sorted = Meta::SORT<Meta::DIM_GT, myList>::TYPE;
   using t_num1 = Meta::At< t_Sorted, 1 >::RET;
   EXPECT_EQ(t_num1::DIM, 10);
}

TEST(MetaList, ListAtForth) {
   using t_Sorted = Meta::SORT<Meta::DIM_GT, myList>::TYPE;
   using t_num4 = Meta::At< t_Sorted, 4 >::RET;
   EXPECT_EQ(t_num4::DIM, 2);
}

TEST(MetaList, SizeSorted) {
   using t_Sorted = Meta::SORT<Meta::DIM_GT, myList>::TYPE;
   EXPECT_EQ(t_Sorted::LENGTH, 6);
}

TEST(MetaList, BuildListWithUnit) {

   using T = t_Joule;
   using SystemOfUnits::t_BaseDim;

   using t_List = Meta::LIST5< t_BaseDim< typename T::Length, T::eL>, t_BaseDim< T::Time, T::et>, t_BaseDim< T::Mass, T::eM>, t_BaseDim< T::Temperature, T::eT>, t_BaseDim< T::Charge, T::eQ > >;
   EXPECT_EQ(t_List::TYPE::LENGTH, 5);
}

TEST(MetaList, SortWithUnit) {
   using T = t_Joule;
   using SystemOfUnits::t_BaseDim;

   using t_List = Meta::LIST5< t_BaseDim< t_Joule::Length, T::eL>, t_BaseDim< T::Time, T::et>, t_BaseDim< T::Mass, T::eM>, t_BaseDim< T::Temperature, T::eT>, t_BaseDim< T::Charge, T::eQ > >::TYPE;

   //using myListA = Meta::LIST5< t_BaseDim< T::Length, T::eL>, t_Test<23>, t_Test<4>, t_Test<2>, t_Test<9> >::TYPE;

   using t_Sort = Meta::SORT< Meta::DIM_GT, t_List >::TYPE;
   constexpr int x = Meta::At< t_Sort, 0 >::RET::DIM;
   EXPECT_EQ( x , 2) << "Not sure why it would not use the enum DIM";
}

TEST(Dim, CharFromSingleString) {

   using T = t_Joule;
   using SystemOfUnits::helpers::t_SingleDim;
   EXPECT_EQ(T::et, -2);

   using t_List = Meta::LIST5< t_SingleDim< T::Length, T::eL>, t_SingleDim< T::Time, T::et>, t_SingleDim< T::Mass, T::eM>, t_SingleDim< T::Temperature, T::eT>, t_SingleDim< T::Charge, T::eQ > >::TYPE;
   using t_Sorted = Meta::SORT< Meta::DIM_GT, t_List >::TYPE;

   //std::string const retStr = Meta::At< t_Sorted, 0 >::RET::c_str();
   EXPECT_EQ(std::string( Meta::At< t_Sorted, 0 >::RET::c_str() ), "[L]^2");
   EXPECT_EQ(std::string(Meta::At< t_Sorted, 1 >::RET::c_str()), "[M]");
   EXPECT_EQ( int(Meta::At< t_Sorted, 2 >::RET::DIM), 0);
   EXPECT_EQ(int(Meta::At< t_Sorted, 4 >::RET::DIM), -2);
   //EXPECT_STREQ( (Meta::At< t_Sorted, 4 >::RET::c_str()), "[T]^2");

}

TEST(WhatAmITest, TestDouble)
{
   double val = 6.7888;
   EXPECT_EQ(SOU::WhatAmI(val), std::string(""));
}

TEST(Diminsion, OneDimPrint1) {
   SystemOfUnits::helpers::t_bufPair bufPair;
   std::string temp{ SystemOfUnits::helpers::OneDim<'L', 1>(bufPair).first.str() };
   EXPECT_EQ(temp, std::string("[L]"));
   temp = SystemOfUnits::helpers::OneDim<'M', -1 >(bufPair).second.str();
   EXPECT_EQ(temp, "[M]");
}
TEST(Diminsion, OneDimPrint2) {
   SystemOfUnits::helpers::t_bufPair bufPair;
   std::string temp = SystemOfUnits::helpers::OneDim<'L', 2>(bufPair).first.str();
   EXPECT_EQ(temp, "[L]^2");
   temp = SystemOfUnits::helpers::OneDim<'M', -3 >(bufPair).second.str();
   EXPECT_EQ(temp, "[M]^3");
}
TEST(Diminsion, Struct_Sym) {
   using t_X = SystemOfUnits::helpers::SymbolForDimension<'X'>;
   EXPECT_EQ('X', t_X::sym);
}

TEST(Dim, NoDiminsion) {
   EXPECT_EQ(SystemOfUnits::Dim(SystemOfUnits::tNoUnit()), std::string_view(""));
}

TEST(Dim, InverseOne) {
   using t_Unk = t_MakeType::MakeDim< -3, -2, -1, 0, 0 >::type;
   std::string const str = SystemOfUnits::Dim(t_Unk());
   EXPECT_EQ("1/[M][T]^2[L]^3", str );
}

TEST(Dim, FirstTest ) {
   EXPECT_EQ( SystemOfUnits::Dim(t_Joule() ), "[L]^2[M]/[T]^2" ); // << "The return of Dim is: " << str;
}

TEST(Dim, Kilogram) {
    std::string const str = SystemOfUnits::Dim(t_kilogram());
    EXPECT_EQ(str, std::string_view("[M]"));
}

TEST(Dim, OneElement) {
    using t_Unk1 = t_MakeType::MakeDim< 1,0,0,0,0 >::type;
    EXPECT_EQ("[L]", SystemOfUnits::Dim(t_MakeType::MakeDim< 1, 0, 0, 0, 0 >::type()));
    EXPECT_EQ("[T]", SystemOfUnits::Dim(t_MakeType::MakeDim< 0, 1, 0, 0, 0 >::type()));
    EXPECT_EQ("[M]", SystemOfUnits::Dim(t_MakeType::MakeDim< 0, 0, 1, 0, 0 >::type()));
    EXPECT_EQ("[C]", SystemOfUnits::Dim(t_MakeType::MakeDim< 0, 0, 0, 0, 1 >::type()));
}

TEST(Dim, ThetaOrTempeture) {
    EXPECT_EQ("[\xe9]", SystemOfUnits::Dim(t_MakeType::MakeDim< 0, 0, 0, 1, 0 >::type()));  // \xE9
}


TEST(Dim, RandomType) {
    using t_Unk = t_MakeType::MakeDim< -3, -2, -1, 1, 2 >::type;
    std::string const str = SystemOfUnits::Dim(t_Unk());
    EXPECT_EQ("[C]^2[\xE9]/[M][T]^2[L]^3", str );
}



