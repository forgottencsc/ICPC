#include <bits/stdc++.h>
#define N 2000002
using namespace std;

char s[N]; int n;
int g[N][26], f[N], l[N], w[N], nc;

int gn(int len, int q = 0) {
    int p = nc++; l[p] = len; f[p] = f[q];
    memcpy(g[p], g[q], sizeof(g[p]));
    return p;
}

void clr() { nc = 1; gn(0); }

int extend(int p, int o) {
    int np = gn(l[p] + 1);
    for (; p && !g[p][o]; p = f[p])
        g[p][o] = np;
    if (!p) f[np] = 1;
    else {
        int q = g[p][o];
        if (l[q] == l[p] + 1) f[np] = q;
        else {
            int nq = gn(l[p] + 1, q);
            f[np] = f[q] = nq;
            for (; p && g[p][o] == q; p = f[p])
                g[p][o] = nq;
        }
    }
    return np;
}

int c[N], pos[N];
void sort_sam() {
    iota(pos, pos + nc, 0);
    for (int p = 0; p != nc; ++p) c[l[p]]++;
    for (int i = 1; i <= n; ++i) c[i] += c[i - 1];
    for (int p = 0; p != nc; ++p) pos[--c[l[p]]] = p;
}

int main(void) {
    ios::sync_with_stdio(0); cin.tie(0);
    #ifndef ONLINE_JUDGE
    ifstream cin("1.in");
    #endif // ONLINE_JUDGE
    cin >> s; n = strlen(s);
    int p = 1; clr();
    for (int i = 0; i != n; ++i) {
        p = extend(p, s[i] - 'a');
        w[p]++;
    }
    sort_sam();
    for (int i = nc - 1; l[pos[i]]; --i) {
        int p = pos[i];
        w[f[p]] += w[p];
    }
    typedef long long ll; ll ans = 0;
    for (int i = 1; i != nc; ++i) {
        if (w[i] > 1)
            ans = max(ans, 1ll * w[i] * l[i]);
    }
    cout << ans << endl;
    return 0;
}