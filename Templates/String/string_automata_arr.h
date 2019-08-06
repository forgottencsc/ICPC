#include <bits/stdc++.h>
#define N 1000001
using namespace std;

//  ACAM
int g[N][26], f[N], e[N], nc;

int gn() {
    int p = nc++; f[p] = e[p] = 0;
    memset(g[p], 0, sizeof(g[p]));
    return p;
}

void clr() { nc = 0; gn(); }

void ins(const string& s) {
    int p = 0;
    for (int i = 0; i != s.size(); ++i) {
        int o = s[i] - 'a';
        if (!g[p][o]) g[p][o] = gn();
        p = g[p][o];
    }
    e[p] = 1;
}

void build() {
    queue<int> q;
    for (int o = 0; o != 26; ++o)
        if (g[0][o]) q.push(g[0][o]);
    while(!q.empty()) {
        int u = q.front(); q.pop();
        if (e[f[u]]) e[u] = 1;
        for (int o = 0; o != 26; ++o) {
            int& v = g[u][o];
            if (!v) v = g[f[u]][o];
            else {
                f[v] = g[f[u]][o];
                q.push(v);
            }
        }
    }
}

//  SAM
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


//  PAM
char s[N];
int g[N][26], f[N], l[N], w[N], nc;

int gn(int len) {
    int p = nc++; l[p] = len; f[p] = 0;
    memset(g[p], 0, sizeof(g[p]));
    return p;
}

int gf(int p, int i) {
    while (s[i] != s[i - l[p] - 1])
        p = f[p];
    return p;
}

void clr() {
    nc = 0; gn(0); gn(-1);
    f[0] = 1; f[1] = -1;
}

int extend(int p, int i) {
    int o = s[i] - 'a'; p = gf(p, i);
    if (!g[p][o]) {
        int q = gn(l[p] + 2); g[p][o] = q;
        if (p != 1) f[q] = g[gf(f[p], i)][o];
    }
    p = g[p][o];
    return p;
}
