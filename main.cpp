#include <bits/stdc++.h>
#define N 100005
using namespace std;

typedef long long ll;

namespace pam {

char s[N<<1]; int tl, tr;
int g[N][26], f[N], l[N], h[N], nc;
int pl, pr;

int gn(int len) {
    int q = nc++; l[q] = len; h[q] = f[q] = 0;
    memset(g[q], 0, sizeof(g[q]));
    return q;
}

void clr() {
    fill(s + tl, s + tr + 1, 0);
    nc = 0; gn(0); gn(-1); f[0] = 1;
    tr = N; tl = tr + 1; h[0] = h[-1] = 0;
    pl = pr = 0;
}

int gfl(int p, int i) {
    while (s[i] != s[i + l[p] + 1])
        p = f[p];
    return p;
}

int gfr(int p, int i) {
    while (s[i] != s[i - l[p] - 1])
        p = f[p];
    return p;
}

int extl(int o) {
    s[--tl] = o + 'a'; int p = gfl(pl, tl);
    if (!g[p][o]) {
        int q = gn(l[p] + 2); g[p][o] = q;
        if (p != 1) f[q] = g[gfl(f[p], tl)][o];
        h[q] = h[f[q]] + 1;
    }
    pl = g[p][o];
    if (tl + l[pl] - 1 == tr)
        pr = pl;
    return h[pl];
}

int extr(int o) {
    s[++tr] = o + 'a'; int p = gfr(pr, tr);
    if (!g[p][o]) {
        int q = gn(l[p] + 2); g[p][o] = q;
        if (p != 1) f[q] = g[gfr(f[p], tr)][o];
        h[q] = h[f[q]] + 1;
    }
    pr = g[p][o];
    if (tr - l[pr] + 1 == tl)
        pl = pr;
    return h[pr];
}

}

int main(void) {
    #ifndef ONLINE_JUDGE
    freopen("1.in", "r", stdin);
    #endif // ONLINE_JUDGE

    int n;
    while (~scanf("%d", &n)) {
        pam::clr();
        typedef long long ll;
        ll cnt = 0;
        while (n--) {
            int o; scanf("%d", &o);
            if (o == 1) {
                char b[2]; scanf("%s", b);
                cnt += pam::extl(b[0] - 'a');
            }
            if (o == 2) {
                char b[2]; scanf("%s", b);
                cnt += pam::extr(b[0] - 'a');
            }
            if (o == 3) {
                printf("%d\n", pam::nc - 2);
            }
            if (o == 4) {
                printf("%lld\n", cnt);
            }
        }
    }

    return 0;
}