#include <bits/stdc++.h>
#include "../generator.h"

using namespace std;
using namespace placeholders;

void gen(int id, int n, int m, sgen tg, const vector<sgen>& sgv,
         int minn = 0, int maxn = 0) {
    n = igr(2 * n / 3, n);
    ofstream cout(to_string(id) + ".in");
    cout << tg(n) << endl;

    vector<string> sv = svgen(sgv, m, minn, maxn);
    cout << sv.size() << endl;
    for (const string& s : sv)
        cout << s << endl;
    cout.close();
}

void gen_batch0(int& id, int n, int m) {
    gen(++id, n, m, bind(sgr, _1, 'a', 'b'),
        { bind(sgr, _1, 'a', 'b') }, 1, 40);
    gen(++id, n, m, bind(sgr, _1, 'a', 'd'),
        { bind(sgr, _1, 'a', 'd') }, 4, 200);
    gen(++id, n, m, bind(sgr, _1, 'a', 'z'),
        { bind(sgr, _1, 'a', 'z') }, 10, 2000);
    gen(++id, n, m, bind(sgr, _1, 'a', 'z'),
        { bind(sgr, _1, 'a', 'z') }, 10, 10000);
}

void gen_batch1(int& id, int n, int m) {
    vector<sgen> sgv = {
        bind(sgr, _1, 'a', 'b'),
        bind(sgt, _1, "aab"),
        bind(sgt, _1, "baa"),
        bind(sg, "abaaaba"),
        bind(sg, "aabaaabaaaab"),
        bind(sg, "ab"),
        bind(sg, "ababa"),
        bind(sg, "aaab")
    };
    gen(++id, n, m, bind(sgr, _1, 'a', 'b'), sgv);
    gen(++id, n, m, bind(sqgp, _1, "aab"s, 0.01, 'a', 'b'), sgv);
    gen(++id, n, m, bind(sqgp, _1, "baa"s, 0.01, 'a', 'b'), sgv);
    gen(++id, n, m, bind(sqgp, _1, "bba"s, 0.01, 'a', 'b'), sgv);
    gen(++id, n, m, bind(sqgp, _1, "abb"s, 0.01, 'a', 'b'), sgv);
    gen(++id, n, m, bind(sqgp, _1, "aab"s, 0.01, 'a', 'b'), sgv);
    gen(++id, n, m, bind(sqgp, _1, "ab"s, 0.01, 'a', 'b'), sgv);
    gen(++id, n, m, bind(sqgp, _1, "aaab"s, 0.01, 'a', 'b'), sgv);
    gen(++id, n, m, bind(sgp, _1, "aab"s), sgv);
    gen(++id, n, m, bind(sgp, _1, "baa"s), sgv);
    gen(++id, n, m, bind(sgp, _1, "bba"s), sgv);
    gen(++id, n, m, bind(sgp, _1, "abb"s), sgv);
    gen(++id, n, m, bind(sgp, _1, "aab"s), sgv);
    gen(++id, n, m, bind(sgp, _1, "ab"s), sgv);
    gen(++id, n, m, bind(sgp, _1, "aaab"s), sgv);
}

void solve(istream& cin, ostream& cout);

int main(void) {
    int id = 1;
    gen_batch0(id, 100, 50);
    gen_batch1(id, 100, 50);
    gen_batch0(id, 50000, 10000);
    gen_batch1(id, 50000, 10000);
    gen_batch0(id, 1000000, 100000);
    gen_batch1(id, 1000000, 100000);
    gen(++id, 1000000, 100000, bind(sgr, _1, 'a', 'a'), { bind(sgr, _1, 'a', 'a') });
    gen(++id, 1000000, 100000, bind(sgp, _1, "ab"), { bind(sgr, _1, 'a', 'b') }, 1, 10);
    for (int i = 1; i <= id; ++i) {
        ifstream cin(to_string(i) + ".in");
        ofstream cout(to_string(i) + ".out");
        solve(cin, cout);
    }
}

