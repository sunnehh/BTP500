/**************************************************/
/*                                                */
/*  Lab 2 Starter file                            */
/*                                                */
/*  Name:                                         */
/*  Student number:                               */
/*                                                */
/**************************************************/

/* remember to code these in a RECURSIVE only manner*/


#include "timer.h"
#include <iostream>
using namespace std;



unsigned long long factorial (unsigned int n){
	// base case 0! = 1;
	if (n == 0) {
		return 1;
	}
	else
	{
		return n*factorial(n - 1);
	}
}

unsigned long long power (unsigned int base, unsigned int n){
	// base case
	if (n == 0)
	{
		return 1;
	}
	else
	{
		return base * power(base, n - 1);
	}
}
unsigned long long fibonacci (unsigned int n){
	//base case 1
	if (n == 0)
	{
		return 0;
	}
	//base case 2;
	else if (n == 1) {
		return 1;
	}
	else
	{
		return fibonacci(n - 2) + fibonacci(n - 1);
	}
}

