#include <bits/stdc++.h>
#define N 1<<20
using namespace std;
int s[N], t[N]; int f[N], l[N], n, m;

void getl() {
    for (int i = 2; i <= m; ++i) {
        int j = f[i - 1];
        while (j && t[i] != t[j + 1]) j = f[j];
        if (t[i] == t[j + 1]) ++j;
        f[i] = j;
    }
    for (int i = 1; i <= n; ++i) {
        int j = l[i - 1];
        while (j && s[i] != t[j + 1]) j = f[j];
        if (s[i] == t[j + 1]) ++j;
        l[i] = j;
        if (j == m) j = f[j - 1];
    }
}

signed main(void) {
    ios::sync_with_stdio(0); cin.tie(0);
    #ifndef ONLINE_JUDGE
    ifstream cin("1.in");
    #endif // ONLINE_JUDGE
    int T; cin >> T;
    while(T--) {
        cin >> n >> m;
        for (int i = 1; i <= n; ++i) cin >> s[i];
        for (int i = 1; i <= m; ++i) cin >> t[i];
        getl();
        int ans = -1;
        for (int i = 1; i <= n; ++i) {
            if (l[i] != m) continue;
            ans = i - m + 1;
            break;
        }
        cout << ans << endl;
    }
    return 0;
}
