#include <bits/stdc++.h>
#include "../generator.h"
using namespace std;

void gen(int& id, const string& s) {
    ofstream cout(to_string(++id) + ".in");
    cout << s << endl;
    cout.close();
}

void gen_batch(int& id, int n) {
    gen(id, sgr(n, 'a', 'b'));
    gen(id, sgr(n, 'a', 'c'));
    gen(id, sgr(n, 'a', 'z'));
    gen(id, sgp(n, "ab"));
    gen(id, sgp(n, "aab"));
    gen(id, sqgp(n, "aabaabaa", log(n) / n, 'a', 'c'));
    gen(id, sqgr(n, 'a', log(n) / n, 'b', 'b'));
    gen(id, sqgr(n, 'a', log(n) / n, 'b', 'z'));
}

void solve(istream& cin, ostream& cout);

int main(void) {
    int id = 2;
    gen_batch(id, 10);
    gen_batch(id, 1000);
    gen_batch(id, 1000000);
    for (int i = 1; i <= id; ++i) {
        ifstream cin(to_string(i) + ".in");
        ofstream cout(to_string(i) + ".out");
        solve(cin, cout);
    }
    return 0;
}