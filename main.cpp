#include <bits/stdc++.h>
#define N 200001
using namespace std;

int a[N], b[N];

int main(void){
    ios::sync_with_stdio(0); cin.tie(0);
#ifndef ONLINE_JUDGE
    ifstream cin("1.in");
#endif // ONLINE_JUDGE
    int T; cin >> T;
    while(T--) {
        int n, x; cin >> n >> x;
        int m = 0, d = 0;
        for (int i = 1; i <= n; ++i) {
            cin >> a[i] >> b[i];
            m = max(m, a[i]);
            d = max(d, a[i] - b[i]);
        }
        if (!d) cout << -1 << endl;
        else {
            cout << (x - m - 1) / d + 1 + (x > m) << endl;
        }
    }

    return 0;
}
