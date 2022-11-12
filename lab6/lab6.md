Sunny Qi -
Alex Cucos - 

# Part A

1) Speaker was trying to improve insertion sort
2) threshhold of 32
3) threshhold of 16
4) The speaker stated that although the metrics were improved, the time was worse
	The reason stated was because branch prediction was not possible with Binary search, with a fail rate of 50%. With insertion sort, branch prediction can be more accurate with a success rate of 87.5%
5) Branch prediction is a technique in computer archetecture predict the outcome of a comparison and optimize for that outcome.
6) Information entropy here is referring to the amount of information that has to be extracted. The average amount of information that is revealed by insertion sort is less than binary search
7) In binary arithmetic, the rightmost bit determines even or odd. Since binary is base 2, the rightmost bit being 2^0 determines whether the number is even or odd. 
size & 1 is true when size is odd. thus adding 1 to the total will prevent splitting the array at the same index, preventing comparing the same number twice.
8) Make heap guarantees that the first element in the array is the minimum element. Unguarded sort does not check bounds. i.e. it gaurantees that the element being compared is larger than the first element
9) Using arithmetic in-line refers to relying on the binary characteristic of bool.
ie instead of doing:
	 if(size % 2 == 1)
	 	size + 1
do this:
	size += (size & 1)

10) GNU's implementation causes the worst-case scenario when the smallest element is the last element. The speaker called this the rotated data set 
11) The author describes the missing metric as measuring the average distance between two subsequent array accesses, D(n).
12) The speaker means that each individual line in the code is short and concise.
He gives the example of the linux kernal having a max line length of 80 characters.
13) Hot code is code which is called extremely often and/or is expensive to run, while cold code is the opposite. He recommends not to mix hot and cold code to maximize efficiency.

# Part B
### Random
![image](https://user-images.githubusercontent.com/26829551/201447527-3ef7df64-a62c-4657-9f99-da6090a29fd4.png)

### Reversed
![image](https://user-images.githubusercontent.com/26829551/201447777-cad442df-c473-4c33-9b61-5b853ea64202.png)

### Organ Pipe
![image](https://user-images.githubusercontent.com/26829551/201447867-afeda6be-2a8f-4411-b959-61b52cf95d3a.png)

#### sorted and rotated are ommitted because it shows 0 for all data.



## C

1. Our team attempted to do all of the micro-optimizations described; however, we did not make use of the infinite loops and jump statements, nor the excessive breaking. Since we are not as experienced in following the thought proccess of an experienced C++ developerm, keeping track of how to exit the loops when using all of the miccro-optimizations made debugging unreasonable. Thus, I decided to implement the clasic versions using my own coding style
2. The most difficult thing to understand was the idea of informational entropy. Since we did not learn the nuance of informational entropy, it didn't make sense that some methods of viewing data were "more expensive" than others
