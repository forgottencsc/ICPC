#include <bits/stdc++.h>
#include "../generator.h"
using namespace std;

void gen(int& id, const string& s, int t) {
    ofstream cout(to_string(++id) + ".in");
    cout << s << endl << igr(t / 2, t) << endl;
    cout.close();
}

void gen_batch(int& id, int n, int t) {
    gen(id, sqgp(n, "1111122211111", 0.001, '3', '5'), t);
    gen(id, sqgp(n, "1112111", 0.001, '3', '5'), t);
    gen(id, sqgp(n, "122221", 0.001, '3', '5'), t);
    gen(id, sqgp(n, "1145141919810", 0.001, '3', '5'), t);
    gen(id, sqgr(n, 0.01, '1', '2', '3'), t);
    gen(id, sqgr(n, 0.0001, '1', '2', '3'), t);
    gen(id, sqgr(n, 0.01, '1', '1', '1'), t);
    gen(id, sqgr(n, 0.01, '0', '1', '9'), t);
    gen(id, sgr(n, '0', '9'), t);
    gen(id, sgr(n, '0', '1'), t);
    gen(id, sgr(n, '1', '1'), t);
}

void solve(istream& cin, ostream& cout);

int main(void) {
    ios::sync_with_stdio(0); cin.tie(0);
    #ifndef ONLINE_JUDGE
    ifstream cin("1.in");
    #endif // ONLINE_JUDGE
    int id = 1;
    gen_batch(id, 100, 10000);
    gen_batch(id, 10000, 1000000);
    gen_batch(id, 1000000, 1000000000);
    for (int i = 1; i <= id; ++i) {
        ifstream cin(to_string(i) + ".in");
        ofstream cout(to_string(i) + ".out");
        solve(cin, cout);
    }
    return 0;
}