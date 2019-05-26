#include <bits/stdc++.h>
using namespace std;
mt19937_64 mt(time(0) * 1145141919);


string gens_rnd1(int n, char cl = 'a', char cr = 'z') {
    uniform_int_distribution<char> rng(cl, cr);
    string r;
    for (int i = 0; i != n; ++i) r += rng(mt);
    return r;
}

string gens_rnd3(int n, double p = 0.1, char cm = 'x', char cl = 'a', char cr = 'z') {
    string r(n, cm);
    bernoulli_distribution rng(p);
    uniform_int_distribution<char> rng2(cl, cr);
    for (int i = 0; i != n; ++i)
        if (rng(mt))
            r[i] = rng2(mt);
    return r;
}

string gens_per(int n, string pattern) {
    string s;
    while(s.size() < n) s += pattern.substr(0, n - s.size());
    return s;
}

string gens_quasi_per(int n, string pattern, double p = 0.01, char cl = 'a', char cr = 'z') {
    string s = gens_per(n, pattern);
    bernoulli_distribution rng(p);
    uniform_int_distribution<char> rng2(cl, cr);
    for (int i = 0; i != n; ++i) {
        if (rng(mt))
            s[i] = rng2(mt);
    }
    return s;
}

void gen(function<string(int)> f1, function<string(int)> f2, int n, int id) {
    uniform_real_distribution<> nd(0.3, 1);
    ofstream dout(to_string(id) + ".in");
    dout << f1(n * nd(mt)) << endl << f2(n * nd(mt)) << endl;
}

void gen_batch(int& id, int n) {
    using namespace placeholders;
    vector<function<string(int)>> gensv = {
        bind(gens_rnd1, _1, 'a', 'a'),
        bind(gens_rnd1, _1, 'a', 'b'),
        bind(gens_rnd3, _1, 0.01, 'c', 'a', 'b'), //  %zh
        bind(gens_per, _1, "abababcbabab"),
        bind(gens_quasi_per, _1, "cccdeeeefeeeedccc", 0.01, 'a', 'c')
    };
    for (auto& f1 : gensv)
        for (auto& f2 : gensv)
            gen(f1, f2, n, ++id);
}

void solve(istream& cin, ostream& cout);

int main(void) {
    int id = 2;
    gen_batch(id, 20);
    gen_batch(id, 1000);
    gen_batch(id, 1000000);
    for (int i = 1; i <= id; ++i) {
        ifstream cin(to_string(i) + ".in");
        ofstream cout(to_string(i) + ".out");
        solve(cin, cout);
    }
}