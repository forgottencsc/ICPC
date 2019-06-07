#include <bits/stdc++.h>
#include "../generator.h"

using namespace std;
using namespace placeholders;

void gen(int& id, const vector<string>& sv) {
    ofstream cout(to_string(++id) + ".in");
    cout << sv.size() << endl;
    for (const string& s : sv) cout << s << endl;
    cout.close();
}

void gen(int& id, int n, const vector<sgen>& sgv,
         int minn = 0, int maxn = 0) {
    n = igr(4 * n / 5, n);
    gen(id, svg(sgv, n, minn, maxn));
    gen(id, svg3(sgv, n, log(n) * log(n)));
}

void gen_batch0(int& id, int n) {
    gen(id, n, { bind(sgr, _1, 'a', 'b'), bind(sqgp, _1, "abaab", 0.01, 'a', 'c') }, 1, 40);
    gen(id, n, { bind(sgr, _1, 'a', 'd') }, 4, 200);
    gen(id, n, { bind(sgr, _1, 'a', 'z') }, 10, 5);
    gen(id, n, { bind(sgr, _1, 'a', 'z') }, 10, 200);
}

void gen_batch1(int& id, int n) {
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
    gen(id, n, sgv);
}

void solve(istream& cin, ostream& cout);

int main(void) {
//    int id = 1;
//    gen_batch0(id, 100);
//    gen_batch1(id, 100);
//    gen_batch0(id, 50000);
//    gen_batch1(id, 50000);
//    gen_batch0(id, 1000000);
//    gen_batch1(id, 1000000);
//    gen(id, 1000000, { bind(sgr, _1, 'a', 'a') });
//    gen(id, 1000000, { bind(sgr, _1, 'a', 'b') }, 1, 40);
    for (int i = 1; i <= 35; ++i) {
        ifstream cin(to_string(i) + ".in");
        ofstream cout(to_string(i) + ".out");
        solve(cin, cout);
    }
    return 0;
}