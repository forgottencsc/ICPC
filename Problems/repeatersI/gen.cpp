#include <bits/stdc++.h>
#include "../generator.h"
using namespace std;

void solve(istream& cin, ostream& cout);

vector<string> svgen1(sgen g, int n) {
    vector<string> sv;
    int s = 0;
    for (int i = 1; s + i <= n; ++i) {
        sv.emplace_back(g(i));
        s += i;
    }
    reverse(sv.begin(), sv.end());
    return sv;
}

vector<string> svgen2(sgen g, int n) {
    vector<string> sv;
    int s = 0;
    for (int i = 1; s + i <= n; ++i) {
        sv.emplace_back(g(i));
        s += i;
    }
    shuffle(sv.begin(), sv.end(), mt);
    return sv;
}

vector<string> svgen3(sgen g, int n) {
    int w = sqrt(n);
    vector<string> sv;
    for (int i = 0; i != w; ++i)
        sv.emplace_back(g(w));
    return sv;
}

vector<string> svgen4(sgen g, int n) {
    int w = 0;
    vector<string> sv;
    while(w <= n) {
        string s = g(0);
        w += s.size();
        if (w <= n) sv.push_back(s);
    }
    return sv;
}

void gen(int& id, int n, svgen vg) {
    vector<string> sv = vg(n);
    ofstream dout(to_string(++id) + ".in");
    dout << sv.size() << endl;
    for (const string& s : sv)
        dout << s << endl;
    dout.close();
}

void gen_batch(int& id, int n) {
    gen(id, n, bind(svgen1, (sgen)(bind(sgr, _1, 'a', 'a')), _1));
    gen(id, n, bind(svgen1, (sgen)(bind(sqgr, _1, 0.01, 'a', 'b', 'z')), _1));
    gen(id, n, bind(svgen1, (sgen)(bind(sqgr, _1, 0.01, 'a', 'b', 'b')), _1));
    gen(id, n, bind(svgen1, (sgen)(bind(sgt, _1, "ab")), _1));
    gen(id, n, bind(svgen1, (sgen)(bind(sqgp, _1, "ab"s, 0.001, 'a', 'b')), _1));
    gen(id, n, bind(svgen2, (sgen)(bind(sgr, _1, 'a', 'a')), _1));
    gen(id, n, bind(svgen2, (sgen)(bind(sqgr, _1, 0.01, 'a', 'b', 'z')), _1));
    gen(id, n, bind(svgen2, (sgen)(bind(sqgr, _1, 0.01, 'a', 'b', 'b')), _1));
    gen(id, n, bind(svgen2, (sgen)(bind(sgt, _1, "ab")), _1));
    gen(id, n, bind(svgen2, (sgen)(bind(sqgp, _1, "ab"s, 0.001, 'a', 'b')), _1));
    gen(id, n, bind(svgen3, (sgen)(bind(sgr, _1, 'a', 'a')), _1));
    gen(id, n, bind(svgen3, (sgen)(bind(sqgr, _1, 0.01, 'a', 'b', 'z')), _1));
    gen(id, n, bind(svgen3, (sgen)(bind(sqgr, _1, 0.01, 'a', 'b', 'b')), _1));
    gen(id, n, bind(svgen3, (sgen)(bind(sgt, _1, "ab")), _1));
    gen(id, n, bind(svgen3, (sgen)(bind(sqgp, _1, "ab"s, 0.001, 'a', 'b')), _1));
    gen(id, n, bind(svgen4, (sgen)(bind(sg, "abcba"s)), _1));
    gen(id, n, bind(svgen4, (sgen)(bind(sg, "aba"s)), _1));
    gen(id, n, bind(svgen4, (sgen)(bind(sg, "a"s)), _1));
}

int main(void) {
    int id = 2;
    gen_batch(id, 10);
    gen_batch(id, 1000);
    gen_batch(id, 1000000);
    for (int i = 1; i <= id; ++i) {
        ifstream din(to_string(i) + ".in");
        ofstream aout(to_string(i) + ".out");
        solve(din, aout);
    }
    return 0;
}