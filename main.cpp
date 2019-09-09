#include <bits/stdc++.h>
#define N 2001
#define M(x) (((x) + P) % P)
#define P 998244353
typedef long long ll;
using namespace std;
ll invs[N], f[N], fi[N];
ll bi[N][N], be[N], ep[N][N];
ll inv(ll x) { return x == 1 ? 1 : M(inv(P % x) * (P - P / x)); }
void ginv() {
    invs[1] = 1; f[0] = fi[0] = 1;
    for (int i = 2; i != N; ++i) invs[i] = M(invs[P % i] * (P - P / i));
    for (int i = 1; i != N; ++i) f[i] = M(f[i - 1] * i);
    for (int i = 1; i != N; ++i) fi[i] = M(fi[i - 1] * invs[i]);
    // Binomial coefficient
    for (int i = 0; i != N; ++i) {
        bi[i][0] = bi[i][i] = 1;
        for (int j = 1; j < i; ++j)
            bi[i][j] = M(bi[i - 1][j - 1] + bi[i - 1][j]);
    }
    be[0] = 1;  //  Bernoulli numbers
    for (int i = 1; i != N; ++i)
        for (int j = 0; j != i; ++j)
            be[i] = M(be[i] - M(bi[i][j] * M(be[j] * invs[i - j + 1])));
    //  Equal Power Sum Coef
    for (int i = 1; i != N; ++i)
        for (int j = 0; j <= i; ++j)
            ep[i][i + 1 - j] = M(M(j&1?-invs[i+1]:invs[i+1])*M(bi[i + 1][j]*be[j]));
}

//  \sum_{i=1}^{n}{i^k}
ll epsum(ll n, ll k) {
    ll w = n, r = 0;
    for (int i = 1; i <= k + 1; ++i, w = M(w * n))
        r = M(r + M(w * ep[k][i]));
    return r;
}

signed main(void) {
    ios::sync_with_stdio(0); cin.tie(0);
    #ifndef ONLINE_JUDGE
    ifstream cin("1.in");
    #endif // ONLINE_JUDGE
    ginv();

    cout << epsum2(120000, 900) << endl;

    return 0;
}
