#include <bits/stdc++.h>
#define P 1000000007
#define M(x) (((x) + P) % P)

using namespace std;

typedef long long ll;

ll qp(ll a, ll b) {
	ll r = 1;
	for (ll i = 1; i <= b; i <<= 1, a = M(a * a))
		if (i & b) r = M(r * a);
	return r;
}

ll inv(ll x) { return x == 1 ? 1 : M(inv(P % x) * (P - P / x)); }

//	O(n) prime generator
#define W 1000001
bool ip[W]; vector<ll> ps;
void gp() {
	ps.reserve(W * 1.3 / log(W));
	memset(ip, 1, sizeof(ip)); ip[1] = 0;
	for (int i = 2; i != W; ++i) {
		if (ip[i]) ps.push_back(i);
		for (int p : ps) {
			if (i * p >= W) break;
			ip[i * p] = 0;
			if (i % p == 0) break;
		}
	}
}

struct pf { ll p, c; };
vector<pf> pfd(ll n) {
	vector<pf> res;
	for (ll p : ps) {
		if (p * p > n) break;
		if (n % p) continue;
		res.push_back({ p, 0 });
		do res.back().c++;
		while ((n /= p) % p == 0);
	}
	if (n != 1) res.push_back({ n, 1 });
	return res;
}

vector<ll> ifd(ll n) {
	vector<ll> v;
	for (ll d = 1; d * d <= n; ++d) {
		if (n % d) continue; v.push_back(d);
		if (d * d != n) v.push_back(n / d);
	}
	return v;
}

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

// Tonelli-Shanks algorithm. O(log^2(p)) 1s~5e3
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

//	Try to reduce ax = b(mod p) to x = b'(mod p')
//  Solve linear congurence equation
bool lce(ll& a, ll& b, ll& p) {
	ll x, k, d = exgcd(a, p, x, k);
	if (b % d == 0) a = 1, b = mod(x * b / d, p /= d);
	return a == 1;
}

ll inv(ll x, ll p) { ll b; lce(x %= p, b, p); return b; }

//  Try to reduce x=b1(mod m1) && x=b2(mod m2) to x=b(mod m)
bool crt(ll& b1, ll& m1, ll b2, ll m2) {
	ll a = m1, b = b2 - b1, p = m2;
	if (!lce(a, b, p)) return false;
	else { b1 += b * m1; m1 *= p; return true; }
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

//	Basic Lucas Theorem
ll lucas(ll n, ll k, ll p) {
	static ll f[N];
	for (int i = f[0] = 1; i != p; ++i) f[i] = f[i - 1] * i % p;
	ll ans = 1;
	do {
		if (n % p < k % p) return 0;
		ans = ans * (f[n % p] * inv(f[k % p] * f[(n - k) % p], p) % p) % p;
		n /= p; k /= p;
	} while (n);
	return ans;
}

//	Solve x from a^x=b(mod p)
struct puu { ll k, v; };
bool operator<(puu p1, puu p2) { return p1.k < p2.k; }
bool operator<(puu p, ll k) { return p.k < k; }
ll bsgs(ll a, ll b, ll p) {
	ll m = ceil(sqrt(p)), gmi = qpm(a, m * (p - 2), p);
	vector<puu> v(m); v[0] = { 1, 0 };
	for (ll i = 1; i != m; ++i)
		v[i] = { v[i - 1].k * a % p, i };
	sort(v.begin(), v.end());
	for (int i = 0; i != m; ++i) {
		auto it = lower_bound(v.begin(), v.end(), b);
		if (it != v.end() && it->k == b)
			return i * m + it->v;
		else b = b * gmi % p;
	}
	return -1;
}

//  Find a primitive root of p. O(p^(1/4))
ll primitive_root(ll p) {
    vector<ll> ds; ll n = p - 1;
    for (ll d = 2; d * d <= n; ++d) {
        if (n % d) continue;
        ds.push_back(d);
        while (n % d == 0) n /= d;
    }
    if (n != 1) ds.push_back(n);
    int g = 1;
    while(1) {
        bool fail = 0;
        for (int d : ds)
            if (qpm(g, (p-1)/d, p) == 1)
                fail = 1;
        if (!fail) return g; else g++;
    }
}
