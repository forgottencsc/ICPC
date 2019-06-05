#include <bits/stdc++.h>
using namespace std;

int main(void) {
    ios::sync_with_stdio(0); cin.tie(0);
    #ifndef ONLINE_JUDGE
    ifstream cin("1.in");
    #endif // ONLINE_JUDGE
    typedef long long ll;
    ll p3[30]; for (int i = p3[0] = 1; i != 30; ++i) p3[i] = p3[i - 1] * 3;
    int n, k, m; ll t; cin >> n >> k >> t; m = n / 2;
    vector<ll> a; copy_n(istream_iterator<ll>(cin), n, back_inserter(a));
    vector<vector<ll>> x(m + 1);
    for (int i = 0; i != p3[m]; ++i) {
        int w = 0; ll s = 0;
        for (int j = 0; j != m; ++j) {
            int o = (i / p3[j]) % 3;
            if (o == 1)
                s += a[j];
            else if(o == 2) {
                s += (a[j] * (a[j] + 1)) / 2;
                w++;
            }
        }
        for (int j = w; j <= m; ++j)
            x[j].push_back(s);
    }
    for (int i = 0; i <= m; ++i) {
        sort(x[i].begin(), x[i].end());
        //cout << x[i].size() << endl;
        //for (int j : x[i]) cout << j << ' '; cout << endl;
    }

    ll ans = 0;
    for (ll i = 0; i != p3[n]; i += p3[m]) {
        int w = 0; ll s = 0;
        for (int j = m; j != n; j++) {
            int o = (i / p3[j]) % 3;
            if (o == 1)
                s += a[j];
            else if (o == 2) {
                s += (a[j] * (a[j] + 1)) / 2;
                w++;
            }
        }
        if (w > k) continue;
        int y = min(k - w, m);
        auto[lb, ub] = equal_range(x[y].begin(), x[y].end(), t - s);
        ans += distance(lb, ub);
    }
    cout << ans << endl;
    return 0;
}