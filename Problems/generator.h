#include <bits/stdc++.h>
using namespace std;
using namespace placeholders;
mt19937_64 mt(chrono::system_clock::now().time_since_epoch().count());
#define gfs(in, out) \
    ifstream in(to_string(i) + ".in"); \
    ofstream out(to_string(i) + ".out");

#define cfs(in, out) \
    ifstream in(to_string(i) + ".in"); \
    ifstream out(to_string(i) + ".out");



typedef long long ll;

inline ll igr(int lb, int rb) {
    return uniform_int_distribution<ll>(lb, rb)(mt);
}

inline bool bgr(double p) {
    return bernoulli_distribution(p)(mt);
}
inline ll bgr(double p, ll i1, ll i2) { return bgr(p) ? i1 : i2; }

typedef function<string(int)> sgen;
typedef function<vector<string>(int)> svgen;

//  dope string s with characters in [cl,cr]
void stq(string& s, double p, char cl, char cr) {
    for (char& ch : s) if (bgr(p)) ch = igr(cl, cr);
}

//  generate a string with all characters from t
string sgt(int n, const string& t) {
    string s(n, '%');
    for (char& ch : s) ch = t[igr(0, t.size() - 1)];
    return s;
}

//  generate a string with all characters in [cl, cr]
string sgr(int n, char cl, char cr) {
    string s(n, '%');
    stq(s, 1, cl, cr);
    return s;
}

//  generate a string with pattern t
string sgp(int n, const string& t) {
    string s;
    while(s.size() + t.size() < n) s += t;
    s += t.substr(0, n - s.size());
    return s;
}

string sg(const string& t) { return t; }

//  generate a string consisting mainly of cm with [cl, cr] doped.
string sqgr(int n, char cm, double p, char cl, char cr) {
    string s(n, cm);
    stq(s, p, cl, cr);
    return s;
}

//  generate a string consisting of pattern with [cl, cr] doped.
string sqgp(int n, const string& t, double p, char cl, char cr) {
    string s = sgp(n, t);
    stq(s, p, cl, cr);
    return s;
}

vector<string> svg(const vector<sgen>& sgv, int n, int minn = 0, int maxn = 0) {
    if (!maxn) maxn = n / 10;
    //if (!maxn) maxn = n;
    if (!minn) minn = 4;
    if (minn > min(n, maxn)) minn = 1;
    vector<string> sv;
    while(n) {
        int len;
        if (n < minn) break;
        else len = igr(minn, min(n, maxn));
        if (n - len < minn) len = n;
        string s = sgv[igr(0,sgv.size()-1)](len);
        sv.push_back(s);
        n -= s.size();
    }
    return sv;
}

vector<string> svg2(const vector<sgen>& sgv, int n, int minn = 0, int maxn = 0) {
    if (!maxn) maxn = n / 10;
    //if (!maxn) maxn = n;
    if (!minn) minn = 4;
    if (minn > min(n, maxn)) minn = 1;
    vector<string> sv;
    set<string> ss;
    while(n) {
        int len;
        if (n < minn) break;
        else len = igr(minn, min(n, maxn));
        if (n - len < minn) len = n;
        string s = sgv[igr(0,sgv.size()-1)](len);
        if (ss.insert(s).second)
            sv.push_back(s);
        n -= s.size();
    }
    return sv;
}

vector<string> svg3(const vector<sgen>& sgv, int n, int avg) {
    poisson_distribution<int> pd(avg);
    vector<string> sv;
    while(n) {
        int len = pd(mt) + 1;
        for (int i = 0; i != 10 && len > n; ++i)
            len = pd(mt) + 1;
        len = min(len, n);
        string s = sgv[igr(0,sgv.size()-1)](len);
        sv.push_back(s);
        n = max(n - (int)s.size(), 0);
    }
    return sv;
}

typedef pair<int, int> pii;
struct tree {
    int n;
    tree() : n(0) {}
    vector<pii> g;
    void print() {
        cout << n << endl;
        for (pii e : g)
            cout << e.first << ' ' << e.second << endl;
    }

    void check() {
        assert(g.size() == n - 1);
    }

};

//  Random tree
tree tgr(int n) {
    tree t; t.n = n;
    for (int i = 2; i <= t.n; ++i) {
        t.g.emplace_back(igr(1, i - 1), i);
    }
    return t;
}

//  Star shaped tree
tree tgs(int n, int d = 0) {
    tree t; t.n = n;
    if (!d) d = sqrt(n);
    for (int i = 2; i <= t.n; ++i) {
        if (i % d) t.g.emplace_back(i, i - 1);
        else t.g.emplace_back(i, 1);
    }
    return t;
}

//  List shaped tree
tree tgl(int n) {
    tree t; t.n = n;
    for (int i = 2; i <= t.n; ++i)
        t.g.emplace_back(i - 1, i);
    return t;
}

void tconn(tree& t1, int u, tree t2, int v) {
    for (pair<int, int> e : t2.g)
        t1.g.emplace_back(e.first + t1.n, e.second + t1.n);
    t1.g.emplace_back(u, v + t1.n);
    t1.n = t1.g.size() + 1;
}

//  Connect 2 tree randomly
void tconn(tree& t1, tree t2) {
    if (!t1.n)
        t1 = t2;
    else {
//        t1.print();
//        t1.check();
//        cout << "---" << endl;
//        t2.print();
//        t1.check();
//        cout << "---" << endl;
        tconn(t1, igr(1, t1.n), t2, igr(1, t2.n));
//        t1.print();
//        t1.check();
    }
    return;
}

tree tg1(int n) {
    tree t;
    int blo = sqrt(n);
    while (n) {
        int r = igr(1, 3);
        int m = blo;
        if (n < 2 * blo) m = n;
        m = min(m, n);
        assert(m);
        if (r == 1)
            tconn(t, tgr(m));
        if (r == 2)
            tconn(t, tgs(m));
        if (r == 3)
            tconn(t, tgl(m));
        n -= m;
    }
    return t;
}

tree tg2(int n) {
    tree t;
    int blo = cbrt(n);
    while (n) {
        int r = igr(1, 3);
        int m = blo;
        if (n < 2 * blo) m = n;
        m = min(m, n);
        assert(m);
        if (r == 1)
            tconn(t, tgr(m));
        else
            tconn(t, tgl(m));
        n -= m;
    }
    return t;
}

tree tg3(int n) {
    tree t;
    int blo = sqrt(n);
    while (n) {
        int r = igr(1, 3);
        int m = blo;
        if (n < 2 * blo) m = n;
        m = min(m, n);
        assert(m);
        if (r == 1)
            tconn(t, tgs(m));
        else
            tconn(t, tgl(m));
        n -= m;
    }
    return t;
}

tree tg(int n) {
    int r = igr(1, 10);
    tree t;
    if (r == 10)
        t = tgr(n);
    if (r % 3 == 0)
        t = tg1(n);
    if (r % 3 == 1)
        t = tg2(n);
    if (r % 3 == 2)
        t = tg3(n);
    return t;
}

template<class T>
void shuffle(T& t) {
    vector<int> per(t.n + 1);
    iota(per.begin(), per.end(), 0);
    shuffle(per.begin() + 1, per.end(), mt);
    for (pair<int, int>& e : t.g) {
        e.first = per[e.first];
        e.second = per[e.second];
    }
}
