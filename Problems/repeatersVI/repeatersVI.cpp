#include <bits/stdc++.h>
#define N 2000005
using namespace std;

int n, m, k;
char s[N], t[N], u[N];
int z[N], e[N], r[N], c[N];

void getz() {
    for (int i = 1, l = 0, r = 0; i != m; ++i) {
        int j = z[i - l];
        if (i+j>r) for (j=max(0, r-i); i+j!=m&&t[i+j]==t[j]; ++j);
        z[i] = j; if (i+j-1>r) l=i, r=i+j-1;
    }
    z[0] = m;
}

void gete() {
    for (int i = 0, l = 0, r = 0; i != n; ++i) {
        int j = z[i - l];
        if (i+j>r) for (j=max(0, r-i); i+j!=n&&s[i+j]==t[j]; ++j);
        e[i] = j; if (i+j-1>r) l=i, r=i+j-1;
    }
}

void getr() {
    k = 2 * n + 1; memset(u, '#', k); u[k] = 0;
    for (int i = 0; i != n; ++i) u[2 * i + 1] = s[i];
    for (int i = 1, p = 0, w = 0; i != k; ++i) {
        int j = (i>p+w ? 0 : min(r[p-(i-p)], p+w-i));
        while(0<=i-j-1 && i+j+1<k && u[i-j-1]==u[i+j+1]) ++j;
        r[i] = j; if (i + j > p + w) p = i, w = j;
    }
}

void solve(istream& cin, ostream& cout) {
    cin >> s >> t;
    n = strlen(s);
    m = strlen(t);
    reverse(s, s + n);

    getz();
    gete();
    getr();

    for (int i = 0; i != n; ++i) c[i] = 0;

    for (int i = 0; i != k; ++i) {
        c[i / 2]++;
        c[i / 2 + ((r[i] + 1) / 2)]--;
    }

    for (int i = 1; i <= n; ++i)
        c[i] += c[i - 1];

    typedef long long ll;
    ll ans = 0;
    for (int i = 1; i != n; ++i)
        ans += 1ll * e[i] * c[i - 1];

    cout << ans << endl;
}

int main1(void) {
	ios::sync_with_stdio(0); cin.tie(0);
#ifndef ONLINE_JUDGE
	ifstream cin("1.in");
#endif
    solve(cin, cout);
	return 0;
}