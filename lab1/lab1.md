```cpp
void bubbleSort(int arr[],int size){            
    int tmp;                                    // + 1               
    for (int i=0; i<size-1; i++) {              // + 1 + (2n-1) + (n-1)
        for (int j=0; j<size-1-i; j++){         // * 1 + (3n-1 - (2n - 1))
            if (arr[j+1] < arr[j]) {            // + 4
                tmp = arr[j];                   // + 4
                arr[j] = arr[j+1];              // + 3
                arr[j+1] = tmp;           
            }
        }
    }
}
```

$f(n) = 2 + ((2n - 1) + (n-1)) * (1 + ((3n - 1) - (2n - 1)) + 4 + 4 + 2$

$f(n)= (3n-2)(n-1) + 16$

$f(n)= 3n^2-5n+18$


wts: $f(n)= 3n^2-5n+18 \in O(n^2)$
---

$f(n) \in O(g(n))$

if $f(n) \le C \cdot g(n)$  $\forall n \ge k$ where C and k are positive

ie. $\dfrac{f(n)}{g(n)} \le C$ &emsp;&emsp;&emsp;&emsp; $\forall n \ge k$ where $k \in \mathbb{N}$

choose k = 1 $\because$ valid for all denom $\ge$ 1

$\dfrac{3n^2-5n+18}{n^2}  \le C$ &emsp;&emsp;&emsp;&emsp; $\forall n \ge 1$

$\dfrac{3n^2-5n+18}{n^2} \lt \dfrac{3n^2-5n^2+18n^2}{n^2} \le C$ &emsp;&emsp;&emsp;&emsp; $\forall n \ge 1$

sub n = 1

$\dfrac{3n^2-5n+18}{n^2} \lt \dfrac{3(1)^2-5(1)^2+18(1)^2}{(1)^2} \le C$ &emsp;&emsp;&emsp;&emsp; $\forall n \ge 1$

Choose C = 4 $\therefore$ $f(n)$ $\in$ $O(n^2)$
