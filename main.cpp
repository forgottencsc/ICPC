#include <bits/stdc++.h>
#define N 1<<18
#define P 998244353
#define M(x) (((x) + P) % P)
#define i2 ((P+1)/2)
using namespace std;
#define fwt(op, u, v) \
void fwt_##op (ll* a, int n) {\
    for (int k = 1; k < n; k <<= 1)\
        for (int m = k << 1, i = 0; i < n; i += m)\
            for (int j = 0; j != k; j++) {\
                ll x = a[i + j], y = a[i + j + k];\
                a[i + j] = u ; \
                a[i + j + k] = v ; \
            }\
}
typedef long long ll;
fwt(or, x, M(x+y))
fwt(ior, x, M(y-x))
fwt(and, M(x+y), y)
fwt(iand, M(x-y), y)
fwt(xor, M(x+y), M(x-y))
fwt(ixor, M(M(x+y)*i2), M(M(x-y)*i2))

ll a[4][N], b[4][N], c[4][N];

int main(void) {
    #ifndef ONLINE_JUDGE
    freopen("1.in", "r", stdin);
    #endif // ONLINE_JUDGE

    int w; cin >> w; int n = 1 << w;
    for (int i = 0; i != n; ++i) scanf("%d", a[0] + i);
    for (int i = 0; i != n; ++i) scanf("%d", b[0] + i);
    for (int i = 1; i != 4; ++i) {
        copy_n(a[0], n, a[i]);
        copy_n(b[0], n, b[i]);
    }
    fwt_or(a[1], n); fwt_or(b[1], n);
    fwt_and(a[2], n); fwt_and(b[2], n);
    fwt_xor(a[3], n); fwt_xor(b[3], n);
    for (int i = 1; i != 4; ++i)
        for (int j = 0; j != n; ++j)
            c[i][j] = M(a[i][j] * b[i][j]);
    fwt_ior(c[1], n);
    fwt_iand(c[2], n);
    fwt_ixor(c[3], n);
    for (int i = 1; i != 4; ++i)
        for (int j = 0; j != n; ++j)
            printf("%d%c", c[i][j], " \n"[j == n - 1]);
    return 0;
}