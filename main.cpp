#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main(void) {
    ios::sync_with_stdio(0); cin.tie(0);
    #ifndef ONLINE_JUDGE
    ifstream cin("1.in");
    #endif // ONLINE_JUDGE

    long double e = 1.322324;

    for (int i = 0; i != 30; ++i) {
        if (abs(e - floor(e)) < 1e-5) break;
        cout << (int)floor(e) << endl;
        e = 1 / (e - floor(e));
    }

    return 0;
}

