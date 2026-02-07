#include "testasm.h"

/* the attribute "used" tells the compiler to not inline this function */
__attribute__((used))
unsigned int testasm(unsigned char a, unsigned char b) {
  unsigned int out;

  asm volatile (R"(

   rjmp start_of_assembly

   .data
   .text

; ----------------------------------------------------------------------------------------------------------------------
; STACK LAYOUT

; Stack at entry:
;     [ return address ]        ← SP
; Stack at exit:
;     [ return address ]        ← SP
; ----------------------------------------------------------------------------------------------------------------------

start_of_assembly:
   ; r24 = a, r25 = b
   mov r24,%1
   mov r25,%2

   add r24, r25               ; r24 = r24 + r25. If overflows 8'b, C will be set

   clr r25                    ; r25 = 0
   brcc end_of_assembly       ; if no carry, done
   inc r25                    ; else, put carry in r25

end_of_assembly: 
   ; move r25:r24 to the 16-bit word in variable out
   movw %0,r24


)" : "=w" (out)  /* out is %0, and a 16-bit variable that is modified
		    by the assembly language */
   : "r" (a), "r" (b)  /* a is %1, b is %2, both are register-sized
			  variables */
   : "r25", "r24");   /* r24, r25 are modified by this assembly
			 language fragment */

  return out;
}
