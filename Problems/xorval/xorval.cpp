#include <bits/stdc++.h>
#define N 500001
#define M N * 30
using namespace std;

int c[M][2], sz[M], sc;

int a[N], m;

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

int main(void) {
    ios::sync_with_stdio(false); cin.tie(0);
    #ifndef ONLINE_JUDGE
    ifstream cin("1.in");
    //ofstream cout("1.out");
    #endif // ONLINE_JUDGE
    int n; cin >> n;
    while(n--) {
        int o, v; cin >> o >> v;
        if (o == 1)
            insert(v);
        else if(o == 2)
            erase(v);
        else
            cout << find_min(v) << ' ' << find_max(v) << endl;
    }
}