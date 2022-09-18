/**************************************************/
/*                                                */
/*  Lab 1 Starter file                            */
/*                                                */
/*  Name: Sunny Qi                                */
/*  Student number: 136570207                     */
/*                                                */
/**************************************************/

/* remember to code these in an iterative only manner*/
#include <iostream>

unsigned long long factorial(unsigned int n) {
   unsigned long long total = 1;

   for (int i = 1; i <= n; ++i)
   {
      total *= i;
   }

   return total;
}

unsigned long long power(unsigned int base, unsigned int n) {
   if (n == 0)
   { 
      return 1;
   }
   unsigned long long value = 1;

   for (int i = 0; i < n; i++)
   {
      value *= base;
   }
   return value;
}

unsigned long long fibonacci(unsigned int n) {
   unsigned long long n1, n2, fib;
   n1 = 0;
   n2 = 1;
   fib = 0;
   if (n >= 2)
   {
      for (int i = 1; i < n; i++)
      {
         fib = n1 + n2;
         n1 = n2;
         n2 = fib;
      }
   }
   else if (n == 0)
      return n1;
   else if (n == 1)
      return n2;

   return fib;
}