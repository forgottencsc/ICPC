#include <bits/stdc++.h>
using namespace std;
const int N = 2000005;

int sa[N], rk[N], sh[N];
int st[N][21], lg2[N];
int sw1[N], sw2[N], sc[N];
void build_sa(const char* s) {
    int n = strlen(s + 1), m = 128, *x = sw1, *y = sw2;
    memset(sc + 1, 0, m << 2);
    for (int i = 1; i <= n; ++i) sc[x[i] = s[i]]++;
    for (int i = 1; i <= m; ++i) sc[i] += sc[i - 1];
    for (int i = 1; i <= n; ++i) sa[sc[x[i]]--] = i;
    for (int k = 1; k <= n; k <<= 1) {
        int p = 0;
        for (int i = n - k + 1; i <= n; ++i) y[++p] = i;
        for (int i = 1; i <= n; ++i) if (sa[i] > k) y[++p] = sa[i] - k;
        memset(sc + 1, 0, m << 2);
        for (int i = 1; i <= n; ++i) sc[x[i]]++;
        for (int i = 1; i <= m; ++i) sc[i] += sc[i - 1];
        for (int i = n; i >= 1; --i) sa[sc[x[y[i]]]--] = y[i];
        swap(x, y); p = x[sa[1]] = 1;
        for (int i = 2; i <= n; ++i)
            x[sa[i]] = (y[sa[i] + k] == y[sa[i - 1] + k]
            && y[sa[i]] == y[sa[i - 1]]) ? p: ++p;
        m = p; if (m == n) break;
    }
    for (int i = 1; i <= n; ++i) rk[sa[i]] = i;
    for (int i = 1, k = 0; i <= n; ++i) {
        if (rk[i] == 1) continue; if (k) --k;
        int j = sa[rk[i] - 1];
        while (j + k <= n && i + k <= n && s[i + k] == s[j + k])
            ++k;
        sh[rk[i]] = k;
    }
}

char s[N], t[N];

int main(void) {
	ios::sync_with_stdio(0); cin.tie(0);
#ifndef ONLINE_JUDGE
	ifstream cin("1.in");
#endif
    cin >> s;
    int n = strlen(s);
    s[n] = '#';
    cin >> s + n + 1;
    int m = strlen(s + n + 1);
    build_sa(s - 1);

    int ans = 0;
    for (int i = 2; i <= n + m + 1; ++i) {
        int u = sa[i], v = sa[i - 1];
        if (u > v) swap(u, v);
        if (u <= n && v >= n + 2)
            ans = max(ans, sh[i]);
    }
    cout << ans << endl;
	return 0;
}