## Power
```cpp
unsigned long long power (unsigned int base, unsigned int n){
	// base case
	if (n == 0)                                       // 1
	{
		return 1;                                       // 1
	}
	else                                              // 1
	{
		return base * power(base, n - 1);               // 1n
	}
}
```
$f(n) = n+3 \in O(n)$


## Factorial
```cpp
unsigned long long factorial (unsigned int n){
	// base case 0! = 1;
	if (n == 0) {                                     // 1
		return 1;                                       // 1
	}
	else                                              // 1
	{
		return n*factorial(n - 1);                      // 1n
	}
}
```
$f(n) = n+3 \in O(n)$

## proof
wts: $f(n) = n+3 \in O(n)$
---

$f(n) \in O(g(n))$

if $f(n) \le C \cdot g(n)$  $\forall n \ge k$ where C and k are positive

ie. $\dfrac{f(n)}{g(n)} \le C$ &emsp;&emsp;&emsp;&emsp; $\forall n \ge k$ where $k \in \mathbb{N}$

choose k = 1 $\because$ lowest k $\in \mathbb{N}$

$\dfrac{n+3}{n}  \le C$ &emsp;&emsp;&emsp;&emsp; $\forall n \ge 1$

$\dfrac{n+3}{n} \lt \dfrac{n+3n}{n} \le C$ &emsp;&emsp;&emsp;&emsp; $\forall n \ge 1$

sub n = 1

$\dfrac{n+3}{n} \lt \dfrac{(1) + 3(1)}{(1)} \le C$ &emsp;&emsp;&emsp;&emsp; $\forall n \ge 1$

Choose C = 4 $\therefore$ $f(n)$ $\in$ $O(n^2)$


## Fib questions
1. it was easier to write fibonacii using recursion. It is simply restating the mathematical formula vertetam
2. The fibonacii function should belong to $O(2^n)$

    I believe this to be the case because for each case where $n > 2$ the function is making 2 function calls for each 1 increase of n
3. 
    ![image](https://user-images.githubusercontent.com/26829551/192168518-394085db-5bb5-48e2-bc80-fd36710eafaa.png)

    This result is in line with my original hypothesis


