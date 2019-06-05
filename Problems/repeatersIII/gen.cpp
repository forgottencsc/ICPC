#include <bits/stdc++.h>
#include "../generator.h"
using namespace std;

void gen(int& id, const string& s, const string& t) {
    ofstream cin(to_string(++id) + ".in");
    cin << s << endl;
    cin << t << endl;
    cin.close();
}

void gen(int& id, int n, function<int(int)> fn, sgen s1, sgen s2) {
    n = igr(3 * n / 4, n);
    gen(id, s1(n), s2(fn(n)));
}

void gen(int& id, int n, sgen s1, sgen s2) {
    gen(id, n, [](int n) { return log(n); }, s1, s2);
    gen(id, n, [](int n) { return n / 2; }, s1, s2);
    gen(id, n, [](int n) { return n / 4; }, s1, s2);
}

void gen_batch(int& id, int n) {
    gen(id, n, bind(sqgp, _1, "aab", 0.1, 'a', 'b'), bind(sg, "aab"));
    gen(id, n, bind(sqgp, _1, "aabaab", 0.01, 'a', 'b'), bind(sg, "aab"));
    gen(id, n, bind(sqgp, _1, "aabbaabbaa", 0.001, 'a', 'b'), bind(sg, "aabba"));
    gen(id, n, bind(sqgr, _1, 0.00001, 'a', 'b', 'b'), bind(sgr, _1, 'a', 'a'));
    gen(id, n, bind(sqgr, _1, 0.000001, 'a', 'b', 'b'), bind(sgr, _1, 'a', 'a'));
}

void solve(istream& cin, ostream& cout);

int main(void) {
    int id = 1;
    gen_batch(id, 10);
    gen_batch(id, 1000);
    gen_batch(id, 1000000);
    for (int i = 1; i <= id; ++i) {
        ifstream cin(to_string(i) + ".in");
        ofstream cout(to_string(i) + ".out");
        solve(cin, cout);
    }
}