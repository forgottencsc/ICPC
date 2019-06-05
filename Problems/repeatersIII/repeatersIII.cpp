#include <bits/stdc++.h>
using namespace std;

void getf(const string& s, vector<int>& f) {
    int n = s.size(); f.resize(n, 0);// f[0] = -1;
    for (int i = 1, j = 0; i != n; ++i) {
        while (j && s[i] != s[j]) j = f[j - 1];
        if (s[i] == s[j]) ++j;
        f[i] = j;
    }
}

void getl(const string& s, const string& t, const vector<int>& f, vector<int>& l) {
    int n = s.size(), m = t.size(); l.resize(m, 0);
    for (int i = 0, j = 0; i != m; ++i) {
        while(j && t[i] != s[j])
            j = f[j - 1];
        if (t[i] == s[j]) ++j;
        l[i] = j;
        if (j == n)
            j = f[j - 1];
    }
}

void solve(istream& cin, ostream& cout) {
    string s, t; vector<int> f, l;
    cin >> t >> s;
    getf(s, f); getl(s, t, f, l);
    for (int i = 0; i != l.size(); ++i)
        if (l[i] == s.size())
            cout << i - s.size() + 2 << ' ';
}

int main1(void) {
    ios::sync_with_stdio(0); cin.tie(0);
    #ifndef ONLINE_JUDGE
    ifstream cin("1.in");
    #endif // ONLINE_JUDG

    solve(cin, cout);

    return 0;
}

