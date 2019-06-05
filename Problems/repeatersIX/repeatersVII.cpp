#include <bits/stdc++.h>
#define N 201
#define P 1000000007
#define R(x) ((x).size())
#define C(x) ((x)[0].size())
#define M(x) ((x) % P)

using namespace std;

typedef unsigned long long ul;
typedef vector<ul> vec;
typedef vector<vec> mat;

mat operator*(const mat& a, const mat& b) {
    mat r(R(a), vec(C(b), 0));
    for (int i = 0; i != R(a); ++i)
        for (int j = 0; j != C(b); ++j)
            for (int k = 0; k != C(a); ++k)
                r[i][j] = M(r[i][j] + a[i][k] * b[k][j]);
    return r;
}

mat I(int n) {
    mat r(n, vec(n, 0));
    for (int i = 0; i != n; ++i) r[i][i] = 1;
    return r;
}

mat qpow(mat a, ul b) {
    mat r = I(R(a));
    do if (b & 1) r = r * a;
    while (a = a * a, b >>= 1);
    return r;
}

ostream& operator<<(ostream& os, const mat& w) {
    for (int i = 0; i != R(w); ++i)
        for (int j = 0; j != C(w); ++j)
            os << w[i][j] << " \n"[j == C(w) - 1];
    return os;
}

struct aca_t {

    int g[N][26], f[N], e[N], nc;

    int gn() {
        int p = nc++;
        memset(g[p], 0, sizeof(g[p]));
        f[p] = e[p] = 0;
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
        for (int o = 0; o != 26; ++o) if (g[0][o]) q.push(g[0][o]);
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

    mat extract_mat() {
        mat r(nc + 2, vec(nc + 2, 0));
        for (int u = 0; u != nc; ++u) {
            if (e[u]) continue;
            for (int o = 0; o != 26; ++o) {
                int v = g[u][o];
                if (e[v]) r[nc][u]++;
                else r[v][u]++;
            }
        }

        r[nc][nc] = 26;
        r[nc + 1][nc] = 1;
        r[nc + 1][nc + 1] = 1;
        return r;
    }

} aca;

ul qpow(ul a, ul b) {
    ul r = 1;
    do if (b & 1) r = M(r * a);
    while(a = M(a * a), b >>= 1);
    return r;
}

void solve(istream& cin, ostream& cout) {
    int n; cin >> n;
    aca.clr();
    for (int i = 0; i != n; ++i) {
        string s; cin >> s;
        aca.ins(s);
    }
    aca.build();
    ul l; cin >> l;
    mat w = qpow(aca.extract_mat(), l + 1);
    cout << w[aca.nc + 1][0] << endl;
}


int main(void) {
    ios::sync_with_stdio(0); cin.tie(0);
    #ifndef ONLINE_JUDGE
    ifstream cin("1.in");
    ofstream cout("1.out");
    #endif
    //gen();
    solve(cin, cout);
    return 0;
}
