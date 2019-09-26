#include <bits/stdc++.h>
#define N 100001
#define M(x) (((x) + P) % P)
#define P 1000000007
typedef long long ll;


ll invs[N], f[N], fi[N];
ll bi[N][N], be[N], ep[N][N];
ll inv(ll x) { return x == 1 ? 1 : M(inv(P % x) * (P - P / x)); }
void ginv() {
    invs[1] = 1; f[0] = fi[0] = 1;
    for (int i = 2; i != N; ++i) invs[i] = M(invs[P % i] * (P - P / i));
    for (int i = 1; i != N; ++i) f[i] = M(f[i - 1] * i);
    for (int i = 1; i != N; ++i) fi[i] = M(fi[i - 1] * invs[i]);
    // Binomial coefficient
    for (int i = 0; i != N; ++i) {
        bi[i][0] = bi[i][i] = 1;
        for (int j = 1; j < i; ++j)
            bi[i][j] = M(bi[i - 1][j - 1] + bi[i - 1][j]);
    }
    be[0] = 1;  //  Bernoulli numbers
    for (int i = 1; i != N; ++i)
        for (int j = 0; j != i; ++j)
            be[i] = M(be[i] - M(bi[i][j] * M(be[j] * invs[i - j + 1])));
    //  Equal Power Sum Coef
    ep[0][0] = ep[0][1] = 1;
    for (int i = 1; i != N; ++i)
        for (int j = 0; j <= i; ++j)
            ep[i][i+1-j]=M(M(j&1?-invs[i+1]:invs[i+1])*M(bi[i + 1][j]*be[j]));
}

//  \sum_{i=0}^{n}{i^k}
ll epsum(ll n, ll k) {
    ll w = 1, r = 0;
    for (int i = 0; i <= k + 1; ++i, w = M(w * n))
        r = M(r + M(w * ep[k][i]));
    return r;
}

#define W 11
typedef array<array<ll, W>, W> arr;
arr g(ll a, ll b, ll c, ll n) {
    arr u; u[0].fill(0); u.fill(u[0]);
    if (a >= c || b >= c) {
        ll qa = a / c, ra = a % c, qb = b / c, rb = b % c;
        ll pqa[W], pqb[W]; pqa[0] = pqb[0] = 1;
        for (int i = 1; i != W; ++i)
            pqa[i] = M(pqa[i - 1] * qa),
            pqb[i] = M(pqb[i - 1] * qb);
        arr v = g(ra, rb, c, n);
        for (int k1 = 0; k1 != W; ++k1)
            for (int k2 = 0; k2 + k1 != W; ++k2)
                for (int i = 0; i <= k2; ++i)
                    for (int j = 0; j <= i; ++j)
                        u[k1][k2] = M(u[k1][k2] + v[k1+j][k2-i] *
                        M(M(bi[k2][i] * bi[i][j]) * M(pqa[j] * pqb[i - j])));
    }
    else if (a == 0) {
        for (int k1 = 0; k1 != W; ++k1)
            for (int k2 = 0; k2 + k1 != W; ++k2)
                u[k1][k2] = M(qp(b / c, k2) * epsum(n, k1));
    }
    else if (a * n + b >= c) {
        arr v = g(c, c - b - 1, a, (a * n + b) / c - 1);
        for (int k1 = 0; k1 != W; ++k1) {
            for (int k2 = 0; k2 + k1 != W; ++k2) {
                u[k1][k2] = M(epsum(n, k1) * qp((a * n + b) / c, k2));
                for (int i = 0; i <= k2 - 1; ++i)
                    for (int j = 0; j <= k1 + 1; ++j)
                        u[k1][k2] = M(u[k1][k2] - M(v[i][j] *
                        M(bi[k2][i] * ep[k1][j])));
            }
        }
    }
    return u;
}


//  fraction representation with farey sequence
pair<ll, ll> get_frac(dbl x, ll p1, ll q1, ll p2, ll q2) {
    ll p3 = (p1 + p2), q3 = (q1 + q2), d = gcd(p3, q3);
    p3 /= d; q3 /= d;
    if (fabs(q3 * x - p3) < eps)return { p3, q3 };
    else if (x * q3 < p3) return get_frac(x, p1, q1, p3, q3);
    else return get_frac(x, p3, q3, p2, q2);
}

