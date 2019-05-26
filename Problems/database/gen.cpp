#include <bits/stdc++.h>

mt19937_64 mt(time(0) * 1145141919);
void gen(int n, int q, int vm, int id) {
    ofstream dout(to_string(id) + ".in");
    ofstream aout(to_string(id) + ".out");
    uniform_int_distribution<int> ad(1, vm), xd(1, n);
    vector<ul> a(n);
    for (int i = 1; i <= n; ++i) a[i - 1] = ad(mt);

    dout << n << ' ' << q << endl;
    for (int w : a) dout << w << ' ';
    dout << endl;
    while(q--) {
        int o = (xd(mt) % 2) + 1;
        dout << o << ' ';
        if (o == 1) {
            int l = xd(mt), r = xd(mt); ul v = ad(mt);
            dout << l << ' ' << r << ' ' << v << endl;
        }
        else if(o == 2) {
            int x = xd(mt);
            dout << x << endl;
            //ul ans = 0;
            //for (int i = l; i <= r; ++i) ans += s[i - 1];
            //aout << ans << endl;
        }
    }
    dout.close();
    //aout.close();
}

void test(int id) {
    ifstream cin(to_string(id) + ".in");
    ofstream aout(to_string(id) + ".out");
    int q; cin >> n >> q;
    for (int i = 1; i <= n; ++i) a[i] = 0;
    for (int i = 1; i <= n; ++i) {
        int v; cin >> v;
        modify(i, v);
    }

    while(q--) {
        int o;
        cin >> o;
        if(o == 1) {
            int x, v;
            cin >> x >> v;
            modify(x, v);
        }
        else if (o == 2) {
            int l, r;
            cin >> l >> r;
            ul res = query(r) - query(l - 1);
            aout << res << endl;
            //ul ans; ain >> ans;
            //assert(res == ans);
        }
    }
}

int gen_data(void) {
    for (int i = 1; i <= 5; ++i) gen(10, 10, 10, i);
    for (int i = 6; i <= 10; ++i) gen(1000, 1000, 1000, i);
    for (int i = 11; i <= 15; ++i) gen(100000, 100000, 1000000000, i);
    for (int i = 16; i <= 20; ++i) gen(1000000, 1000000, 1000000000, i);
    for (int i = 1; i <= 20; ++i) test(i);
}
