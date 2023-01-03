// File is used to test a MetaSorting feature used by Diminsion of units.  See namespace SystemOfUnits below. Removed code from WhatAmI.h until code is ready for production.
#include "Dimension.h"
#include <gtest/gtest.h>
#include <type_traits>
#include "list.hpp"
#include "Struct_Symbol.h"
//#include "WhatAmI.h"
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
static_assert(myList::LENGTH == 6, "Replaced a run time test");

namespace Meta
{
    // printing lists to std::cout
    template <class L> struct ListPrinter
    {
        template< typename OUT > static inline void print(OUT& out)
        {
            //return out;
            //out << std::endl;
        }
    };

    template <typename a> struct ListPrinter < Meta::LIST<a, Meta::EmptyList> >
    {
        template< typename OUT > static inline void print(OUT& out)
        {
            out << a::DIM;
            ListPrinter<Meta::EmptyList>::print(out);
        }
    };

    template <typename a, class TAIL> struct ListPrinter<Meta::LIST<a, TAIL> >
    {
        template< typename OUT> static inline void print(OUT& out)
        {
            out << a::DIM << ", ";
            ListPrinter<TAIL>::print(out);
        }
    };
}

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
   static_assert(t_List::LENGTH == 5);
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

// Used in tests below. Transfered away from having struct t_BaseDim in SI.h
template< SystemOfUnits::Dimensional T, int D >
using t_BaseDim = SystemOfUnits::helpers::t_SingleDim<T, D>;

TEST(MetaList, BuildListWithUnit) {

   using T = t_Joule;

   using t_List = Meta::LIST5< t_BaseDim< typename T::Length, T::eL>, t_BaseDim< T::Time, T::et>, t_BaseDim< T::Mass, T::eM>, t_BaseDim< T::Temperature, T::eT>, t_BaseDim< T::Charge, T::eQ > >;
   EXPECT_EQ(t_List::TYPE::LENGTH, 5);
}

TEST(MetaList, SortWithUnit) {
   using T = t_Joule;

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
    EXPECT_EQ("[I]", SystemOfUnits::Dim(t_MakeType::MakeDim< 0, 0, 0, 0, 1 >::type()));
}

TEST(Dim, ThetaOrTempeture) {
    EXPECT_EQ("[\xe9]", SystemOfUnits::Dim(t_MakeType::MakeDim< 0, 0, 0, 1, 0 >::type()));  // \xE9
}


TEST(Dim, RandomType) {
    using t_Unk = t_MakeType::MakeDim< -3, -2, -1, 1, 2 >::type;
    std::string const str = SystemOfUnits::Dim(t_Unk());
    EXPECT_EQ("[I]^2[\xE9]/[M][T]^2[L]^3", str );
}



