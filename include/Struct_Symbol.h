// Struct supports the dimensional function. Used internally, not for use outside of SOU.
#ifndef SYSTEM_OF_UNITS_HELPERS_STRUCT_T_SYMBOL_H
#define SYSTEM_OF_UNITS_HELPERS_STRUCT_T_SYMBOL_H
namespace SystemOfUnits {
   namespace helpers {
         template<char C > struct T_Symbol 
         { 
            enum { sym = C };
            constexpr static inline char const * Symstr()
            {
               // creation of a static character string array.
               constexpr char static str[] = { '[', sym ,']', '\0' };
               return str;
            }
         };
   }
}
#endif
