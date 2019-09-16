#include <bits/stdc++.h>
#define N 1<<21
using namespace std;

typedef double dbl;
typedef complex<dbl> cplx;
const dbl pi = acos(-1);

int fr[N], fs;
void init(int s) {
	for (fs = 1; fs <= s; fs <<= 1);
	for (int i = 0; i != fs; ++i)
		fr[i] = (fr[i >> 1] >> 1) | (i & 1 ? (fs >> 1) : 0);
}

void fft(cplx* p, int f) {
	for (int i = 0; i != fs; ++i) if (i < fr[i]) swap(p[i], p[fr[i]]);
	for (int i = 1; i != fs; i <<= 1) {
		cplx w0{ cos(pi / i), f * sin(pi / i) };
		for (int j = 0; j != fs; j += (i << 1)) {
			for (int k = 0; k != i; k++) {
                cplx w{ cos(k * pi / i), f * sin(k * pi / i) };
				cplx u = p[j + k], v = w * p[i + j + k];
				p[j + k] = u + v; p[i + j + k] = u - v;
			}
		}
	}
}

void fft_res(cplx* p) {
	for (int i = 0; i != fs; ++i)
		p[i] = p[i] * (1. / fs);
}

cplx p1[N], p2[N], p3[N];
int conv(int* a, int n, int* b, int m, int* c) {
    init(n + m + 1);
    for (int i = 0; i <= n; ++i) p1[i] = a[i];
    fill(p1 + n + 1, p1 + fs, cplx{});
    for (int i = 0; i <= m; ++i) p2[i] = b[i];
    fill(p2 + m + 1, p2 + fs, cplx{});
    fft(p1, 1); fft(p2, 1);
    for (int i = 0; i != fs; ++i) p3[i] = p1[i] * p2[i];
    fft(p3, -1); fft_res(p3);
    for (int i = 0; i != fs; ++i)
        c[i] = round(p3[i].real());
    return fs;
}

int a[N], b[N], c[N];

int main(void) {
    #ifndef ONLINE_JUDGE
    freopen("1.in", "r", stdin);
    #endif // ONLINE_JUDGE

    int n, m; scanf("%d%d", &n, &m);
    for (int i = 0; i <= n; ++i) scanf("%d", &a[i]);
    for (int i = 0; i <= m; ++i) scanf("%d", &b[i]);
    conv(a, n + 1, b, m + 1, c);
    for (int i = 0; i <= n + m; ++i) printf("%d ", c[i]);

    return 0;
}