#include <bits/stdc++.h>
#define W 101
using namespace std;
typedef __int128 ll;
typedef long long l;

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

ll mul(ll a, ll b, ll p) { return (__int128)a * (__int128)b % p; }

ll qpm(ll a, ll b, ll p) {
    ll r = 1;
    do if (b & 1) r = mul(r, a, p);
    while (a = mul(a, a, p), b >>= 1);
    return r;
}

struct bsgs_t {
    static const ll S = 1 << 19;
    ll a, p, m, w, s, msk;
    ll k[S], v[S];
    int c, h[S], g[S];

    ll fin(ll x) {
        for (int i = h[x & msk]; ~i; i = g[i])
            if (k[i] == x) return v[i];
        return -1;
    }

    void ins(ll x, ll e) {
        g[c] = h[x & msk]; k[c] = x;
        v[c] = e; h[x & msk] = c++;
    }

    void init(ll a_, ll p_, ll ord = 0) {
        c = 0; a = a_; p = p_;
        m = ceil(sqrt(ord ? (l)ord : (l)p));
        for (s = 1; s < min(1ll<<19, (l)m<<4); s <<= 1);
        memset(h, 0xff, s << 2); msk = s - 1;
        w = 1;
        for (int i = 0; i != m; ++i) {
            if (fin(w) == -1) ins(w, i);
            w = mul(w, a, p);
        }
        w = qpm(w, p - 2, p);
    }

    ll solve(ll b) {
        ll ret = -1;
        for (int i = 0; i != m; ++i) {
            int r = fin(b);
            if (r != -1) { ret = i * m + r; break; }
            b = mul(b, w, p);
        }
        return ret;
    }
} bsgs;

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

ll mod(ll x, ll p) { x %= p; return x + (x < 0 ? p : 0); }

ll exgcd(ll a, ll b, ll& u, ll& v) { ll d;
	if (b) d = exgcd(b, a % b, v, u), v -= (a / b) * u;
	else d = a, u = 1, v = 0; return d;
}

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

//  Calculate log_g(a)
ll mlog(ll a, ll g, ll p) {
    vector<pf> pfs = pfd(p - 1);
    ll x = 0, b = 1;
    for (pf f : pfs) {
        ll q = qpm(f.p, f.c, p), w = f.p, t = a, r = 0;
        ll h = qpm(g, (p - 1) / w, p);
        bsgs.init(h, p, f.p);
        for (int i = 0; i != f.c; ++i) {
            ll y = qpm(t, (p - 1) / w, p);
            ll z = bsgs.solve(y);
            t = mul(t, qpm(qpm(g, w / f.p * z, p), p - 2, p), p);
            r += (w / f.p) * z;
            w *= f.p;
        }
        crt(x, b, r, q);
    }
    return x;
}

//mt19937_64 mt(1234);

int main(void) {
//    ios::sync_with_stdio(0); cin.tie(0);
    #ifndef ONLINE_JUDGE
    freopen("1.in", "r", stdin);
    //ifstream cin("1.in");
    #endif // ONLINE_JUDGE
    gp();

    int T; scanf("%d", &T);
    while(T--) {
        l A, B, P;
        ll a, b, p; scanf("%lld%lld%lld", &P, &A, &B);
        a = A; b = B; p = P;
        ll g = primitive_root(p);
        ll u = mlog(a, g, p), v = mlog(b, g, p), m = p - 1;
        ll ans = 0;
        if (!lce(u, v, m))
            ans = -1;
        else
            ans = v;
        printf("%lld\n", (l)ans);
    }
    cout << cnt << endl;

    return 0;
}