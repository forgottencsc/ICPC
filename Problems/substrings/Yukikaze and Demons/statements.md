## Yukikaze and Demons

### Description

Yukikaze is facing a huge crisis!

Under the attack of a kind of demons, dragon eaters, the dragon forest is endanger. As a member of the Biscotti Knights Secret Squad, she must do something to save the dragon forest.

The road in the dragon forest forms an undirected tree. Every vertex is occupied by a demon with a type denoted by a decimal digit.

In one of her strike, she can sweep out all the enemy on the path if and only if the decimal number formed by concatenating the types of enemy on the path sequentially is divisible by a special number $k$.

The demons are destroying the forest! Time is limited, she needs to know how many path in the dragon forest can be cleared in a single strike of hers.

In this problem, a single vertex is considered as a path too!

### Standard Input

The input includes several test cases. 

The first line of the input contains one integer $T(1 \leq T \leq 20)$, denoting the number of test cases.

For each test case, the first line contains two space-separated integers $N(1 \leq N \leq 50000)$, $k(1 \leq k \leq 100000)$, and a digit string $S(|S|=N)$. Denoting the number of vertex and the special number, and the decimal digits on every vertex. The decimal digit on the i-th vertex is the i-th character of $S$.

For each of the next $N-1$ lines, there are two space-separated integer $u,v$, denoting a road connecting two vertex in the dragon forest.

### Standard Output

For each test case, print the answer in a line.

### Sample Input

2
4 3 0123
1 2
1 4
3 1
2 10 50
1 2

### Sample Output

6
2

### Note

In the first example, there are 6 path can be cleared in a single strike:

$1,1-4,2-1-3,3-1-2,4,4-1$