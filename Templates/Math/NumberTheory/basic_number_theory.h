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
void sieve() {
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

//	Try to reduce ax = b(mod p) to x = b'(mod p')
//  Solve linear congurence equation
bool lce(ll& a, ll& b, ll& p) {
	ll x, k, d = exgcd(a, p, x, k);
	if (b % d == 0) {
        a = 1; p /= d;
        b = ((x * b / d) % p + p) % p;
	}
	return a == 1;
}

ll inv(ll x, ll m) { ll b = 1; lce(x %= m, b, m); return b; }

//  Try to reduce x=b1(mod m1) && x=b2(mod m2) to x=b(mod m)
bool crt(ll& b1, ll& m1, ll b2, ll m2) {
	ll a = m1, b = b2 - b1, p = m2;
	if (!lce(a, b, p)) return false;
	else { b1 += b * m1; m1 *= p; return true; }
}

//  a^b(mod p) = a^(b%phi(p)+(b>=phi(p)?phi(p):0))
ll qpm(ll a, ll b, ll p) {
	ll r = 1;
	do if (b & 1) r = r * a % p;
    while (a = a * a % p, b >>= 1);
	return r % p;
}

//	Basic Lucas Theorem
//  assert(isprime(p))
ll mbinom(ll n, ll k, ll p) {
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

//  Extend Lucas Theorem
ll mfac(ll n, ll p, ll q) {
    if (!n) return 1;
    static map<ll, vector<ll>> m;
    vector<ll>& v = m[p]; if (v.empty()) v.push_back(1);
    for (int i = v.size(); i <= q; ++i)
        v.push_back(v.back() * (i % p ? i : 1) % q);
    return qpm(v[q], n / q, q) * v[n % q] % q * mfac(n / p, p, q) % q;
}

ll mbinom(ll n, ll k, ll p, ll q) {
    ll c = 0;
    for (ll i = n; i; i /= p) c += i / p;
    for (ll i = k; i; i /= p) c -= i / p;
    for (ll i = n - k; i; i /= p) c -= i / p;
    return mfac(n, p, q) * inv(mfac(k, p, q), q) % q
    * inv(mfac(n - k, p, q), q) % q * qpm(p, c, q) % q;
}

ll mbinom(ll n, ll k, ll m) {
    ll b = 0, w = 1; vector<pf> ps = pfd(m);
    for (pf pp : ps) {
        ll p = pp.p, q = 1;
        while(pp.c--) q *= pp.p;
        crt(b, w, mbinom(n, k, p, q), q);
    }
    return b;
}


//	Solve a^x=b(mod p), O(sqrt(p))
//  Usage: bsgs.init(a, p); bsgs.solve(b);
struct bsgs_t {
    const int S = 1 << 19;
    const int msk = S - 1;
    ll a, p, m, w;
    int c, h[S], g[S], k[S], v[S];

    int fin(int x) {
        for (int i = h[x & msk]; ~i; i = g[i])
            if (k[i] == x) return v[i];
        return -1;
    }

    void ins(int x, int e) {
        g[c] = h[x & msk]; k[c] = x;
        v[c] = e; h[x & msk] = c++;
    }

    void init(ll a_, ll p_) {
        c = 0; a = a_; p = p_; w = 1;
        m = ceil(sqrt(p));
        memset(h, 0xff, sizeof(h));
        for (int i = 0; i != m; ++i) {
            if (fin(w) == -1) ins(w, i);
            w = w * a % p;
        }
        w = qpm(w, p - 2, p);
    }

    int solve(ll b) {
        for (int i = 0; i != m; ++i) {
            int r = fin(b);
            if (r != -1) return i * m + r;
            b = b * w % p;
        }
        return -1;
    }
} bsgs;

// Tonelli-Shanks algorithm. O(log^2(p)) 1s~5e3
ll msqrt(ll n, ll p) {
    if (!n) return 0;
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

//  Solve quadratic congurence equation
//  assert(a && isprime(p) && p > 2);
bool qce(ll a, ll b, ll c, ll p, ll& x1, ll& x2) {
    ll d = ((b * b - 4 * a * c) % p + p) % p;
    if (qpm(d, (p - 1) / 2, p) == p - 1) return false;
    d = msqrt(d, p); a = inv(2 * a % p, p);
    x1 = (p - b + d) * a % p; x2 = (2 * p - b - d) * a % p;
    return true;
}

//  Find a primitive root of modulo p. O(p^(1/4))
//  Use Pollard's rho algorithm when p is huge.
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
        if (!fail) return g; else g++;
    }
}

//  Pohlig-Hellman algorithm
//  Solve g^x=a, O(sqrt(p)c)
ll mlog0(ll g, ll a, ll p) {
    vector<pf> pfs = pfd(p - 1);
    ll x = 0, b = 1;
    for (pf f : pfs) {
        ll q = qpm(f.p, f.c, p), w = 1, t = a, r = 0;
        ll h = qpm(g, (p - 1) / f.p, p);
        bsgs.init(h, p, f.p);
        for (int i = 0; i != f.c; ++i) {
            ll z = bsgs.solve(qpm(t, (p - 1) / (w * f.p), p));
            t = mul(t, qpm(qpm(g, w * z, p), p - 2, p), p);
            r += w * z; w *= f.p;
        }
        crt(x, b, r, q);
    }
    return x;
}

//  Solve a^x=b(mod p)
ll mlog(ll a, ll b, ll p) {
    ll g = primitive_root(p);
    ll u = mlog0(g, a, p), v = mlog0(g, b, p), m = p - 1;
    if (!lce(u, v, m))
        return -1;
    else
        return v;
}