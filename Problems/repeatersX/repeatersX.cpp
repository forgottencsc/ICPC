#include <bits/stdc++.h>
#define N 1000001
using namespace std;

int g[N][26], f[N], w[N], l[N], nc;

inline int gn() {
    int p = nc++;
    memset(g[p], 0, sizeof(g[p]));
    f[p] = w[p] = 0;
    return p;
}

int ins(const string& s) {
    int p = 0;
    for (int i = 0; i != s.size(); ++i){
        int o = s[i] - 'a';
        if (!g[p][o]) g[p][o] = gn();
        l[g[p][o]] = l[p] + 1;
        p = g[p][o]; w[p]++;
    }
    return p;
}

void build() {
    queue<int> q;
    for (int o = 0; o != 26; ++o) if (g[0][o]) q.push(g[0][o]);
    while(!q.empty()){
        int u = q.front(); q.pop();
        for (int o = 0; o != 26; ++o) {
            int& v = g[u][o];
            if (!v) v = g[f[u]][o];
            else f[v] = g[f[u]][o], q.push(v);
        }
    }
}

void clr() { nc = 0; gn(); }

int c[N], pos[N];
void sort_acam() {
    for (int i = 0; i != nc; ++i) c[l[i]] = 0;
    for (int i = 0; i != nc; ++i) c[l[i]]++;
    for (int i = 1; i != nc; ++i) c[i] += c[i - 1];
    for (int i = 0; i != nc; ++i) pos[--c[l[i]]] = i;
}

void solve(istream& cin, ostream& cout){
    int n; cin >> n;
    vector<int> vp;

    clr(); int ssum = 0;
    for (int i = 0; i != n; ++i) {
        string s; cin >> s;
        vp.push_back(ins(s));
        ssum += s.size();
    }
    //assert(ssum <= 1000000);
    build();

    sort_acam();

    for (int i = nc - 1; i > 0; --i)
        w[f[pos[i]]] += w[pos[i]];

    for (int i = 0; i != n; ++i)
        cout << w[vp[i]] << endl;
}

int main(void) {
    ios::sync_with_stdio(0); cin.tie(0);
    #ifndef ONLINE_JUDGE
    ifstream cin("2.in");
    #endif // ONLINE_JUDGE
    solve(cin, cout);
    return 0;
}