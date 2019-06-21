#include <bits/stdc++.h>
using namespace std;
const int N = 1000005;

int sa[N], rk[N], sh[N];
int sc[N], sw1[N], sw2[N];
void isort(int n, int m, int* s, int* c, int* x, int* y){
    for (int i = 1; i <= m; ++i) c[i] = 0;
    for (int i = 1; i <= n; ++i) c[x[i]]++;
    for (int i = 1; i <= m; ++i) c[i] += c[i - 1];
    for (int i = n; i >= 1; --i) s[c[x[y[i]]]--] = y[i];
}
bool cmp(int u, int v, int w, int* x) {
    return x[u] == x[v] && x[u + w] == x[v + w];
}
void build_sa(char* s) {
    int n = strlen(s), m = 128;
    int* x = sw1, *y = sw2;
    for (int i = 1; i <= n; ++i) x[i] = s[i - 1], y[i] = i;
    isort(n, m, sa, sc, x, y);
    for (int w = 1; w <= n && m != n; w <<= 1) {
        int p = 0;
        for (int i = n - w + 1; i <= n; ++i) y[++p] = i;
        for (int i = 1; i <= n; ++i) if (sa[i] > w) y[++p] = sa[i] - w;
        isort(n, m, sa, sc, x, y);
        swap(x, y); m = x[sa[1]] = 1;
        for (int i = 2; i <= n; ++i)
            x[sa[i]] = (cmp(sa[i], sa[i - 1], w, y) ? m : ++m);
        if (m == n) break;
    }
}

char s[N];

int main(void) {
	ios::sync_with_stdio(0); cin.tie(0);
#ifndef ONLINE_JUDGE
	ifstream cin("1.in");
	//ofstream cout("1.out");
#endif
    cin >> s; int n = strlen(s);
    build_sa(s);
    for (int i = 1; i <= n; ++i) cout << sa[i] << ' ';
	return 0;
}