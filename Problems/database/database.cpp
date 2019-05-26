#include <bits/stdc++.h>
#define N 1000001
using namespace std;

typedef unsigned long long ul;

ul a[N], n;

ul query(int x) {
    ul sum = 0;
    for (int w = x; w; w -= w & -w)
        sum += a[w];
    return sum;
}

void modify(int x, ul v) {
    for (int w = x; w <= n; w += w & -w)
        a[w] += v;
}

int main(void) {
    ios::sync_with_stdio(0); cin.tie(0);
    #ifndef ONLINE_JUDGE
    ifstream cin("1.in");
    #endif // ONLINE_JUDGE
    int q; cin >> n >> q;
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
            cout << query(r) - query(l - 1) << endl;
        }
    }
    return 0;
}
