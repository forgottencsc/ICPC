#include <bits/stdc++.h>
#define N (1<<19)
#define P 998244353
#define M(x) (((x) + P) % P)
typedef long long ll;

using namespace std;

ll invs[N], f[N], fi[N];
ll inv(ll x) { return x == 1 ? 1 : M(inv(P % x) * (P - P / x)); }
ll binom(ll n, ll k) { return M(f[n] * M(fi[n - k] * fi[k])); }
void ginv() {
    invs[1] = 1; f[0] = fi[0] = 1;
    for (int i = 2; i != N; ++i) invs[i] = M(invs[P % i] * (P - P / i));
    for (int i = 1; i != N; ++i) f[i] = M(f[i - 1] * i);
    for (int i = 1; i != N; ++i) fi[i] = M(fi[i - 1] * invs[i]);
}

ll qp(ll a, ll b) {
    ll r = 1;
    do if (b & 1) r = M(r * a);
    while (a = M(a * a), b >>= 1);
    return r;
}

ll inv(ll x, ll p) { return x == 1 ? 1 : inv(p % x, p) * (p - p / x) % p; }
ll qpm(ll a, ll b, ll q) {
    ll r = 1;
    do if (b & 1) r = r * a % q;
    while (a = a * a % q, b >>= 1);
    return r;
}

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

typedef unsigned long long ull;
typedef long double ld;
ull mul(ull a, ull b, ull p) {
    return ((__int128)a * b) % p;
	ll res = a * b - p * (ull)((ld)a * (ld)b / (ld)p);
	return res + p * (res < 0) - p * (res >= (ll)p);
}

namespace poly {

    istream& operator>>(istream& is, vector<ll>& p) {
        for (ll& w : p) is >> w;
        return is;
    }

    ostream& operator<<(ostream& os, const vector<ll>& p) {
        for (ll w : p) os << w << ' ';
        return os;
    }

    int fr[N], fs;
    ll pa[N], pb[N], pc[N], pd[3][N];

    void init(int s) {
        for (fs = 1; fs < s; fs <<= 1);
        for (int i = 0; i != fs; ++i)
            fr[i] = (fr[i >> 1] >> 1) | (i & 1 ? (fs >> 1) : 0);
    }

    vector<ll> add(const vector<ll>& p1, const vector<ll>& p2) {
        int n1 = p1.size(), n2 = p2.size(), n3 = max(n1, n2);
        vector<ll> pr(n3, 0);
        for (int i = 0; i != n3; ++i) {
            if (i < n1) pr[i] = M(pr[i] + p1[i]);
            if (i < n2) pr[i] = M(pr[i] + p2[i]);
        }
        return pr;
    }

    vector<ll> sub(const vector<ll>& p1, const vector<ll>& p2) {
        int n1 = p1.size(), n2 = p2.size(), n3 = max(n1, n2);
        vector<ll> pr(n3);
        for (int i = 0; i != n3; ++i) {
            if (i < n1) pr[i] = M(pr[i] + p1[i]);
            if (i < n2) pr[i] = M(pr[i] - p2[i]);
        }
        return pr;
    }

