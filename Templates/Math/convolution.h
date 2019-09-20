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
            cplx w{ 1, 0 };
			for (int k = 0; k != i; k++) {
				cplx u = p[j + k], v = w * p[i + j + k];
				p[j + k] = u + v; p[i + j + k] = u - v;
				w *= w0;
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
    for (int i = 0; i != fs; ++i) c[i] = round(p3[i].real());
    return fs;
}

void fmt(ll* f, ll* g, int w) {
    copy_n(f, 1 << w, g);
    for (int i = 0; i != w; ++i)
        for (int j = 0; j != (1 << w); ++j)
            if (j & (1 << i)) g[j] += g[j ^ (1 << i)];
}

void ifmt(ll* f, ll* g, int w) {
    copy_n(f, 1 << w, g);
    for (int i = 0; i != w; ++i)
        for (int j = 0; j != (1 << w); ++j)
            if (j & (1 << i)) g[j] -= g[j ^ (1 << i)];
}

void fwt(ll* a, int n) {
	for (int k = 1; k < n; k <<= 1)
		for (int m = k << 1, i = 0; i < n; i += m)
			for (int j = 0; j != k; j++) {
				ll x = a[i + j], y = a[i + j + k];
				//^: a[i + j] = x + y, a[i + j + d]= x - y;
				//&: a[i + j] = x + y;
				//|: a[i + j + d] = x + y;
			}
}


void ifwt(ll* a, int n) {
	for (int k = 1; k < n; k <<= 1)
		for (int m = k << 1, i = 0; i < n; i += m)
			for (int j = 0; j != k; j++) {
				ll x = a[i + j], y = a[i + j + k];
				//^: a[i + j] = (x + y) / 2, a[i + j + d] = (x - y) /2;
				//&: a[i + j] = x - y;
				//|: a[i + j + d] = y - x;
			}
}

