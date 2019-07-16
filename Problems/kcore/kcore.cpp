#include <bits/stdc++.h>
#define N 1000001
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
        w = max(w, d[u]);
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

void kcore1() {
    typedef pair<int, int> pii;
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    for (int i = 1; i <= n; ++i) {
        d[i] = g[i].size();
        pq.push({ d[i], i });
    }

    int w = 0;
    while (!pq.empty()) {
        int u, deg;
        tie(deg, u) = pq.top(); pq.pop();
        if (vis[u]) continue;
        w = max(w, deg);
        ans[u] = w;
        for (int v : g[u]) {
            if (vis[v]) continue;
            pq.push({ --d[v], v });
        }
        vis[u] = 1;
    }
}

void solve(istream& cin, ostream& cout) {
    cin >> n >> m;

    for (int i = 1; i <= n; ++i) {
        g[i].clear();
        d[i] = a[i] = c[i] = p[i] = ans[i] = vis[i] = 0;
    }

    for (int i = 1; i <= m; ++i) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    kcore();

    for (int i = 1; i <= n; ++i)
        cout << ans[i] << " \n"[i == n];
    cout.flush();
}

int main1(void) {
    ios::sync_with_stdio(0); cin.tie(0);
    #ifndef ONLINE_JUDGE
    ifstream cin("4.in");
    #endif // ONLINE_JUDGE
    solve(cin, cout);
    return 0;
}
