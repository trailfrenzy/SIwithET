#ifndef UNIT_TYPE_TEMPLATE_HELPER_INCLUDE_H_
#define UNIT_TYPE_TEMPLATE_HELPER_INCLUDE_H_

namespace SystemOfUnits
{

      /** \brief The struct is from "Generative Programming", pg 409 
	  */
	  template<bool condition, typename THEN, typename ELSE> struct IF
	  {
		  typedef THEN RET;
	  };

	  template<typename THEN, typename ELSE>struct IF<false, THEN, ELSE >
	  {
		  typedef ELSE RET;
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

	  template <> struct STATIC_ASSERTION_FAILURE<true> { enum { value = 1 }; };
}

#endif
