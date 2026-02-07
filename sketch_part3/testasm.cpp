#include "testasm.h"

/* the attribute "used" tells the compiler to not inline this function */
__attribute__((used))
unsigned int testasm(unsigned char a, unsigned char b) {
  unsigned int out;

  asm volatile (R"(

   rjmp start_of_assembly

   .data
   ; any data values/static storage can go here

   .text

; ----------------------------------------------------------------------------------------------------------------------
; STACK LAYOUT

; For a call fib(n), the stack frame evolves like so:
; Initial (upon entry):
;     [ return address pushed by caller ]        ← SP
; After "push r24":       (save original n)
;     [ return addr ]
;     [       n      ]                           ← SP
; During fib(n-1):
; The CALL to fib pushes another return address:
;     [ return addr for caller fib ]
;     [ original n ]
;     [ return addr for fib(n-1) ]               ← SP
;     After completion, fib(n-1) returns fib(n-1) in r24.
; Then "push r24":       (push fib(n-1))
;     [ return addr for caller fib ]
;     [ original n ]
;     [     fib(n-1) ]                           ← SP
; The sequence "pop r25" and "pop r24":
;     - r25 ← fib(n-1)
;     - r24 ← original n
;     After these POPs the manual portion of the frame is cleared, leaving only the return address pushed by CALL.
; During fib(n-2):
;     We push r25 (fib(n-1)):
;     [ return addr for caller fib ]
;     [     fib(n-1) ]                           ← SP
;     The CALL to fib pushes another return address:
;     [ return addr for caller fib ]
;     [ fib(n-1) ]
;     [ return addr for fib(n-2) ]               ← SP
; After fib(n-2) returns:
;     pop r25 restores fib(n-1).
;     Stack again returns to:
;     [ return addr ]                             ← SP
; After the final ADD, RET pops the return address and returns.
; ----------------------------------------------------------------------------------------------------------------------

start_of_assembly:
   ; r24 = a, r25 = b
   mov r24,%1
   mov r25,%2  ; IGNORE



fib:
   ; 0. Base cases: if n == 0 or n == 1, return n
   cpi r24, 0
   breq fib_base                                   ; if n == 0, ret 0
   cpi r24, 1
   breq fib_base                                   ; if n == 1, ret 1


   ; 1. Recursive case: fib(n) = fib(n-1) + fib(n-2)
   ; save original n on the stack
   push r24                                        ; stack: [n]

   ; compute fib(n-1)
   dec r24                                         ; r24 = n-1
   call fib                                        ; returns fib(n-1) in r24

   ; save fib(n-1) and recover original n
   push r24                                        ; stack: [n, fib(n-1)]
   pop r25                                         ; r25 = fib(n-1), stack: [n]
   pop r24                                         ; r24 = n, stack: []

   ; compute fib(n-2)
   subi r24, 2                                     ; r24 = n-2
   push r25                                        ; save fib(n-1) on stack: [fib(n-1)]
   call fib                                        ; returns fib(n-2) in r24, stack: [fib(n-1)]
   pop r25                                         ; r25 = fib(n-1), stack: []

   ; add fib(n-1) + fib(n-2)
   add r24, r25                                    ; r24 = fib(n-1) + fib(n-2)
   ; fall through to fib_base to finish

fib_base:
   ; r24 already holds the correct result (0, 1, or fib(n))
   clr r25
   ret



end_of_assembly: 
   ; -- move r25:r24 to the 16-bit word in variable out
   movw %0,r24

)" : "=w" (out)  /* out is %0, and a 16-bit variable that is modified
		    by the assembly language */
   : "r" (a), "r" (b)  /* a is %1, b is %2, both are register-sized
			  variables */
   : "r25", "r24");   /* r24, r25 are modified by this assembly
			 language fragment */

  return out;
}