//  Lagrangian Interpolation, P(x[0])==y[0], P(x[1])==y[1], ...
ll lintp(const vector<ll>& y, const vector<ll>& x, ll m) {
    int n = y.size(); ll res = 0;
    for (int i = 0; i != n; ++i) {
        ll t = y[i];
        for (int j = 0; j != n; ++j)
            if (j != i)
                t = M(t * M((P+m-x[j]) * inv(P+x[i]-x[j])));
        res = M(res + t);
    }
    return res;
}

//  Lagrangian Interpolation, P(0)==y[0], P(1)==y[1], ...
ll lp[N], ls[N];
ll lintp(const vector<ll>& y, ll x) {
    int n = y.size(); ll res = 0; lp[0] = x; ls[n - 1] = x - (n - 1);
    for (int i = 1; i != n; ++i) lp[i] = M(lp[i - 1] * (x - i));
    for (int i = n - 2; i >= 0; --i) ls[i] = M(ls[i + 1] * (x - i));
    for (int i = 0; i != n; ++i) {
        ll t = (n - i + 1) & 1 ? P - y[i] : y[i];
        if (i)          t = M(t * M(lp[i - 1] * fi[i]));
        if (i != n - 1) t = M(t * M(ls[i + 1] * fi[n - 1 - i]));
        res = M(res + t);
    }
    return res;
}

//  Calculate \sum_{k=0}^m{(n*k+x)/m}=\sum_{k=0}^n{(m*k+x)/n}
int fsum(int n, int m, int x) {
    int d = gcd(n,m);
    return d * (x / d) + ((m - 1) * n + (d - m)) / 2;
}

//  Cantor expansion when S is huge, 1 based
ll cexp(int* a, int n) {
    static int b[N] = {0};
    fill(b+1,b+n+1,0);
	ll res = 0;
	for (int i = n; i >= 1; --i) {
        ll cnt = 0;
        for (int j=a[i]; j; j-=j&-j) cnt += b[j];
        res = M(res + cnt * f[n-i]);
        for (int j=a[i]; j<=n; j+=j&-j) b[j]++;
	}
	return res + 1;
}

//  Cantor expansion when S is small, 0 based
ll cexp(array<int, S> a) {
	int res = 0;
	for (int i = 0; i != S - 1; ++i)
		for (int j = i + 1; j != S; ++j)
			if (a[i] > a[j]) res += f[S - 1 - i];
	return res;
}

array<int, S> icexp(ll x) {
	array<int, S> res;
	vector<int> v(S); iota(v.begin(), v.end(), 0);
	for (int i = 0; i != S; ++i) {
		int t = f[S - i - 1];
		res[i] = v[x / t];
		v.erase(v.begin() + x / t);
		x %= t;
	}
	return res;
}

//  Fraction
struct frac {
    ll n, d;
    frac(ll nn = 0, ll dd = 1) { ll w = gcd(nn, dd); n = nn / w; d = dd / w;}
    frac operator-() const { return frac(-n, d); }
    frac operator+(frac f) { return frac(n * f.d + d * f.n, d * f.d); }
    frac operator-(frac f) { return frac(n * f.d - d * f.n, d * f.d); }
    frac operator*(frac f) { return frac(n * f.n, d * f.d); }
    frac operator/(frac f) { return frac(n * f.d, d * f.n); }
};

//	Solve cubic/quadratic equation
#define sq(x) ((x) * (x))
#define cb(x) (sq(x) * (x))
typedef complex<dbl> cplx;
void cubic(dbl a0, dbl a1, dbl a2, dbl a3,
	cplx& x1, cplx& x2, cplx& x3) {
	a0 /= a3; a1 /= a3; a2 /= a3;
	dbl p = sq(a2) / 9 - a1 / 3, q = a2 * a1 / 6 - cb(a2) / 27 - a0/ 2;
	cplx del = sqrt((cplx)(sq(q) - cb(p))), w(-0.5, sqrt(3) / 2),
		f1 = pow(q + del, 1. / 3), f2 = pow(q - del, 1. / 3);
	x1 = f1 + f2 - a2 / 3;
	x2 = w * f1 + sq(w) * f2 - a2 / 3;
	x3 = sq(w) * f1 + w * f2 - a2 / 3;
}

