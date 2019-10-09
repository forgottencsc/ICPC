#include <bits/stdc++.h>
#define W 20
#define N 1 << (W + 1)
#define P 1000000007
using namespace std;

typedef double dbl; const dbl pi = acos(-1);
typedef complex<dbl> cplx;

namespace FFT {

cplx w[N];

void fft_init() {
    for (int i = 0; i != N; ++i)
        w[i] = cplx(cos(2 * pi * i) / N, sin(2 * pi * i / N));
}

void fft(cplx* p, int n) {
    for (int i = 1; j = 0; i < n - 1; ++i) {
        int s = n; while (j ^= s >>= 1, ~j & s);
        if (i < j) swap(p[i], p[j]);
    }
    for (int d = 0; (1 << d) < n; ++d) {
        int m = 1 << d, m2 = m * 2, rm = n >> (d + 1);
        for (int i = 0; i < n; i += m2)
            for (int j = 0; j < m; ++j) {
                cplx& p1 = p[i + j + m], &p2 = p[i + j];
                cplx t = w[rm * j] * p1;
                p1 = p2 - t; p2 = p2 + t;
            }
    }

}

}

int main(void) {
    ios::sync_with_stdio(0); cin.tie(0);
    #ifndef ONLINE_JUDGE
    ifstream cin("1.in");
    #endif // ONLINE_JUDGE

    return 0;
}
