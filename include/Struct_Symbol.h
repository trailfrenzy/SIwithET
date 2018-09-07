#pragma once
#ifndef STRUCT_T_SYMBOL_H_
#define STRUCT_T_SYMBOL_H_
namespace SystemOfUnits {
   namespace helpers {
         template<char C > struct T_Symbol 
         { 
            enum { sym = C };
            static inline char const * Symstr()
            {
               constexpr char str[] = { '[', sym ,']', '\0' };
               return str;
            }
         };
   }
}
#endif
