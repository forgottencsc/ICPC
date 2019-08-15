# K-th Occurence

## Description

You are given a string $S$ consisting of only lowercase english letters and some queries.

For each query $(l, r, k)$, please output the starting position of the k-th occurence of the substring $S_lS_{l+1}...S_r$ in S.

## Standard input

The first line contains an integer $T(1 \leq T \leq 20)$, denoting the number of test cases.

The first line of each test case contains two integer $N(1 \leq N \leq 10^5), Q(1 \leq N \leq 10^5)$, denoting the length of $S$ and the number of queries.

The second line of each test case contains a string $S(|S|=N)$ consisting of only lowercase english letters.

Then $Q$ lines follow, each line contains three integer $l, r(1 \leq l \leq r \leq N)$ and  $k(1 \leq k \leq N)$, denoting a query.

There are at most $5$ testcases which $N$ is greater than $10^3$.

## Standard output

For each query, output the starting position of the k-th occurence of the given substring.

If such position don't exists, output $-1$ instead.

## Sample input

2
12 6
aaabaabaaaab
3 3 4
2 3 2
7 8 3
3 4 2
1 4 2
8 12 1
1 1
a
1 1 1

## Sample output

5
2
-1
6
9
8
1