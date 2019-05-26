#include <bits/stdc++.h>
using namespace std;
#define N 2000001

int go[N][26], sz[N], sc = 3;

int ins(int p, const string& str) {
    sz[p]++;
    for (char ch : str) {
        int o = ch - 'a';
        if (!go[p][o]) go[p][o] = sc++;
        p = go[p][o];
        sz[p]++;
    }
    return sz[p] - 1;
}

void solve(istream& cin, ostream& cout) {
    int n; cin >> n;
    while(n--) {
        string s; cin >> s;
        int ans1 = ins(1, s);
        reverse(s.begin(), s.end());
        int ans2 = ins(2, s);
        cout << ans1 << ' ' << ans2 << endl;
    }
}

int main(void) {
    ios::sync_with_stdio(0); cin.tie(0);
    #ifndef ONLINE_JUDGE
    ifstream cin("1.in");
    #endif // ONLINE_JUDG

    solve(cin, cout);

    return 0;
}

/*
5
aabaa
aab
baa
aa
a

*/
