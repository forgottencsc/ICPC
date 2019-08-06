#include <bits/stdc++.h>
#define N 1000002
using namespace std;

typedef long long ll;
typedef double dbl;
ll a[N], s[N];
dbl dp[N]; int c[N];

dbl cal(int l, int r) {
    dbl p; int l1, r1, l2, r2;
    if ((r - l + 1) % 2) {
        p = a[(l + r) / 2];
        l1 = l; r1 = (l + r) / 2 - 1;
        l2 = (l + r) / 2 + 1; r2 = r;
    }
    else {
        p = (a[(l + r) / 2] + a[(l + r) / 2 + 1]) / 2;
        l1 = l; r1 = (l + r) / 2;
        r2 = (l + r) / 2 + 1; r2 = r;
    }
    dbl lv = p * (r1 - l1 + 1) - (s[r1] - s[l1 - 1]);
    dbl rv = (s[r2] - s[l2 - 1]) - p * (r2 - l2 + 1);
    dbl res = lv + rv;
    return res;
}

int main(void) {
    #ifndef ONLINE_JUDGE
    freopen("1.in", "r", stdin);
    #endif // ONLINE_JUDGE
    int n, k; scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; ++i)
        scanf("%lld", &a[i]);
    for (int i = 1; i <= n; ++i)
        s[i] = s[i - 1] + a[i];

    ll l = -1e12, r = 1e12, ans = -1;
    while (l <= r) {
        ll mid = (l + r) >> 1;
        int cnt = 0;
        deque<int> q; q.push_back(0);
        for (int i = 1; i <= n; ++i) {
            while (q.size() >= 2 && cal(i, q[0] + 1) + dp[q[0]] < cal(i, q[1] + 1) + dp[q[1]])
                q.pop_front();
            dp[i] = cal(i, q[0] + 1) + dp[q[0]] + mid;
            c[i] = c[q[0]] + 1;
            while (
        }
    }

    return 0;
}
