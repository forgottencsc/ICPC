
# k-Tuples

Operations:

`1 u`: if vertex $u$ exists, then erase it from graph $G$ with all edges connecting it, else add it to graph $G$.

`2 u v`：if edge $(u,v)$ exists, then erase it from graph, else add edge $(u,v)$ to graph.

`3 u v`: if there exists a path from $u$ to $v$, output 1, else output 0.

`4 u`: query the size of connected component containing $u$.

`5 k`: query the number of k-tuples mod $998244353$.

`6 u k`: query the number of k-tuples containing $u$ mod $998244353$.
