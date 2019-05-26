#include <bits/stdc++.h>
#define N 100001
using namespace std;


int g[N][26], f[N], s[N], c[N], nc;
int q[N], *h, *t;

int nid[N];

int gn() {
    int p = nc++;
    memset(g[p], 0, sizeof(g[p]));
    f[p] = s[p] = c[p] = 0;
    return p;
}

void clr() { nc = 0; gn(); }

int ins(const string& s, int id) {
    int p = 0;
    for (char ch : s) {
        int o = ch - 'a';
        if (!g[p][o]) g[p][o] = gn();
        p = g[p][o];
    }
    nid[id] = p;
}

void build() {
    h = t = q;
    for (int o = 0; o != 26; ++o)
        if (g[0][o]) *t++ = g[0][o];
    while(h != t) {
        int u = *h++;
        for (int o = 0; o != 26; ++o) {
            int& v = g[u][o];
            if (v) {
                int w = f[u];
                while(w && !g[w][o])
                    w = f[w];
                f[v] = g[w][o], *t++ = v;
            }
        }
    }
}

void match(const string& t) {
    int p = 0;
    for (char ch : t) {
        int o = ch - 'a';
        while (p && !g[p][o])
            p = f[p];
        p = g[p][o];
        for (int q = p; q; q = f[q])
            c[q]++;
    }
}

void solve(istream& cin, ostream& cout) {
    string t; cin >> t;
    int n; cin >> n;
    clr();
    for (int i = 1; i <= n; ++i) {
        string s; cin >> s;
        ins(s, i);
    }
    build();
    match(t);
    for (int i = 1; i <= n; ++i)
        cout << c[nid[i]] << endl;
}

int main1(void) {
    #ifndef ONLINE_JUDGE
    ifstream cin("6.in");
    #endif // ONLINE_JUDGE
    solve(cin, cout);
    return 0;
}
