#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

#define N 500001
#define M N * 30
using namespace std;

int c[M][2], sz[M], sc;

using namespace __gnu_pbds;
tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> s;

void insert(int v) {
    int p = 0;
    for (int i = 29; i >= 0; --i){
        int o = (v >> i) & 1;
        if (!c[p][o]) c[p][o] = ++sc;
        p = c[p][o]; sz[p]++;
    }
}

void erase(int v) {
    int p = 0;
    for (int i = 29; i >= 0; --i) {
        int o = (v >> i) & 1;
        p = c[p][o]; sz[p]--;
    }
}

int find_min(int v) {
    int p = 0, res = 0;
    for (int i = 29; i >= 0; --i) {
        int o = (v >> i) & 1;
        if (sz[c[p][o]])
            p = c[p][o];
        else {
            p = c[p][!o];
            res |= (1 << i);
        }
    }
    return res;
}

int find_max(int v) {
    int p = 0, res = (1 << 30) - 1;
    for (int i = 29; i >= 0; --i) {
        int o = (v >> i) & 1;
        if (sz[c[p][!o]])
            p = c[p][!o];
        else {
            p = c[p][o];
            res &= ~(1 << i);
        }
    }
    return res;
}

pair<int, int> bf(int v) {
    int minval = INT_MAX, maxval = INT_MIN;
    for (int i : s) {
        minval = min(minval, i ^ v);
        maxval = max(maxval, i ^ v);
    }
    return { minval, maxval };
}

mt19937_64 mt(time(0));

int ww(int o) {
    if (o <= 3) return 1;
    else if(o <= 7) return 3;
    else return 2;
}

void gen(int id, int n, int am, bool chk = false) {
    cout << id << endl;
    this_thread::sleep_for(100ms);
    ofstream dout(to_string(id) + ".in");
    ofstream aout(to_string(id) + ".out");

    uniform_int_distribution ad(1, am);

    memset(c, 0, sizeof(c));
    memset(sz, 0, sizeof(sz));
    s.clear();
    sc = 0;

    dout << n << endl;
    for (int i = 1; i <= n; ++i) {
        int o = ww(ad(mt) % 10), v = ad(mt);
        if (o != 1 && !s.size()) o = 1;
        if (o == 1) {
            insert(v);
            s.insert(v);
        }
        else if(o == 2) {
            uniform_int_distribution<int> dd(0, s.size() - 1);
            auto it = s.find_by_order(dd(mt));
            v = *it;
            erase(*it);
            s.erase(it);
        }
        else if (o == 3){
            int minval = find_min(v),
                maxval = find_max(v);

            if (chk) {
                int bminval, bmaxval;
                tie(bminval, bmaxval) = bf(v);
                assert(bminval == minval);
                assert(bmaxval == maxval);
            }
            aout << minval << ' ' << maxval << endl;
        }
        dout << o << ' ' << v << endl;
    }
    cout << s.size() << endl;
}

int main(void) {
    int mv = (1<<30) - 1;
    for (int i = 2; i <= 11; ++i)
        gen(i, 1000, mv, true);
    for (int i = 12; i <= 21; ++i)
        gen(i, 500000, mv, false);
}