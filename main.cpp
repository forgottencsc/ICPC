#include <bits/stdc++.h>
#define N (1<<20)
typedef long long ll;
typedef double dbl;

using namespace std;

dbl f[N], g[N];
int c[N];

void fmt(dbl* f, dbl* g, int w) {
    copy_n(f, 1 << w, g);
    for (int i = 0; i != w; ++i)
        for (int j = 0; j != (1 << w); ++j)
            if (j & (1 << i)) g[j] += g[j ^ (1 << i)];
}


int main(void) {
    ios::sync_with_stdio(0); cin.tie(0);
    #ifndef ONLINE_JUDGE
    ifstream cin("1.in");
    #endif // ONLINE_JUDGE
    int n; cin >> n;
    for (int i = 0; i != (1 << n); ++i)
        cin >> f[i];
    for (int i = 0; i != (1 << n); ++i)
        c[i] = c[i >> 1] + (i & 1);

    dbl ans = 0;
    fmt(f, g, n);

    bool flg = 0;

    for (int i = 1; i != (1 << n); ++i) {
        ans += (c[i] & 1 ? 1 : -1) * (1. / (1 - g[(1 << n) - 1 - i]));
        if (g[(1 << n) - 1 - i] == 1) flg = 1;
    }

    if (flg) cout<< "INF" << endl;
    else cout << setprecision(10) << ans << endl;

    return 0;
}
