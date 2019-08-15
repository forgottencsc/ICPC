#include <bits/stdc++.h>

using namespace std;

void solve_bf(istream& cin, ostream& cout) {
    int t; cin >> t;
    while(t--) {
        int n, q;
        string s;
        cin >> n >> q >> s;
        if (n > 500) break;
        map<string, vector<int>> m;
        for (int i = 0; i != n; ++i)
            for (int j = i + 1; j <= n; ++j)
                m[s.substr(i, j - i)].push_back(i + 1);
        while(q--) {
            int l, r, k;
            cin >> l >> r >> k;
            vector<int>& pos = m[s.substr(l - 1, r - l + 1)];
            if (pos.size() < k)
                cout << -1 << endl;
            else
                cout << pos[k - 1] << endl;
        }
    }
}

int main2(void) {
    solve_bf(cin, cout);
    return 0;
}
