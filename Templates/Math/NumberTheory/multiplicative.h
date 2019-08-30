#include <bits/stdc++.h>
using namespace std;

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

ll eulerphi(ll n) {
	ll res = 1;
	for (ll p : ps) {
		if (p * p > n) break;
		if (n % p) continue;
		n /= p; res *= (p - 1);
		while (n % p == 0) { n /= p; res *= p; }
	}
	if (n != 1) res *= n - 1;
	return res;
}

ll moebiusmu(ll n) {
	ll res = 1;
	for (ll p : ps) {
		if (p * p > n) break;
		if (n % p) continue;
		n /= p; res = -res;
		if (n % p == 0) return 0;
	}
	if (n != 1) res = -res;
	return res;
}

//	Eulerian Sieve

//	Power of minimum prime factor pk[i];
//	(1): 1;	(2): 1; (3): pk[i] + 1;

//	px[i]=p^pk[i];
//	(1): i;	(2): p;	(3): px[i] * p;

//	MoebiusMu mu[i];
//	(1): -1; (2): -mu[i]; (3): 0;

//	EulerPhi ph[i];
//	(1): i - 1;	(2): ph[i] * (p - 1);
//	(3): ph[i] * p;

//	DivisorCount dc[i];
//	(1): 2;		(2): dc[i] * 2;
//	(3): dc[i] / (pk[i] + 1) * (pk[i] + 2);
//	(3): dc[i] + dc[i] / (pk[i] + 1);

//	DivisorSum ds[i];
//	(1): i + 1;	(2): ds[i] * (p + 1);
//	(3): ds[i / px[i]] * (qpow(p, pk[i] + 2) - 1) / (p - 1)
//	(3): ds[i / px[i]] * ((px[i] * p * p) - 1) / (p - 1)

//	Sum of coprime numbers; sigma[i] = i * ph[i] / 2;
#define W 1000001
bool ip[W]; vector<ll> ps;
void eulersieve() {
	ps.reserve(N * 1.2 / log(N));
	memset(ip, 1, sizeof(ip)); ip[1] = 0;
	//  f[1] = 1
	for (int i = 2; i != N; ++i) {
		if (ip[i]) {
			ps.push_back(i);
			//  f[i] = (1)
		}
		for (ll p : ps) {
			if (i * p >= N) break;
			ip[i * p] = 0;
			if (i % p) {
				// f[i * p] = (2)
			}
			else {
				//	f[i * p] = (3)
				break;
			}
		}
	}
}

//  Sublinear sieves
namespace mfps_du {

ll m[N], n, s;
function<ll(ll)> sf, sg, sh;

void init(ll n_) {
    n = n_; s = sqrt(n) + 2;
    fill(m, m + s, 0);
}

ll get(ll x) {
    if (x < N) return sf(x);
    ll& sum = m[n / x];
    if (sum) return sum;
    sum = sh(x);
    for (ll l = 2, r; l <= x; l = r + 1) {
        r = x / (x / l);
        sum = M(sum - M((sg(r) - sg(l - 1)) * get(x / l)));
    }
    return sum;
}

}

namespace mfps_min25 {

bool ip[N]; ll ps[N], pc;
void sieve() {
    fill(ip + 2, ip + N, 1);
    for (int i = 2; i != N; ++i) {
        if (ip[i]) ps[++pc] = i;
        for (int j = 1; j <= pc; ++j) {
            if (i * ps[j] >= N) break;
            ip[i * ps[j]] = 0;
            if (i % ps[j] == 0) break;
        }
    }
}

ll s1(ll x) { x = M(x); return M(M(x * (x + 1)) * inv2); }
ll s2(ll x) { x = M(x); return M(M(x * (x + 1)) * M((2 * x + 1) * inv6)); }

ll n, sq, r, w[N], c, id1[N], id2[N];
ll sp[3][N], g[3][N];

inline ll id(ll x) { return x <= sq ? id1[x] : id2[n / x]; }

void init(ll n_) {
    if (!pc) sieve();
    n = n_; sq = sqrt(n_); c = 0;
    for (r = 1; ps[r] <= sq; ++r);
    for (int i = 1; i <= r; ++i) {
        sp[0][i] = M(sp[0][i - 1] + 1);
        sp[1][i] = M(sp[1][i - 1] + ps[i]);
        sp[2][i] = M(sp[1][i - 1] + M(ps[i] * ps[i]));
    }
    for (ll l = 1, r; l <= n; l = r + 1) {
        ll v = w[++c] = n / l; r = n / v;
        (v <= sq ? id1[v] : id2[n/v]) = c;
        g[0][c] = M(v - 1);
        g[1][c] = M(s1(v) - 1);
        g[1][c] = M(s2(v) - 1);
    }
    for (int i = 1; i <= r; ++i) {
        ll p = ps[i];
        for (int j = 1; j <= c && p * p <= w[j]; ++j) {
            ll k = id(w[j] / p);
            g[0][j] = M(g[0][j] - M(g[0][k] - sp[0][i - 1]));
            g[1][j] = M(g[1][j] - M((p) * M(g[1][k] - sp[1][i - 1])));
            g[2][j] = M(g[2][j] - M(M(p * p) * M(g[2][k] - sp[2][i - 1])));
        }
    }
}

ll get_f(ll p, ll e, ll q) {
    return 114514;
}

ll get_s(ll n, ll i = 0) {
    if (ps[i] >= n) return 0;
    ll k = id(n), s[3];
    for (int j = 0; j != 3; ++j) s[j] = M(g[j][k] - sp[j][i]);
    ll sum = M(s[2] - s[1] + s[0]);    //  f(p) = p^2-p+1
    for (int j = i + 1; j <= r && ps[j] * ps[j] <= n; ++j)
        for (ll q = ps[j], e = 1; q <= n; q *= ps[j], ++e)
            sum = M(sum + M(get_f(ps[j], e, q) * (get_s(n / q, j) + (e != 1))));
    return sum + (i == 0);
}

}