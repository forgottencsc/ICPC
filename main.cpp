#include <bits/stdc++.h>
#define N 100001
using namespace std;

typedef long long ll;

ll qpm(ll a, ll b, ll p) {
	ll r = 1;
	do if (b & 1) r = r * a % p;
    while (a = a * a % p, b >>= 1);
	return r % p;
}

ll msqrt(ll n, ll p) {
    ll q = p - 1, s = 0, z = 2;
    //while (~q & 1) q >>= 1, s++;
    q >>= (s = __builtin_ctzll(q));
    if (s == 1) return qpm(n, (p + 1) / 4, p);
    while(qpm(z, (p - 1) / 2, p) == 1) ++z;
    ll c = qpm(z, q, p), t = qpm(n, q, p),
       r = qpm(n, (q + 1) / 2, p), m = s;
    while(t % p != 1) {
        ll i = 1; while(qpm(t, 1ll << i, p) != 1) ++i;
        ll b = qpm(c, 1ll << (m - i - 1), p);
        r = r * b % p; c = (b * b) % p;
        t = (t * c) % p; m = i;
    }
    return min(r, p - r); //    r^2=(p-r)^2=n
}


int main(void) {
    #ifndef ONLINE_JUDGE
    freopen("1.in", "r", stdin);
    #endif // ONLINE_JUDGE
    ll p = 998244353; cout << boolalpha;
    int cnt = 0;
    for (int x = 1; x != min(p, 10001ll); ++x) {
        ll i = x + 5e8;
        if (qpm(i, (p-1)/2, p) != 1)
            continue;
        cnt++;
        ll r = msqrt(i, p);
        cout << i << ": " << (r * r % p == i) << endl;
    }
    cout << cnt << endl;

    return 0;
}