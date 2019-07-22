#include <bits/stdc++.h>
#define N 100001
#define P 998244353
#define M(x) (((x) + P) % P)
using namespace std;
typedef long long ll;

int main () {
    ios::sync_with_stdio(0); cin.tie(0);
    #ifndef ONLINE_JUDGE
    ifstream cin("1.in");
    #endif // ONLINE_JUDGE

    ll c[10] = { 0 }, d[11] = { 0 }, n;
    ll ans = 0, p10[21];
    for (int i = p10[0] = 1; i <= 20; ++i) p10[i] = M(p10[i - 1] * 10);
    cin >> n;
    while(n--) {
        string s; cin >> s;
        for (int i = 0; i != s.size(); ++i) {
            int o = s[s.size() - i - 1] - '0';
            c[i] += o;
        }
        d[s.size() - 1]++;
    }

    for (int i = 0; i != 10; ++i) {
        for(int j = 0; j <= 10; ++j) {
            if (i <= j)
                ans = M(ans + d[j] * M(c[i] * p10[2 * i + 1]));
            else
                ans = M(ans + d[j] * M(c[i] * p10[i + j + 1]));
            if (i <= j + 1)
                ans = M(ans + d[j] * M(c[i] * p10[2 * i]));
            else
                ans = M(ans + d[j] * M(c[i] * p10[i + j + 1]));
        }
    }

    cout << ans << endl;

    return 0;
}
