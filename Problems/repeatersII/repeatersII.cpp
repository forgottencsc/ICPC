#include <bits/stdc++.h>
#define N 1000001
using namespace std;

char s[N]; int f[N];

void solve(istream& cin, ostream& cout) {
    cin >> s; int n = strlen(s);
    for (int i = 1, j = 0; i != n; ++i) {
        while (j && s[i] != s[j]) j = f[j - 1];
        if (s[i] == s[j]) ++j;
        f[i] = j;
    }
    int p = n;
    while(p = f[p - 1])
        cout << n - p << ' ';
    cout << n << endl;
}

int main(void) {
    ios::sync_with_stdio(0); cin.tie(0);
    #ifndef ONLINE_JUDGE
    ifstream cin("1.in");
    #endif
    solve(cin, cout);
//    for (int id = 1; id <= 20; ++id) {
//        ifstream cin(to_string(id) + ".in");
//        ofstream cout(to_string(id) + ".out");
//        solve(cin, cout);
//    }
    return 0;
}
