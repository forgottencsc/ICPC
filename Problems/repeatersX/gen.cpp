#include <bits/stdc++.h>

using namespace std;

mt19937_64 mt(time(0) * 1145141919);
typedef pair<int, int> pii;
typedef pair<pii, pii> pp;

bool chk(string s) {
    int n = s.size();
    for (int i = 0; i != n; ++i) {
        if (!islower(s[i])) {
            cout << (int)s[i] << endl;
            exit(1145141919);
        }
    }
    return true;
}

string gens_rnd1(int n, char cl = 'a', char cr = 'z') {
    uniform_int_distribution<char> rng(cl, cr);
    string r;
    for (int i = 0; i != n; ++i) r += rng(mt);
    return r;
}

string gens_rnd2(int n, const vector<int>& w, char cl = 'a') {
    int sum = 0, cr = cl + w.size() - 1, m = w.size();
    for (int i = 0; i != m; ++i) sum += w[i];
    string s, r;
    for (int i = 0; i != m; ++i)
        for (int j = 0; j != w[i]; ++j) {
            s += (char)(cl + i);
            assert(cr <= 'z' && cl + i <= 'z');
        }
    uniform_int_distribution<int> rng(0, sum - 1);
    for (int i = 0; i != n; ++i)
        r += s[rng(mt)];
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

vector<pp> genq_rand(int n, int q) {
    uniform_int_distribution<int> rng(1, n);
    vector<pp> querys;
    for (int i = 0; i != q; ++i) {
        int l1 = rng(mt), r1 = rng(mt), l2 = rng(mt), r2 = rng(mt);
        if (l1 > r1) swap(l1, r1);
        if (l2 > r2) swap(l2, r2);
        querys.emplace_back(pii(l1, r1), pii(l2, r2));
    }
    return querys;
}

vector<pp> genq_rand1(int n, int q, double mu, double sigma) {
    uniform_int_distribution<int> rng(1, n);
    normal_distribution<double> rng2(mu, sigma);
    vector<pp> querys;
    for (int i = 0; i != q; ++i) {
        int l1 = rng(mt), r1 = rng2(mt), l2 = rng(mt), r2 = rng(mt);
        if (l2 > r2) swap(l2, r2);
        r1 = min(l1 + r1 * r1, n);
        querys.emplace_back(pii(l1, r1), pii(l2, r2));
    }
    return querys;
}

bool chk(int n, int w) {
    return 1 <= w && w <= n;
}

bool chk(int n, int l1, int r1, int l2, int r2) {
    return chk(n, l1) && chk(n, r1) && chk(n, l2) && chk(n, r2);
}

bool chk(int n, pp p) {
    return chk(n, p.first.first, p.first.second, p.second.first, p.second.second);
}

void gen(function<string(int)> gens,
         function<vector<pp>(int, int)> genq,
         int n, int q, int id) {
    ofstream dout(to_string(id) + ".in");
    dout << n << ' ' << q << endl;
    const string s = gens(n);
    chk(s);
    dout << s << endl;
    vector<pp> querys = genq(n, q);
    for (pp p : querys) {
        if (!chk(n, p))
            exit(114514);
        dout << p.first.first << ' ' << p.first.second << ' ' << p.second.first << ' ' << p.second.second << endl;
    }
}

void chk_bf(istream& cin, istream& cout) {
    int n, q; cin >> n >> q;
    string s; cin >> s;
    for (int i = 1; i <= q; ++i) {
        int l1, r1, l2, r2;
        cin >> l1 >> r1 >> l2 >> r2;
        string s1 = s.substr(l1 - 1, r1 - l1 + 1),
               s2 = s.substr(l2 - 1, r2 - l2 + 1);

        size_t pos = 0, res = 0, ans;
        while(1) {
            pos = s2.find(s1, pos);
            if (pos == string::npos)
                break;
            else {
                res++;
                pos++;
            }
        }
        cout >> ans;
        if (res != ans) {
            cerr << i << ' ' << res << ' ' << ans << endl;
            cerr << s << ':' << s1 << ':' << s2 << endl;
            exit(1145141919);
        }
    }
}

void solve(istream&, ostream&);

void gen_batch(int& id, int n, int q, bool do_chk) {
    int idl = id, idr = id;
    if (1) {
        using namespace std::placeholders;
        vector<function<string(int)>> gensv = {
            bind(gens_rnd1, _1, 'a', 'z'),
            bind(gens_rnd1, _1, 'd', 'g'),
            //bind(gens_rnd2, _1, vector<int>{ 20, 5 }, 'a'),
            bind(gens_rnd2, _1, vector<int>{ 20, 10, 5, 1 }, 'h'),
            bind(gens_rnd3, _1, 0.2, 'x', 'a', 'c'),
            //bind(gens_rnd3, _1, 0.05, 'x', 'a', 'b'),
            bind(gens_per, _1, string("aaaabaaaaaaabbbaabaaaaab")),
            bind(gens_quasi_per, _1, string("aaaababbabbbbabbbbbbb"), 0.1, 'a', 'h'),
        };

        vector<function<vector<pp>(int, int)>> genqv = {
            bind(genq_rand, _1, _2),
            bind(genq_rand1, _1, _2, 8, 6)
        };

        for (auto& fs : gensv)
            for (auto&  fq : genqv) {
                gen(fs, fq, n, q, ++idr);
            }

    }
    if (1) for (int i = idl + 1; i <= idr; ++i) {
        ifstream cin(to_string(i) + ".in");
        ofstream dout(to_string(i) + ".out");
        solve(cin, dout);
        cin.close();
        dout.close();
        cout << i << ' ';
    }
    if (do_chk) {
        for (int i = idl + 1; i <= idr; ++i) {
            ifstream cin(to_string(i) + ".in");
            ifstream cout(to_string(i) + ".out");
            chk_bf(cin, cout);
            cin.close();
            cout.close();
        }
    }
    id = idr;
    cout << endl << string(79, '%') << endl;
}

int main(void) {
    int id = 0;
    gen_batch(id, 10, 10, true);
    gen_batch(id, 1000, 1000, true);
    gen_batch(id, 500000, 500000, false);
    return 0;
}
