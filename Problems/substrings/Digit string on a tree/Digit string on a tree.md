
题面：

Given a undirected tree and a string $S$ consists of at most $N$ decimal digits '0'~'9', digit on the $i$-th vertex is $S_i$.

We define the weight of a simple path $u_1, u_2, ..., u_m$ as the decimal integer $S_{u_1}S_{u_2}...S_{u_m}$.

Your task is to determine how many simple path on the tree whose weight is divisible by a given postive integer $k$.


***Standard Input***

The first line of the input contains one integer $T$, denoting the number of test cases.

The first line of each test case contains two integer $N,k$ and a string $S$ consisting of decimal digits.

Each of the next $N-1$ lines contain two integer $u_i,v_i$, denoting an edge $(u_i,v_i)$ on the tree.

***Standard Output***

Number of simple path whose weight is divisible by $k$.


***Constraints***
$1 \leq T \leq 30$

$1 \leq \sum{N} \leq 3 \times 10^5$

$1 \leq N \leq 5 \times 10^4$

$1 \leq k \leq 10^5$


题意：给出一个长度为$N$的数字串，每个数字对应树上的一个点，求其中有多少条树上路径代表的十进制数能被给定的$k$整除。

数据范围：

$1 \leq T \leq 30$

$1 \leq \sum{N} \leq 3 \times 10^5$

$1 \leq N \leq 5 \times 10^4$

$1 \leq k \leq 10^5$

题解：

先想想上树前怎么做：分治统计答案。

考虑区间$(l,r)$中经过区间中点$m=\lfloor (l+r)/2 \rfloor$的能被$k$整除的子串数量。

关于左半边：对于每个$d$统计有多少个$u \in \{l,l+1,...,m\}$使得$S_{u...m-1} \equiv x \pmod d$,记为$cnt(x,d)$。

关于右半边：枚举$v \in \{ m + 1, ..., r \}$,即$S_{m...v}\equiv y \pmod k$，需解一次同余方程$10^{v-m}x \equiv k-y\pmod k$。

利用exgcd解得$x\equiv x_0 \pmod{d}$后将$cnt(x_0,d)$计入答案。

观察到解得的$d=\frac{k}{\gcd(10^w,k)}$，因此只有部分的$d$对应的$cnt(x,d)$才会对答案有贡献。将$w$从$0$取到$30$即可找到所有可能对答案有贡献的$d$。

总复杂度$O(nlognlogk)$。

把序列上的分治换成点分治即可强行上树。