#include <bits/stdc++.h>
#include "../generator.h"
using namespace std;

void gen(int& id, const vector<pair<string, int>>& sv, int l) {
    ofstream cout(to_string(++id) + ".in");
    cout << sv.size() << endl;
    for (int i = 0; i != sv.size(); ++i) {
        cout << sv[i].first << ' ' << sv[i].second << endl;
    }
    cout << igr(2 * l / 3, l) << endl;
    cout.close();
}

void gen(int& id, int n, svgen vg, int l, int w) {
    vector<pair<string, int>> sv;
    auto v = vg(n);
    for (const string& s : v)
        sv.emplace_back(s, igr(w / 10, w));
    gen(id, sv, l);
}

void gen(int& id, int n, const vector<sgen>& sgv, int l) {
    gen(id, n, bind(svg, sgv, _1, 0, 0), l, 400);
    gen(id, n, bind(svg, sgv, _1, 1, 5), l, 400);
    gen(id, n, bind(svg, sgv, _1, 1, n / 2), l, 400);
    gen(id, n, bind(svg, sgv, _1, 1, n / 5), l, 400);
}

void gen(int& id, int n, int l) {
    gen(id, n, vector<sgen>{ bind(sgr, _1, 'a','b') }, l);
    gen(id, n, vector<sgen>{ bind(sgr, _1,'a','b'), bind(sgr, _1,'b','c') }, l);
    gen(id, n, vector<sgen>{ bind(sgr, _1,'a','c') }, l);
    gen(id, n, vector<sgen>{ bind(sgr, _1,'a','z') }, l);
}

void solve(istream& cin, ostream& cout);
bool chk(istream& cin, istream& cout);

int main(void) {
//    int id = 1;
//    gen(id, 10, 20);
//    gen(id, 100, 500);
//    gen(id, 500, 2000);
    for (int i = 1; i <= 49; ++i) {
        ifstream cin(to_string(i) + ".in");
//
//        ofstream cout(to_string(i) + ".out");
//        solve(cin, cout);

        ifstream dout(to_string(i) + ".out");
        cout << boolalpha << chk(cin, dout) << endl;
    }
}