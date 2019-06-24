#include <bits/stdc++.h>
using namespace std;

int main(void) {
    #ifndef ONLINE_JUDGE
    ifstream cin("1.in");
    #endif // ONLINE_JUDGE
    int n, k, a = 0; cin >> n >> k;
    vector<int> v(k);
    for (int i = 0; i != k; ++i) cin >> v[i];
    for (int i = 0; i != (1 << k); ++i) {
        int w = 1, s = 1;
        for (int j = 0; j != k; ++j)
            if (i & (1 << j)) w = lcm(w, v[j]), s = -s;
        a += s * (n / w);
    }
    int ans = 0;
    for (int i = 1; i <= n; ++i) {
        bool flg = 0;
        for (int w : v)
            if (i % w == 0)
                flg = 1;
        if (!flg) ans++;
    }
    cout << a << ' ' << ans << endl;
    return 0;
}