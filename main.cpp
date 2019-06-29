#include <bits/stdc++.h>
#define N 1000001
using namespace std;

typedef long long ll;

ll mod(ll x, ll p) { x %= p; return x + (x < 0 ? p : 0); }

//	Extended Euclidean Algorithm
ll exgcd(ll a, ll b, ll& u, ll& v) { ll d;
	if (b) d = exgcd(b, a % b, v, u), v -= (a / b) * u;
	else d = a, u = 1, v = 0; return d;
}

//  a^b(mod p) = a^(b%phi(p)+phi(p))
ll qpm(ll a, ll b, ll p) {
	ll r = 1;
	do if (b & 1) r = r * a % p;
    while (a = a * a % p, b >>= 1);
	return r % p;
}

// Tonelli-Shanks algorithm. O(log^2p)
ll msqrt(ll n, ll p) {
    ll q = p - 1, s = 0, z = 2;
    while (~q & 1) q >>= 1, s++;
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


//	Try to reduce ax = b(mod p) to x = b'(mod p')
//  Solve linear congurence eps
bool lce(ll& a, ll& b, ll& p) {
	ll x, k, d = exgcd(a, p, x, k);
	if (b % d == 0) a = 1, b = mod(x * b / d, p /= d);
	return a == 1;
}

//  Solve quadratic congurence equation
bool qce(ll a, ll b, ll c, ll p, ll& x1, ll& x2) {
    if (qpm(mod(b*b-4*a*c, p), (p-1)/2, p) != 1) return false;
    ll r1 = msqrt(mod(b*b-4*a*c, p), p), r2 = p - r1;
    ll a1 = 2 * a % p, a2 = 2 * a % p;
    x1 = (r1 + p - b) % p; x2 = (r2 + p - b) % p;
    lce(a1, x1, p); lce(a2, x2, p);
    return true;
}

int main(){
    ios::sync_with_stdio(0); cin.tie(0);
    #ifndef ONLINE_JUDGE
    ifstream cin("1.in");
    #endif // ONLINE_JUDGE

    ll p = 1000000007; cout << boolalpha;
    for (int a = -10; a <= 10; ++a) {
        for (int b = -10; b <= 10; ++b) {
            for (int c = -10; c <= 10; ++c) {
                int u = mod(a, p), v = mod(b, p), w = mod(c, p);
                ll x1, x2;
                if (qce(u, v, w, p, x1, x2)) {
                    cout << u << ' ' << v << ' ' << w << ' ' << x1 << ' ' << x2 <<endl;
                    ll y1 = mod(u * mod(x1 * x1, p) + v * x1 + w, p);
                    ll y2 = mod(u * mod(x2 * x2, p) + v * x2 + w, p);
                    cout << (!y1) << ' ' << (!y2) << endl;
                }
            }
        }
    }

    return 0;
}