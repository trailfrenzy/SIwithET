#include <gtest/gtest.h>
#include "list.hpp"
#include "Struct_Symbol.h"
#include "WhatAmI.h"

template< int D > struct t_Test 
{ 
   enum { DIM = D }; 
   template< typename OUT> friend static OUT &operator<<(OUT &out, t_Test<D> )
   {
      return out << D;
   }
};

using myList = Meta::LIST5<t_Test<10>, t_Test<23>, t_Test<4>, t_Test<2>, t_Test<9> >::TYPE ;

template <class a, class b> struct ORD {
   enum { VALUE = a::DIM > b::DIM };
};

TEST(MetaList, UnSortedInt) {
   std::stringstream strm;
   Meta::ListPrinter<myList>::print(strm);
   EXPECT_EQ( strm.str(), "10, 23, 4, 2, 9");
}

TEST(MetaList, SortedInt) {
   std::stringstream strm;
   Meta::ListPrinter< Meta::SORT<ORD, myList>::TYPE >::print(strm);
   EXPECT_EQ(strm.str(), "23, 10, 9, 4, 2");
}

using LENGTH = SystemOfUnits::helpers::T_Symbol<'L'>;
using MASS = SystemOfUnits::helpers::T_Symbol<'M'>;
using Len1 = SystemOfUnits::helpers::t_BaseDim< LENGTH, 1 >;

TEST(MetaList, PrintSymbol) {
   EXPECT_EQ(std::string("[L]"), LENGTH::Symstr() ) << "Ensure base print works";
   EXPECT_EQ(std::string("[M]"), MASS::Symstr());
}

TEST( MetaList, PrintBaseDim) {
   EXPECT_EQ(std::string("[L]"), Len1::t_BaseUnit::Symstr());
   EXPECT_EQ(std::string("[L]"), Len1::c_str());
}

// From "Modern C++ Design", Andrei Alexandrescu, section 3.6
template< typename L, unsigned Index > struct At;

template< class Head, class Tail > 
struct At< Meta::LIST<Head,Tail>, 0> 
{
   using RET = Head;
};

// /*
template< class Head, class Tail, unsigned Index >
struct At< Meta::LIST<Head,Tail>, Index >
{
   typedef typename At< Tail, Index - 1>::RET RET;
};
// */

TEST(MetaList, ListAtZero ) {
   using t_Sorted = Meta::SORT<ORD, myList>::TYPE;
   using t_num0 = At< t_Sorted, 0 >::RET;
   EXPECT_EQ(t_num0::DIM, 23);
   using t_numUn = At< myList, 0 >::RET;
   EXPECT_EQ(t_numUn::DIM, 10) << "before the sort";
}

TEST(MetaList, ListAtFirst) {
   using t_Sorted = Meta::SORT<ORD, myList>::TYPE;
   using t_num1 = At< t_Sorted, 1 >::RET;
   EXPECT_EQ(t_num1::DIM, 10);
}

TEST(MetaList, ListAtForth) {
   using t_Sorted = Meta::SORT<ORD, myList>::TYPE;
   using t_num4 = At< t_Sorted, 4 >::RET;
   EXPECT_EQ(t_num4::DIM, 2);
}

TEST(MetaList, SizeSorted) {
   using t_Sorted = Meta::SORT<ORD, myList>::TYPE;
   EXPECT_EQ(t_Sorted::LENGTH, 5);
}