#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef __int128 lll;

ll mul(ll a, ll b, ll p) { return (lll)a * b % p; }

ll qpm(ll a, ll b, ll p) {
    ll r = 1;
    do if (b & 1) r = mul(r, a, p);
    while (a = mul(a, a, p), b >>= 1);
    return r;
}

//	Miller-Rabin primality test(Deterministic)
//	{ 2, 7, 61 } for 2^32
//	{ 2, 3, 7, 61, 24251 } for 1e16 (except 46856248255981)
//	{ 2, 325, 9375, 28178, 450775, 9780504, 1795265022 } for 2^64
bool mr(ll n) {
    if (n % 2 == 0) return n == 2;
    if (n < 128) return (0X816D129A64B4CB6E >> (n / 2)) & 1;
    const int l[7] = { 2, 325, 9375, 28178, 450775, 9780504, 1795265022 };
    ll d0 = n - 1; do d0 >>= 1; while(!(d0 & 1));
    for (ll a : l) {
        if (a % n == 0) return true;
        ll d = d0, t = qpm(a, d, n);
        while(d != n - 1 && t != 1 && t != n - 1)
            d <<= 1, t = mul(t, t, n);
        if (t != n - 1 && !(d & 1)) return false;
    }
    return true;
}


int main(void) {
    ios::sync_with_stdio(0); cin.tie(0);
    #ifndef ONLINE_JUDGE
    ifstream cin("1.in");
    #endif // ONLINE_JUDGE

    ll p;
    while(cin >> p) {
        ll x = p - 1, y = p - 1;
        while (!mr(y)){
            x = mul(x, qpm(y, p - 2, p), p);
            y--;
        }
        cout << x << endl;
    }

    return 0;
}
