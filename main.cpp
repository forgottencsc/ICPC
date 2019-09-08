#include <bits/stdc++.h>
#define N (1<<19)
#define P 998244353
#define M(x) (((x) + P) % P)
typedef long long ll;

using namespace std;

vector<int> g[N];

int deg[N]; bool del[N];
void encode_tree(int* p, int n) {
    priority_queue<int, vector<int>, greater<int>> pq;
    fill(del + 1, del + n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        deg[i] = g[i].size();
        if (deg[i] == 1)
            pq.push(i);
    }
    for (int i = 1; i <= n - 2; ++i) {
        int u = pq.top(), v; pq.pop(); del[u] = 1;
        for (int w : g[u]) if (!del[w]) v = w;
        p[i] = v; if (--deg[v] == 1) pq.push(v);
    }
}

int cnt[N];
void decode_tree(int* p, int n) {
    priority_queue<int, vector<int>, greater<int>> pq;
    for (int i = 1; i <= n - 2; ++i) cnt[p[i]]++;
    for (int i = 1; i <= n; ++i) if (!cnt[i]) pq.push(i);
    for (int i = 1; i <= n - 2; ++i) {
        int u = p[i], v = pq.top(); pq.pop();
        g[u].push_back(v);
        g[v].push_back(u);
        if (!--cnt[u]) pq.push(u);
    }
    int u = pq.top(); pq.pop();
    int v = pq.top(); pq.pop();
    g[u].push_back(v);
    g[v].push_back(u);
}

int main(void) {
    ios::sync_with_stdio(0); cin.tie(0);
    #ifndef ONLINE_JUDGE
    ifstream cin("1.in");
    #endif // ONLINE_JUDGE
    int p[4] = { 0, 5, 5, 4 }, q[4];
    decode_tree(p, 5);
    for (int i = 1; i <= 5; ++i) {
        cout << i << ": ";
        for (int v : g[i]) cout << v << ' ';
        cout << endl;
    }
    encode_tree(q, 5);
    for (int i = 1; i <= 3; ++i)
        cout << q[i] << ' ';
    cout << endl;
    return 0;
}