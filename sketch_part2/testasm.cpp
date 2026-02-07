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

;  - These functions are NOT recursive.
;  - They do NOT push any registers manually.
;  - The only stack activity is the automatic push of the return address by CALL, and the corresponding POP by RET.

; Upon entry:
;     [ return address ]         ← SP
;     Local variables are held only in registers (r18 to r23).
;     No pushes, so RET restores return address immediately.

; ----------------------------------------------------------------------------------------------------------------------

start_of_assembly:
   ; r24 = a, r25 = b
   mov r24,%1
   mov r25,%2
   rjmp start_main



   ; FUNCTION 1
   ; unsigned int sumval(unsigned char a, unsigned char b)
   ; {
   ;    return a+b;
   ; }
   
   sumval:
      mov   r18, r24        ; r18 = a
      mov   r19, r25        ; r19 = b
      add   r18, r19        ; low byte sum in r18, Carry may set
      clr   r19             ; r19 = 0 high byte
      brcc  sum_no_carry
      inc   r19             ; put carry into high byte
   sum_no_carry:
      movw  r24, r18        ; move result into return registers r25:r24
      ret



   ; FUNCTION 2
   ; unsigned int diffval(unsigned char a, unsigned char b)
   ; {
   ;    if (a > b) {
   ;       return a-b;
   ;    }
   ;    else {
   ;       return b-a;
   ;    }
   ; }

   diffval:
      mov   r18, r24        ; r18 = a
      mov   r19, r25        ; r19 = b
      cp    r18, r19        ; compare a vs b (sets flags)
      brsh  a_ge_b          ; if a >= b, branch (unsigned compare)
      ; else path: return b - a
      mov   r20, r19        ; r20 = b
      sub   r20, r18        ; r20 = b - a
      clr   r21             ; high byte = 0 (sub never produces carry)
      movw  r24, r20        ; return value
      ret
   a_ge_b:
      ; return a - b
      mov   r20, r18        ; r20 = a
      sub   r20, r19        ; r20 = a - b
      clr   r21
      movw  r24, r20
      ret



   ; FINAL RETURN
   ; sumval(a,b) + diffval(a,b)

   start_main:
   mov   r16, r24        ; save a
   mov   r17, r25        ; save b

   ; 1. call sumval(a,b)
   mov   r24, r16
   mov   r25, r17
   call  sumval          ; returns in r25:r24
   movw  r22, r24        ; store sumval result in r23:r22

   ; 2. call diffval(a,b)
   mov   r24, r16
   mov   r25, r17
   call  diffval         ; returns in r25:r24

   ; 3. compute sumval + diffval
   add   r24, r22        ; low byte add
   adc   r25, r23        ; high byte add with carry

   rjmp  end_of_assembly



   ;  --- YOUR CODE ENDS ---
   ;      The result must be in the register pair r25:r24
   ;      You can also rjmp to the label end_of_assembly if you need to.

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