void quadr(dbl a0, dbl a1, dbl a2, dbl a3, dbl a4,
	cplx& x1, cplx& x2, cplx& x3, cplx& x4) {
	a0 /= a4; a1 /= a4; a2 /= a4; a3 /= a4; a3 /= 4;
	dbl b = a2 - 6 * sq(a3), c = 3 * (a1 - 2 * a2 * a3 + cb(2 * a3)),
		d = 12 * (a0 - a1 * a3 + a2 * sq(a3) - 3 * sq(sq(a3))),
		p = sq(b) + d, q = 2 * cb(b) + 3 * sq(c) - 6 * b * d, k = 2 * sqrt(3);
	cplx del = sqrt((cplx(sq(q) - 4 * cb(p)))),
		f = pow((q + del) / 2., 1. / 3) + pow((q - del) / 2., 1. / 3),
		f1 = sqrt(f - 2 * b), f2 = k * c / f1, f3 = -4 * b - f;
	x1 = (f1 - sqrt(f3 - f2)) / k - a3; x2 = (f1 + sqrt(f3 - f2)) / k - a3;
	x3 = (-f1 - sqrt(f3 + f2)) / k - a3; x4 = (-f1 + sqrt(f3 + f2)) / k - a3;
}

//  Solve polynomial equations
const dbl eps = 1e-8;
int dc(dbl d) { return d < -eps ? -1 : d > eps ? 1 : 0; }

dbl val(const vector<dbl>& p, dbl x) {
    dbl w = 1, r = 0;
    for(int i = 0; i != p.size(); ++i, w *= x)
        r += p[i] * w;
    return r;
}

dbl fr(vector<dbl> p, dbl lb, dbl ub, bool flg) {
    dbl x = (lb + ub) / 2;
    while(dc(ub - lb)) {
        dbl res = val(p, x);
        if (!dc(res)) break;
        else if (flg ^ (dc(res) == 1)) lb = x;
        else ub = x; x = (ub + lb) / 2;
    }
    return x;
}

vector<dbl> peq(vector<dbl> p) {
    if (p.size() < 2) return {};
    else if (p.size() == 2) return { -p[0] / p[1] };
    else {
        vector<dbl> p_, res, sx, sy; dbl b = 0;
        for (int i = 0; i != p.size(); ++i) b = max(b, abs(p[i] / p[0]) + 1);
        for (int i = 1; i != p.size(); ++i) p_.push_back(p[i] * i);
        sx = peq(p_); sx.insert(sx.begin(), -b); sx.push_back(b);
        for (dbl x : sx) sy.push_back(val(p, x));
        for (int i = 0; i != sx.size() - 1; ++i)
            if (dc(sy[i] * sy[i + 1]) == -1)
                res.push_back(fr(p, sx[i], sx[i + 1], dc(sy[i]) == -1));
        return res;
    }
}

//	Simpson's Rule
template<class F> dbl sps0(const F& f,dbl l, dbl r) {
	return (f(l) + 4 * f((l + r) / 2) + f(r)) * (r - l) / 6;
}

template<class F> dbl sps1(const F& f, dbl l, dbl r, dbl eps, dbl s) {
	dbl m = (l + r) / 2, lv = sps0(f, l, m), rv = sps0(f, m, r), d = lv + rv - s;
	if (fabs(d) < 15 * eps) return lv + rv + 15 * d;
	else return sps1(f, l, m, eps / 2, lv) + sps1(f, m, r, eps / 2, rv);
}

template<class F> dbl spsint(const F& f, dbl l, dbl r, dbl eps) {
	return sps1(f, l, r, eps, sps0(f, l, r));
}

//  golden section search
typedef double dbl;
const dbl eps = 1e-8, phi = (sqrt(5) - 1) / 2;
pair<dbl, dbl> gss0(const function<dbl(dbl)>& f,
         dbl l1, dbl l2, dbl r2, dbl r1,
         dbl l1v, dbl l2v, dbl r2v, dbl r1v) {
    if (l2 + eps >= r2) {
        if (l2v < r2v) return { l2, l2v };
        else return { r2, r2v };
    }
    if (l2v > r2v)  //  < for minimum, > for maximum
        return gss0(f, l1, r2 - phi * (r2 - l1), l2, r2,
                    l1v, f(r2 - phi * (r2 - l1)), l2v, r2v);
    else
        return gss0(f, l2, r2, l2 + phi * (r1 - l2), r1,
                    l2v, r2v, f(l2 + phi * (r1 - l2)), r1v);
}

pair<dbl, dbl> gss(const function<dbl(dbl)>& f,
                   dbl l1, dbl r1) {
    dbl t = phi * (r1 - l1), l2 = r1 - t, r2 = l1 + t;
    return gss0(f, l1, l2, r2, r1, f(l1), f(l2), f(r2), f(r1));
}

