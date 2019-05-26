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

ll qpm(ll a, ll b, ll p) {
	ll r = 1;
	for (ll i = 1; i <= b; i <<= 1, a = a * a % p)
		if (i & b) r = r * a % p;
	return r % p;
}

ll mod(ll x, ll p) { x %= p; return x + (x < 0 ? p : 0); }

//	Extended Euclidean Algorithm
ll exgcd(ll a, ll b, ll& u, ll& v) { ll d;
	if (b) d = exgcd(b, a % b, v, u), v -= (a / b) * u;
	else d = a, u = 1, v = 0; return d;
}

//	Try to reduce ax = b(mod p) to x = b'(mod p')
bool lce(ll& a, ll& b, ll& p) {
	ll x, k, d = exgcd(a, p, x, k);
	if (b % d == 0) a = 1, b = mod(x * b / d, p /= d);
	return a == 1;
}

bool crt(ll& b1, ll& m1, ll b2, ll m2) {
	ll a = m1, b = b2 - b1, p = m2;
	if (!lce(a, b, p)) return false;
	else { b1 += b * m1; m1 *= p; return true; }
}

ll inv(ll x, ll p) { ll b; lce(x %= p, b, p); return b; }

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
            if (qpm(g, (p - 1) / d, p) == 1)
                fail = 1;
        if (!fail) return g;
        else g++;
    }
}