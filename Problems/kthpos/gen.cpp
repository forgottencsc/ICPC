#include "../generator.h"

struct query { int l, r, k; };

void gen(ostream& cout, string s, const vector<query>& q) {
    cout << s.size() << ' ' << q.size() << endl;
    int n = s.size() / 200;
    for (int i = 0; i != n; ++i)
        s[s.size() - (n - i)] = igr('a', 'z');
    cout << s << endl;
    for (const query& w : q) {
        cout << w.l << ' ' << w.r << ' ' << w.k << endl;
    }
}

void gen1(ostream& os, int n, int q) {
    string s = sgr(n, 'a', 'b');
    stq(s, 0.01, 'c', 'z');
    vector<query> qs;
    uniform_int_distribution<int> ul(1, n);
    while(q--) {
        int len = max((int)(sqrt(n) - sqrt(ul(mt))), 2);
        uniform_int_distribution<int> up(1, n - len + 1);
        int pos = up(mt);
        len = min(len, n - pos + 1);
        int l = pos, r = pos + len - 1;
        uniform_int_distribution<int> uk(1, sqrt(n / len));
        int k = uk(mt);
        qs.push_back({ l, r, k });
    }
    gen(os, s, qs);
}

void gen2(ostream& os, int n, int q) {
    string s = sqgp(n, sgr(log(n), 'a', 'b'), log(n) / n, 'c', 'c');
    vector<query> qs;
    uniform_int_distribution<int> ul(1, n);
    while(q--) {
        int len = max((n / cbrt(ul(mt))), 2.);
        uniform_int_distribution<int> up(1, n - len + 1);
        int pos = up(mt);
        len = min(len, n - pos + 1);
        int l = pos, r = pos + len - 1;
        uniform_int_distribution<int> uk(1, sqrt(n / len));
        int k = uk(mt);
        qs.push_back({ l, r, k });
    }
    gen(os, s, qs);
}

void gen3(ostream& os, int n, int q) {
    string s = sqgr(n, 'w', log(n) / n, 'v', 'v');
    vector<query> qs;
    while(q--) {
        int l = igr(1, n), r = igr(1, n);
        int k = igr(1, pow(n, 0.66));
        if (l > r) swap(l, r);
        qs.push_back({ l, r, k });
    }
    gen(os, s, qs);
}

void gen4(ostream& os, int n, int q) {
    string s = sqgr(n, 'w', log(n) / n, 'v', 'v');
    vector<query> qs;
    uniform_int_distribution<int> ul(1, n);
    while(q--) {
        int len = max((n / ul(mt)), 2);
        uniform_int_distribution<int> up(1, n - len + 1);
        int pos = up(mt);
        len = min(len, n - pos + 1);
        int l = pos, r = pos + len - 1;
        uniform_int_distribution<int> uk(1, pow(n, 0.8));
        int k = uk(mt);
        qs.push_back({ l, r, k });
    }
    gen(os, s, qs);
}

void solve_bf(istream& cin, ostream& cout);

void solve(istream& cin, ostream& cout);

int main(void) {
    ofstream o("1.in");

    o << 16 << endl;
    gen(o, "aaabaabaaaab", {
        { 3, 3, 4 },
        { 2, 3, 2 },
        { 7, 8, 3 },
        { 3, 4, 2 },
        { 1, 4, 2 },
        { 8, 12, 1 }
    });
    gen(o, "a", {
        { 1, 1, 1 }
    });
    gen(o, "ababa", {
        { 1, 2, 1 },
        { 1, 2, 2 },
        { 3, 4, 1 },
        { 3, 4, 2 },
        { 1, 3, 2 },
        { 3, 5, 1 }
    });
    int m = 500;
    gen1(o, m, m);
    gen2(o, m, m);
    gen3(o, m, m);
    gen3(o, m, m);
    gen3(o, m, m);
    gen3(o, m, m);
    gen3(o, m, m);
    gen3(o, m, m);
    gen3(o, m, m);
    m = 100000;
    gen1(o, m, m);
    gen3(o, m, m);
    gen4(o, m, m);
    gen2(o, m, m);
    o.close();

    string fo = "1.out";
    {
        ifstream in("1.in");
        ofstream out(fo);
        solve(in, out);
    }

//    string fc = "1.chk";
//    {
//        ifstream in("1.in");
//        ofstream out(fc);
//        solve_bf(in, out);
//    }
//    system("fc 1.out 1.chk");
//    m = 100000;
//    gen1(o, m, m);
//    gen2(o, m, m);
//    gen3(o, m, m);
}
