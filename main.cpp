#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

void fmt(ll* a, int w) {
    for (int i = 0; i != w; ++i)
        for (int j = 0; j != (1 << w); ++j)
            if (j & (1 << i)) a[j] += a[s ^ (1 << i)];
}

void ifmt(ll* a, int w) {
    for (int i = 0; i != w; ++i)
        for (int j = 0; j != (1 << w); ++j)
            if (j & (1 << i)) a[j] -= a[s ^ (1 << i)];
}

int main(void) {
    ios::sync_with_stdio(0); cin.tie(0);
    #ifndef ONLINE_JUDGE
    ifstream cin("1.in");
    #endif // ONLINE_JUDGE

    return 0;
}