vector<ll> BM(const vector<ll>& x) {
    vector<ll> ls, cur;
    int pn = 0, lf, ld;
    for(int i = 0;i != x.size(); ++i) {
        ll t = M(-x[i]);
        for(int j = 0; j != cur.size(); ++j)
            t = M(t + x[i - j - 1] * cur[j]);
        if(!t) continue;
        if(cur.empty()) {
            cur.resize(i + 1);
            lf = i; ld = t;
            continue;
        }
        ll k = M(M(-t) * inv(ld));
        vector<ll> c(i - lf - 1); c.push_back(M(-k));
        for(int j = 0; j != ls.size(); ++j)
            c.push_back(M(ls[j] * k));
        if(c.size() < cur.size())
            c.resize(cur.size());
        for(int j = 0;j != cur.size(); ++j)
            c[j]=M(c[j]+cur[j]);
        if(i-lf+ls.size()>=cur.size())
            ls = cur,lf = i, ld = t;
        cur = move(c);
    }
    return cur;
}

//	FFT/NTT/FWT
ui fr[N], fs;

void init(ui s) {
	for (fs = 1; fs <= s; fs <<= 1);
	for (int i = 0; i != fs; ++i)
		fr[i] = (fr[i >> 1] >> 1) | (i & 1 ? (fs >> 1) : 0);
}


void fft(cplx* p, int f) {
	for (int i = 0; i != fs; ++i) if (i < fr[i]) swap(p[i], p[fr[i]]);
	for (int i = 1; i != fs; i <<= 1) {
		cplx w0{ cos(pi / i), (f ? 1. : -1.) * sin(pi / i) };
		for (int j = 0; j != fs; j += (i << 1)) {
			cplx w{ 1, 0 };
			for (int k = 0; k != i; k++, w = w * w0) {
				cplx u = p[j + k], v = w * p[i + j + k];
				p[j + k] = u + v; p[i + j + k] = u - v;
			}
		}
	}
}

void fft_res(cplx* p) {
	for (ui i = 0; i != fs; ++i)
		p[i] = p[i] * (1. / fs);
}


void ntt(ll* p, int f) {
	static const ll g;
	// ((3u<<30)|1)->5; ((119u<<23)|1)->3; ((479u<<21)|1)->3;
	for (int i = 0; i != fs; ++i) if (i < fr[i]) swap(p[i], p[fr[i]]);
	for (int i = 1; i != fs; i <<= 1) {
		ll e = (MOD - 1) / (i << 1), w0 = qp(g, f ? e : MOD - 1 - e);
		for (int j = 0; j != fs; j += (i << 1)) {
			ll w = 1;
			for (int k = 0; k != i; k++, w = M(w * w0)) {
				ll u = p[j + k], v = M(w * p[i + j + k]);
				p[j + k] = M(u + v); p[i + j + k] = M(u - v);
			}
		}
	}
}

void ntt_res(ll* p) {
	for (ll i = 0, is = inv(fs); i != fs; ++i)
		p[i] = M(p[i] * is);
}

typedef double dbl;
const dbl eps = 1e-8;
int sgn(dbl x) { return x < -eps ? -1 : x > eps; }

dbl dis(const vector<dbl>& p, const vector<dbl>& v,
        const vector<dbl>& q) {
    int n = p.size();
    dbl d1 = 0, d = 0;
    for (int i = 0; i != n; ++i) {
        d += v[i] * v[i];
        d1 += v[i] * (p[i] - q[i]);
    }
    dbl t = -d1 / d;
    dbl res = 0;
    for (int i = 0; i != n; ++i)
        res = hypot(res, v[i] * t + p[i] - q[i]);
    return res;
}

dbl dis(const vector<dbl>& p1, const vector<dbl>& v1,
        const vector<dbl>& p2, const vector<dbl>& v2) {
    int n = p1.size();
    dbl a1 = 0, b1 = 0, c1 = 0,
        a2 = 0, b2 = 0, c2 = 0;
    for (int i = 0; i != n; ++i) {
        a1 += v1[i] * v1[i];
        b1 -= v1[i] * v2[i];
        c1 += v1[i] * (p1[i] - p2[i]);
        a2 -= v1[i] * v2[i];
        b2 += v2[i] * v2[i];
        c2 -= v2[i] * (p1[i] - p2[i]);
    }
    dbl d1 = c1 * b2 - c2 * b1,
        d2 = a1 * c2 - a2 * c1,
        d = a1 * b2 - a2 * b1;
    if (!sgn(d)) return dis(p1, v1, p2);
    dbl t1 = - d1 / d, t2 = - d2 / d;
    dbl res = 0;
    for (int i = 0; i != n; ++i)
        res = hypot(res, p1[i] - p2[i] + t1 * v1[i] - t2 * v2[i]);
    return res;
}