    vector<ll> mul(const vector<ll>& p1, ll k) {
        int n1 = p1.size();
        vector<ll> p2(n1);
        for (int i = 0; i != n1; ++i) p2[i] = M(k * p1[i]);
        return p2;
    }

//  MTT
//    void ntt(ll* a, int f, ll q) {
//        static const ll g = 3;
//        for (int i = 0; i != fs; ++i) if (i < fr[i]) swap(a[i], a[fr[i]]);
//        for (int i = 1; i != fs; i <<= 1) {
//            ll e = (q - 1) / (i << 1), w0 = qpm(g, f == 1 ? e : q - 1 - e, q);
//            for (int j = 0; j != fs; j += (i << 1)) {
//                ll w = 1;
//                for (int k = 0; k != i; k++, w = w * w0 % q) {
//                    ll u = a[j + k], v = w * a[i + j + k] % q;
//                    a[j + k] = (u + v) % q; a[i + j + k] = (u - v + q) % q;
//                }
//            }
//        }
//        if (f == -1) {
//            ll d = inv(fs, q);
//            for (ll i = 0; i != fs; ++i)
//                a[i] = a[i] * d % q;
//        }
//    }
//    vector<ll> mul(const vector<ll>& p1, const vector<ll>& p2, int n = 0) {
//        ll q[4] = { 469762049, 998244353, 1004535809 }; q[3] = q[0] * q[1];
//        int n1 = p1.size(), n2 = p2.size(), n3 = n1 + n2 - 1;
//        init(n3 + 1); vector<ll> pr(n3);
//        for (int j = 0; j != 3; ++j) {
//            copy_n(p1.begin(), n1, pa); fill(pa + n1, pa + fs, 0);
//            copy_n(p2.begin(), n2, pb); fill(pb + n2, pb + fs, 0);
//            ntt(pa, 1, q[j]); ntt(pb, 1, q[j]);
//            for (int i = 0; i != fs; ++i) pd[j][i] = pa[i] * pb[i] % q[j];
//            ntt(pd[j], -1, q[j]);
//        }
//        ll i1 = inv(q[1] % q[0], q[0]), i2 = inv(q[0] % q[1], q[1]),
//                 i3 = inv(q[3] % q[2], q[2]);
//        for (int i = 0; i != n3; ++i) {
//            ll A = (::mul(pd[0][i] * q[1] % q[3], i1, q[3])
//                  + ::mul(pd[1][i] * q[0] % q[3], i2, q[3])) % q[3];
//            ll k = (((pd[2][i] - A) % q[2] + q[2]) % q[2]) * i3 % q[2];
//            pr[i] = M(M(M(k) * M(q[3])) + M(A));
//        }
//        if (n) pr.resize(n, 0);
//        return pr;
//    }

    void ntt(ll* p, int f) {
        static const ll g = 3;
        for (int i = 0; i != fs; ++i) if (i < fr[i]) swap(p[i], p[fr[i]]);
        for (int i = 1; i != fs; i <<= 1) {
            ll e = (P - 1) / (i << 1), w0 = qp(g, f == 1 ? e : P - 1 - e);
            for (int j = 0; j != fs; j += (i << 1)) {
                ll w = 1;
                for (int k = 0; k != i; k++, w = M(w * w0)) {
                    ll u = p[j + k], v = M(w * p[i + j + k]);
                    p[j + k] = M(u + v); p[i + j + k] = M(u - v);
                }
            }
        }
        if (f == -1)
            for (ll i = 0; i != fs; ++i)
                p[i] = M(p[i] * invs[fs]);
    }

    vector<ll> mul(const vector<ll>& p1, const vector<ll>& p2, int n = 0) {
        int n1 = p1.size(), n2 = p2.size(), n3 = n1 + n2 - 1;
        init(n3 + 1); vector<ll> pr(n3);
        copy_n(p1.begin(), n1, pa); fill(pa + n1, pa + fs, 0);
        copy_n(p2.begin(), n2, pb); fill(pb + n2, pb + fs, 0);
        ntt(pa, 1); ntt(pb, 1);
        for (int i = 0; i != fs; ++i) pc[i] = M(pa[i] * pb[i]);
        ntt(pc, -1); copy(pc, pc + n3, pr.begin());
        if (n) pr.resize(n, 0);
        return pr;
    }


    vector<ll> inv(const vector<ll>& p1) {
        int n1 = p1.size(), n2 = (n1 + 1) >> 1;
        if (n1 == 1) return { ::inv(p1[0]) };
        else {
            vector<ll> p2 = inv(vector<ll>(p1.begin(), p1.begin() + n2));
            return sub(mul(p2, 2), mul(p1, mul(p2, p2, n1), n1));
        }
    }


