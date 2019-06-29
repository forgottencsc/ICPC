#include <bits/stdc++.h>
#define N 100001
using namespace std;

typedef long long ll;

char str[N]; int s[N], k, n;

int main(void) {
    cin >> k >> str; n = strlen(str);
    for (int i = 1; i <= n; ++i)
        s[i] = str[i - 1] - '0';
    ll res = 0;
    for (int l = 1; l <= n; ++l) {
        for (int r = l; r <= n; ++r) {
            ll x = 0;
            for (int i = l; i <= r; ++i)
                x = (10 * x + s[i]) % k;
            if (!x) res++;
        }
    }
    cout << res << endl;
	return 0;
}