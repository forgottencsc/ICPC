#include <bits/stdc++.h>
#define N (1<<18)
#define P 998244353
#define M(x) (((x) + P) % P)
typedef long long ll;

ll invs[N];
ll inv(ll x) { return x == 1 ? 1 : M(inv(P % x) * (P - P / x)); }
void ginv() {
    invs[1] = 1;
    for (int i = 2; i != N; ++i)
        invs[i] = M(invs[P % i] * (P - P / i));
}

namespace poly {

    ostream& operator<<(ostream& os, const vector<ll>& p) {
        for (ll w : p) os << w << ' ';
        return os;
    }

    int fr[N], fs;
    ll pa[N], pb[N], pc[N];

    void init(int s) {
        for (fs = 1; fs < s; fs <<= 1);
        for (int i = 0; i != fs; ++i)
            fr[i] = (fr[i >> 1] >> 1) | (i & 1 ? (fs >> 1) : 0);
    }

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

    vector<ll> add(const vector<ll>& p1, const vector<ll>& p2) {
        int n1 = p1.size(), n2 = p2.size(), n3 = max(n1, n2);
        vector<ll> pr(n3);
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

    vector<ll> mul(const vector<ll>& p1, int k) {
        int n1 = p1.size();
        vector<ll> p2(n1);
        for (int i = 0; i != n1; ++i)
            p2[i] = M(k * p1[i]);
        return p2;
    }

    vector<ll> mul(const vector<ll>& p1, const vector<ll>& p2, int n = 0) {
        int n1 = p1.size(), n2 = p2.size(), n3 = n1 + n2 - 1;
        init(n3 + 1); vector<ll> pr(n3);
        copy_n(p1.begin(), n1, pa); fill(pa + n1, pa + fs, 0);
        copy_n(p2.begin(), n2, pb); fill(pb + n2, pb + fs, 0);
        ntt(pa, 1); ntt(pb, 1);
        for (int i = 0; i != fs; ++i)
            pc[i] = M(pa[i] * pb[i]);
        ntt(pc, -1); copy(pc, pc + n3, pr.begin());
        if (n) pr.resize(n, 0);
        return pr;
    }

    vector<ll> inv(const vector<ll>& p1) {
        int n1 = p1.size(), n2 = (n1 + 1) >> 1;
        if (n1 == 1)
            return vector<ll>(1, ::inv(p1[0]));
        else {
            vector<ll> p1_(p1.begin(), p1.begin() + n2);
            vector<ll> p2 = inv(p1_);
            return sub(add(p2, p2), mul(p1, mul(p2, p2, n1), n1));
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
        vector<ll> p2(n1 + 1);
        p2[0] = 0;
        for (int i = 0; i != n1; ++i) p2[i + 1] = M(p1[i] * invs[i + 1]);
        return p2;
    }

    vector<ll> log(const vector<ll>& p1) {
        int n1 = p1.size();
        return integ(mul(deriv(p1), inv(p1), n1 - 1));
    }

    vector<ll> exp(const vector<ll>& p1) {
        int n1 = p1.size(), n2 = (n1 + 1) >> 1;
        if (n1 == 1) return vector<ll>(1, 1);
        else {
            vector<ll> p2 = exp(vector<ll>(p1.begin(), p1.begin() + n2));
            p2.resize(n1, 0);
            vector<ll> one(n1, 0); one[0] = 1;
            return mul(p2, add(sub(one, log(p2)), p1), n1);
        }
    }

    vector<ll> pow(const vector<ll>& p1, int k) {
        return exp(mul(log(p1), k));
    }

}