    pair<vector<ll>, vector<ll>> div(const vector<ll>& p1, const vector<ll>& p2) {
        int n1 = p1.size(), n2 = p2.size(), n3 = n1 - n2 + 1;
        vector<ll> p1r = p1, p2r = p2;
        reverse(p1r.begin(), p1r.end());
        reverse(p2r.begin(), p2r.end());
        p1r.resize(n3, 0); p2r.resize(n3, 0);
        vector<ll> p3 = mul(p1r, inv(p2r), n3);
        reverse(p3.begin(), p3.end());
        vector<ll> p4 = sub(p1, mul(p2, p3));
        p4.resize(n2 - 1, 0);
        return { p3, p4 };
    }

    vector<ll> deriv(const vector<ll>& p1) {
        int n1 = p1.size();
        vector<ll> p2(n1 - 1);
        for (int i = 1; i != n1; ++i) p2[i - 1] = M(i * p1[i]);
        return p2;
    }

    vector<ll> integ(const vector<ll>& p1) {
        int n1 = p1.size();
        vector<ll> p2(n1 + 1, 0);
        for (int i = 0; i != n1; ++i) p2[i + 1] = M(p1[i]*invs[i + 1]);
        return p2;
    }

    vector<ll> log(const vector<ll>& p1) {
        return integ(mul(deriv(p1), inv(p1), p1.size() - 1));
    }

    vector<ll> exp(const vector<ll>& p1) {
        if (p1.size() == 1) return { 1 };
        else {
            vector<ll> p2 = exp({p1.begin(),p1.begin()+(p1.size()+1>>1)});
            p2.resize(p1.size(), 0);
            return mul(p2, add(sub({ 1 }, log(p2)), p1), p1.size());
        }
    }

    vector<ll> sqrt(const vector<ll>& p1) {
        int n1 = p1.size(), n2 = (n1 + 1) >> 1;
        if (n1 == 1) return { ::msqrt(p1[0], P) };
        else {
            vector<ll> p2 = sqrt(vector<ll>(p1.begin(), p1.begin() + n2));
            vector<ll> p3 = mul(p2, 2); p3.resize(n1);
            p3 = inv(p3);
            return mul(add(mul(p2, p2, n1), p1), p3, n1);
        }
    }
    //  k mod P, not P - 1
    vector<ll> pow0(const vector<ll>& p1, int k) {
        return exp(mul(log(p1), k));
    }

    vector<ll> pow(const vector<ll>& p1, int k) {
        int n1 = p1.size(), n2 = n1;
        while (n2 && !p1[n1 - n2]) n2--;
        int n3 = max(n1 - 1ll * (n1 - n2) * k, 0ll);
        if (!n2 || !n3) return vector<ll>(n1, 0);
        vector<ll> p2(p1.begin() + n1 - n2, p1.begin() + n1 - n2 + n3);
        ll c = p2[0]; p2 = mul(pow0(mul(p2, ::inv(c)), k), qp(c, k));
        p2.resize(n1, 0); rotate(p2.begin(), p2.begin() + n3, p2.end());
        return p2;
    }

    //  f[i] = \sum f[i-j]g[j]
    vector<ll> conv(const vector<ll>& g) {
        return inv(sub({ 1 }, g));
    }

    vector<ll> egf(const vector<ll>& g) {
        vector<ll> r(g.size());
        for (int i = 0; i != g.size(); ++i)
            r[i] = M(g[i] * fi[i]);
        return r;
    }

    vector<ll> iegf(const vector<ll>& g) {
        vector<ll> r(g.size());
        for (int i = 0; i != g.size(); ++i)
            r[i] = M(g[i] * f[i]);
        return r;
    }

}

using namespace poly;

int main(void) {
    ios::sync_with_stdio(0); cin.tie(0);
    #ifndef ONLINE_JUDGE
    ifstream cin("1.in");
    #endif // ONLINE_JUDGE
    ginv();
    int n, m; cin >> n >> m;
    vector<ll> a(n); cin >> a;
    cout << pow(a, m) << endl;

    return 0;
}
