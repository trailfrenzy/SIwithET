/** These helper structures for compile time branching were provided in the Boost libraries but the author did not want to include Boost in the build for only these features were required.
*/
#ifndef UNIT_TYPE_TEMPLATE_HELPER_INCLUDE_H_
#define UNIT_TYPE_TEMPLATE_HELPER_INCLUDE_H_
// #pragma warning( disable : 4091 )  
#include <type_traits>
//#include <tuple>
//#include <utility> // for tuple_sort

namespace SystemOfUnits
{
      /** \brief The struct is from "Generative Programming", pg 409 
	  */
	  template<bool condition, typename THEN, typename ELSE> struct IF
	  {
		  using RET = THEN;
	  };

	  template<typename THEN, typename ELSE>struct IF<false, THEN, ELSE >
	  {
		  using RET = ELSE;
	  };


	  namespace TL 
	  {
#ifdef DO_NOT_USE_YET
		  /// used during the sort
		  template< int DIM, typename T> struct Atom 
		  {
			  enum { eDIM = DIM };
			  using t_AtomicType = T;
		  };

        template <class T, class U>
		  struct descending : std::conditional_t<( U::eDIM < T::eDIM ), std::true_type, std::false_type>
		  {};

		/// https://codereview.stackexchange.com/questions/131194/selection-sorting-a-type-list-compile-time
		/// swap types at index i and index j in the template argument tuple
		  template <std::size_t i, std::size_t j, class Tuple>
		  class tuple_element_swap
		  {
			  template <class IndexSequence>
			  struct tuple_element_swap_impl;

			  template <std::size_t... indices>
			  struct tuple_element_swap_impl<std::index_sequence<indices...>>
			  {
				  using type = std::tuple< std::tuple_element_t<
					  indices != i && indices != j ? indices : indices == i ? j : i, Tuple
					  >...
					  >;
			  };

		  public:
			  using type = typename tuple_element_swap_impl
				  <
				  std::make_index_sequence<std::tuple_size<Tuple>::value>
				  >::type;
		  };

		  // selection sort template argument tuple's variadic template's types
		  template <template <class, class> class Comparator, class Tuple>
		  class tuple_selection_sort
		  {
			  // selection sort's "loop"
			  template <std::size_t i, std::size_t j, std::size_t tuple_size, class LoopTuple>
			  struct tuple_selection_sort_impl
			  {
				  // this is done until we have compared every element in the type list
				  using tuple_type = std::conditional_t
					  <
					  Comparator
					  <
					  std::tuple_element_t<i, LoopTuple>,
					  std::tuple_element_t<j, LoopTuple>
					  >::value,
					  typename tuple_element_swap<i, j, LoopTuple>::type, // true: swap(i, j)
					  LoopTuple                                           // false: do nothing
					  >;

				  using type = typename tuple_selection_sort_impl // recurse until j == tuple_size
					  <
					  i, j + 1, tuple_size, tuple_type // using the modified tuple
					  >::type;
			  };

			  template <std::size_t i, std::size_t tuple_size, class LoopTuple>
			  struct tuple_selection_sort_impl<i, tuple_size, tuple_size, LoopTuple>
			  {
				  // once j == tuple_size, we increment i and start j at i + 1 and recurse
				  using type = typename tuple_selection_sort_impl
					  <
					  i + 1, i + 2, tuple_size, LoopTuple
					  >::type;
			  };

			  template <std::size_t j, std::size_t tuple_size, class LoopTuple>
			  struct tuple_selection_sort_impl<tuple_size, j, tuple_size, LoopTuple>
			  {
				  // once i == tuple_size, we know that every element has been compared
				  using type = LoopTuple;
			  };

		  public:
			  using type = typename tuple_selection_sort_impl
				  <
				  0, 1, std::tuple_size<Tuple>::value, Tuple
				  >::type;
		  };

		  template<typename T, typename U> struct Typelist
		  {
			  using Head = T;
			  using Tail = U;
		  };

		  struct NullType { enum { eDIM = -99999 }; };
#endif

     }

	  //typedef double t_meter;
	  //typedef double t_sec;
	  //typedef double t_gram;
	  //using sortList = TL::Typelist< TL::Atom< 3, t_meter>, TL::NullType >;
	  //using myList = TL::Typelist < TL::Atom< -1, t_meter >, TL::Typelist< Atom< 2, t_sec >, TL::TypeList< Atom< 3, t_gram >, TL::NullType > > >;

	  /// less-than needed for compile time sort
	  //template< class TList > struct Sort
	  //{


	  //};
}

#endif
