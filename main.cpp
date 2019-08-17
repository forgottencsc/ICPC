#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

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

vector<pair<ll, ll>> pfd(ll n) {
	vector<pair<ll, ll>> res;
	for (ll p : ps) {
		if (p * p > n) break;
		if (n % p) continue;
		res.emplace_back(p, 0);
		do res.back().second++;
		while ((n /= p) % p == 0);
	}
	if (n != 1) res.emplace_back(n, 1);
	return res;
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

//  Try to reduce x=b1(mod m1) && x=b2(mod m2) to x=b(mod m)
bool crt(ll& b1, ll& m1, ll b2, ll m2) {
	ll a = m1, b = b2 - b1, p = m2;
	if (!lce(a, b, p)) return false;
	else { b1 += b * m1; m1 *= p; return true; }
}

ll inv(ll x, ll m) { ll b = 1; lce(x %= m, b, m); return b; }

//  a^b(mod p) = a^(b%phi(p)+(b>=phi(p)?phi(p):0))
ll qpm(ll a, ll b, ll p) {
	ll r = 1;
	do if (b & 1) r = r * a % p;
    while (a = a * a % p, b >>= 1);
	return r % p;
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
    vector<pair<ll, ll>> ps = pfd(m);
    ll b = 0, w = 1;
    for (pair<ll, ll> pp : ps) {
        ll p = pp.first, q = 1;
        while(pp.second--) q *= p;
        crt(b, w, mbinom(n, k, p, q), q);
    }
    return b;
}

int main(void) {
    ios::sync_with_stdio(0); cin.tie(0);
    #ifndef ONLINE_JUDGE
    ifstream cin("1.in");
    #endif // ONLINE_JUDGE
    sieve();
    ll n, k, m; cin >> n >> k >> m;
    cout << mbinom(n, k, m) << endl;

    return 0;
}