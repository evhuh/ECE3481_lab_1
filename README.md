## PART 1: Add two numbers (8-bit integers ‘a’ & ‘b’)
- GOAL:
  * Compute two 8-bit unsigned integers ‘a’ and ‘b’ where r24 =a, r25 = b
  * Result = 16-bit sum = a + b in  r25:r24 [HIGH | LOW]
  * If the 8-bit addition overflows, the carry is placed in the high byte (r25)

- INPUTS :
    * a = r24
    * b = r25

- OUTPUTS :
    * r25:r24 = 16-bit sum
       - r24 contains the low byte
       - r25 is set to 0 or 1 (depending on if carry out)

## PART 2: Add 2 functions sumval(a,b) + diffval(a,b)
- FUNCTIONS : sumval, diffval
  * FUNCTION 1: sumval(a,b) 
     - INPUTS two unsigned char a & char b then ADD them
     - RETURNS (a + b) as 16-bit unsigned
   * FUNCTION 2:diffval(a,b) 
     - INPUTS two unsigned char a & char b inputs
       * IF a greater than b, return (a - b), ELSE if a is less than or equal to b, return (b - a )
     - RETURNS |a - b| as 16-bit unsigned

- INPUTS :
  * a = r24   (unsigned char)
  * b = r25   (unsigned char)

- OUTPUTS :
  * r25:r24 holds the 16-bit unsigned result


## PART 3: Recursively compute Fibonacci(n)
- NOTE: This works for any Fibonacci number that can be represented by an 8-bit value (so up to fib(13) = 233) 

- FUNCTIONS: fib, fib_base
  * FUNCTION 1: fib
    - INPUTS :
       * n is passed in r24 (unsigned 8-bit)
    - OUTPUTS :
      * r25:r24 = 16-bit result (HIGH byte = 0)
  * FUNCTION 2: fib_base
    - Returns 1 or 0, if passed 1 or 0 (respectively) to the calling function

