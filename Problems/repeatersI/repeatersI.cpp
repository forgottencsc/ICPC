#include <bits/stdc++.h>
#define N 2000002
using namespace std;

int g[N][26], sz[N], nc;

int gn() {
    int p = nc++;
    memset(g[p], 0, sizeof(g[p]));
    sz[p] = 0;
    return p;
}

void clr() { nc = 0; gn(); gn(); }

int ins(const string& s, int p) {
    for (char ch : s) {
        int o = ch - 'a';
        if (!g[p][o]) g[p][o] = gn();
        p = g[p][o];
        sz[p]++;
    }
    return sz[p] - 1;
}

void solve(istream& cin, ostream& cout) {
    int n; cin >> n;
    clr();
    for (int i = 1; i <= n; ++i) {
        string s; cin >> s;
        cout << ins(s, 0) << ' ';
        reverse(s.begin(), s.end());
        cout << ins(s, 1) << endl;
    }
}

int main1(void) {
    ios::sync_with_stdio(0); cin.tie(0);
    #ifndef ONLINE_JUDGE
    ifstream cin("1.in");
    #endif
    solve(cin, cout);
    return 0;
}
