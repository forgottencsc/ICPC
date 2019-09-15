#include <bits/stdc++.h>
#define N 1<<18
using namespace std;


typedef complex<double> cplx;

int fr[N], fs;

void init(int s) {
	for (fs = 1; fs <= s; fs <<= 1);
	for (int i = 0; i != fs; ++i)
		fr[i] = (fr[i >> 1] >> 1) | (i & 1 ? (fs >> 1) : 0);
}

typedef double dbl;
const dbl pi = acos(-1);
void fft(cplx* p, int f) {
	for (int i = 0; i != fs; ++i) if (i < fr[i]) swap(p[i], p[fr[i]]);
	for (int i = 1; i != fs; i <<= 1) {
		cplx w0{ cos(pi / i), (f ? 1. : -1.) * sin(pi / i) };
		for (int j = 0; j != fs; j += (i << 1)) {
			cplx w{ 1, 0 };
			for (int k = 0; k != i; k++, w = w * w0) {
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

cplx p1[N], p2[N], pr[N];

int a[N], b[N], c[N], d[N];
long long sum[N],ans;

int MAX;

void conv(int* a, int* b, int n, int* d) {
    for (int i = 1; i <= n; ++i)
        p1[a[i]] += 1;
    for (int i = 1; i <= n; ++i)
        p2[b[i]] += 1;
    init(5);
    fft(p1, 1); fft(p2, 1);
    for (int i = 0; i != fs; ++i) pr[i] = p1[i] * p2[i];
    fft(pr, 0); fft_res(pr);
    for (int i = 0; i != fs; ++i)
        d[i] = round(pr[i].real());
}

int main () {
    int T; scanf("%d", &T);
    while(T--) {
        int n; scanf("%d", &n);

        ans = MAX = 0;

        for (int i = 1; i <= n; ++i) {
            scanf("%d", &a[i]);
            MAX = max(a[i],MAX);
        }
        for (int i = 1; i <= n; ++i) {
            scanf("%d", &b[i]);
            MAX = max(b[i],MAX);
        }
        for (int i = 1; i <= n; ++i) {
            scanf("%d", &c[i]);
            MAX = max(c[i],MAX);
        }
        sort(a + 1, a + n + 1);
        sort(b + 1, b + n + 1);
        sort(c + 1, c + n + 1);
        //for (int i = 1; i <= n; ++i)

        conv(a,b,n,d);
        sum[0] = d[0];
        for(int i = 1;i <= MAX * 2;++i)
            sum[i] = sum[i - 1] + d[i];
        for(int i = 1;i <= n;++i) {
            ans += sum[c[i] * 2] - sum[c[i] - 1];
        }

        conv(a,c,n,d);
        sum[0] = d[0];
        for(int i = 1;i <= MAX * 2;++i)
            sum[i] = sum[i - 1] + d[i];
        for(int i = 1;i <= n;++i) {
            ans += sum[b[i] * 2] - sum[b[i] - 1];
        }

        conv(c,b,n,d);
        sum[0] = d[0];
        for(int i = 1;i <= MAX * 2;++i)
            sum[i] = sum[i - 1] + d[i];
        for(int i = 1;i <= n;++i) {
            ans += sum[a[i] * 2] - sum[a[i] - 1];
        }



        for(int i = 1;i <= n;++i) {

        }


    }
    return 0;
}
