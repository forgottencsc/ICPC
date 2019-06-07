#include <bits/stdc++.h>
using namespace std;
using namespace placeholders;
mt19937_64 mt(chrono::system_clock::now().time_since_epoch().count());

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
string sqgr(int n, double p, char cm, char cl, char cr) {
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