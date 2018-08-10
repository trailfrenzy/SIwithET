#ifndef UNIT_TYPE_TEMPLATE_HELPER_INCLUDE_H_
#define UNIT_TYPE_TEMPLATE_HELPER_INCLUDE_H_
#pragma warning( disable : 4091 )  

namespace SystemOfUnits
{

      /** \brief The struct is from "Generative Programming", pg 409 
	  */
	  template<bool condition, typename THEN, typename ELSE> struct IF
	  {
		  //typedef THEN RET;
		  using RET = THEN;
	  };

	  template<typename THEN, typename ELSE>struct IF<false, THEN, ELSE >
	  {
		  //typedef ELSE RET;
		  using RET = ELSE;
	  };

	  template<class T, class U> struct is_same 
	  {
		  enum{ value = false };
	  };

	  template<class T> struct is_same<T, T> 
	  {
		  enum{ value = true };
	  };

	  template <bool x> struct STATIC_ASSERTION_FAILURE;

	  template <> struct STATIC_ASSERTION_FAILURE<true> { enum { value = true }; };
}

#endif
