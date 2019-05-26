#include <bits/stdc++.h>
#define N 101
using namespace std;
int n, m;
vector<int> g[N];

//  a[]: array of vertices with non-decreasing degree.
//  c[]: array for counting sort. c[i]+1 is the position of the first vertex with degree i.
//  p[]: p[i] is the position of vertex i in the array a[].
int d[N]; bool vis[N];
int a[N], c[N], p[N];
int ans[N];

inline void dec_key(int u) {
    //  find the first element v such that d[v] == d[u]
    int v = a[c[d[u]]];
    if (v != u) {
        //  swap v & u.
        swap(a[p[v]], a[p[u]]);
        //  swap the position of v & u.
        swap(p[v], p[u]);
    }
    //  decrease the degree of vertex u.
    c[d[u]]++; d[u]--;
}

void kcore() {
    //  initialize array d[].
    for (int i = 1; i <= n; ++i) d[i] = g[i].size();
    //  calculate c[i]: the number of vertices having degree equal to i.
    for (int i = 1; i <= n; ++i) c[d[i]]++;
    //  calculate c[i]: the number of vertices having degree less or equal to i.
    for (int i = 1; i <= n; ++i) c[i] += c[i - 1];
    //  get the position of vertex i.
    for (int i = 1; i <= n; ++i) a[p[i] = c[d[i]]--] = i;
    //  get the position of the first vertex with degree i.
    for (int i = 1; i <= n; ++i) c[i]++;
    //  delete vertex with minimum degree.
    for (int i = 1, w = 0; i <= n; ++i) {
        int u = a[i];
        //  delete u from array.
        //  calculate the coreness of vertex u.
        while(w < d[u])
            ++w;
        ans[u] = w;
        //  decrease the degree of u's neighbors.
        for (int v : g[u]) {
            if (vis[v]) continue;
            dec_key(u);
            dec_key(v);
            //cout << u << ' ' << v << endl;
        }
        //  mark vertex u.
        vis[u] = 1;
    }
}

void solve(istream& cin, ostream& cout) {
    cin >> n >> m;
    for (int i = 1; i <= m; ++i) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    kcore();

    for (int i = 1; i <= n; ++i)
        cout << ans[i] << endl;
}

int main(void) {
    ios::sync_with_stdio(0); cin.tie(0);
    #ifndef ONLINE_JUDGE
    ifstream cin("1.in");
    #endif // ONLINE_JUDGE
    solve(cin, cout);
    return 0;
}

/*
12 28
1 2
1 3
1 4
1 5
1 6
2 3
2 4
2 5
2 6
3 4
3 5
3 6
4 5
4 6
5 6
7 8
8 9
9 10
10 11
11 12
12 7
8 10
10 12
12 8
7 9
9 11
11 7
1 7

11 23
1 2
1 3
1 4
1 5
2 3
2 4
2 5
3 4
3 5
4 5
6 7
7 8
8 9
9 10
10 11
11 6
6 8
8 10
10 6
7 9
9 11
11 7
1 7

16 32
1 2
2 3
3 4
4 5
5 6
6 1
1 3
3 5
5 1
2 4
4 6
6 2
7 8
7 9
7 10
7 11
8 9
8 10
8 11
9 10
9 11
10 11
12 13
12 14
13 14
1 12
7 12
15 16
2 15
3 16
8 15
9 16
*/