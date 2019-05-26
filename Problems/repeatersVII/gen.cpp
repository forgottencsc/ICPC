#include <bits/stdc++.h>
using namespace std;

mt19937_64 mt(time(0));

string gens(int n, char cl = 'a', char cr = 'z') {
    string s(n, cl);
    uniform_int_distribution<int> uid(cl, cr);
    for (int i = 0; i != n; ++i)
        s[i] = uid(mt);
    return s;
}

void gen(int id, int n, ul l, int minl = 0, int maxl = 0, char cl = 'a', char cr = 'z') {
    {
        ofstream cout(to_string(id) + ".in");
        if (!minl) minl = 3;
        if (!maxl) maxl = max(n / 5, minl);
        uniform_int_distribution<int> nd(1, n);
        uniform_int_distribution<ul> ld(1, l);
        l = ld(mt);
        n = (n + nd(mt)) / 2;
        vector<string> sv;
        int r = n;
        while(r) {
            uniform_int_distribution<int> wd(minl, min(maxl, r));
            int w = wd(mt);
            if (r - w < minl) w = r;
            sv.push_back(gens(w, cl, cr));
            r -= w;
        }
        cout << sv.size() << endl;
        for (int i = 0; i != sv.size(); ++i)
            cout << sv[i] << endl;
        cout << l << endl;
        cout.close();
    }
    {
        ifstream cin(to_string(id) + ".in");
        ofstream wout(to_string(id) + ".out");
        solve(cin, wout);
        cout << id << endl;
    }
}

void gen() {
    gen(1, 4, 3, 1, 2, 'a', 'c');
    for (int i = 2; i <= 5; ++i)
        gen(i, 10, 10, 0, 0, 'a', 'b');
    for (int i = 6; i <= 10; ++i)
        gen(i, 20, 100, 0, 0, 'a', 'd');
    for (int i = 11; i <= 15; ++i)
        gen(i, 200, 1000000000000000000, 0, 0, 'a', 'b');
    for (int i = 16; i <= 20; ++i)
        gen(i, 200, 1000000000000000000, 5, 15, 'a', 'z');
}