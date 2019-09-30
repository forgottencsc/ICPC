#include <bits/stdc++.h>
#define N (1<<20)
#define P 998244353
typedef long long ll;

using namespace std;

inline int add(int a, int b) { int r = a + b; return r < P ? r : r - P; }
inline int sub(int a, int b) { int r = a - b; return r < 0 ? r + P : r; }
inline int mul(ll a, ll b) { ll r = a * b; return r % P; }
inline int inv(int a) { return a == 1 ? a : mul(inv(P % a), P - P / a); }
inline int qpm(int a, int b) {
    int r = 1;
    do if (b & 1) r = mul(r, a);
    while (a = mul(a, a), b >>= 1);
    return r;
}

int invs[N], f[N], fi[N];
int binom(int n, int k) { return mul(f[n], mul(fi[n - k], fi[k])); }
void ginv() {
    invs[1] = 1; f[0] = fi[0] = 1;
    for (int i = 2; i != N; ++i) invs[i] = mul(invs[P % i], (P - P / i));
    for (int i = 1; i != N; ++i) f[i] = mul(f[i - 1], i);
    for (int i = 1; i != N; ++i) fi[i] = mul(fi[i - 1], invs[i]);
}

ll inv(ll x, ll p) { return x == 1 ? 1 : inv(p % x, p) * (p - p / x) % p; }
ll qpm(ll a, ll b, ll q) {
    ll r = 1;
    do if (b & 1) r = r * a % q;
    while (a = a * a % q, b >>= 1);
    return r;
}

int msqrt(int n) {
    if (!n) return 0;
    int q = P - 1, s = 0, z = 2;
    //while (~q & 1) q >>= 1, s++;
    q >>= (s = __builtin_ctzll(q));
    if (s == 1) return qpm(n, (P + 1) / 4);
    while(qpm(z, (P - 1) / 2) == 1) ++z;
    int c = qpm(z, q), t = qpm(n, q),
       r = qpm(n, (q + 1) / 2), m = s;
    while(t % P != 1) {
        ll i = 1; while(qpm(t, 1ll << i) != 1) ++i;
        ll b = qpm(c, 1ll << (m - i - 1));
        r = mul(r, b); c = mul(b, b);
        t = mul(t, c); m = i;
    }
    return min(r, P - r); //    r^2=(p-r)^2=n
}

typedef unsigned long long ull;
typedef long double ld;
ull mul(ull a, ull b, ull p) {
    return ((__int128)a * b) % p;
	ll res = a * b - p * (ull)((ld)a * (ld)b / (ld)p);
	return res + p * (res < 0) - p * (res >= (ll)p);
}

namespace poly {

    using ::add;
    using ::sub;
    using ::mul;
    using ::inv;
    using ::qpm;

    istream& operator>>(istream& is, vector<int>& p) {
        for (int& w : p) is >> w;
        return is;
    }

    ostream& operator<<(ostream& os, const vector<int>& p) {
        for (int w : p) os << w << ' ';
        return os;
    }

    int pa[N], pb[N], pc[N], pd[3][N];

    const int W = 20, S = 1 << W, g = 3;
    int fr[W][S], fw[2][S];

    void init() {
        for (int s = 1; s != W; ++s)
            for (int i = 0; i != (1 << s); ++i)
                fr[s][i] = (fr[s][i>>1]>>1)|((i&1)<<(s-1));
        fw[0][0] = fw[1][0] = 1;
        fw[0][1] = qpm(g, (P - 1) / (1 << W));
        fw[1][1] = inv(fw[0][1]);
        for (int i = 2; i != (1 << W); ++i) {
            fw[0][i] = mul(fw[0][i - 1], fw[0][1]);
            fw[1][i] = mul(fw[1][i - 1], fw[1][1]);
        }
    }

    int fs, ft;
    void init(int n) {
        for (fs = 1, ft = 0; fs < n; fs <<= 1, ++ft);
    }

    void ntt(int* p, int t) {
        for (int i=0;i!=fs;++i) if (i<fr[ft][i]) swap(p[i],p[fr[ft][i]]);
        for (int i = 1, s = 0; i != fs; i <<= 1, s++)
            for (int j = 0; j != fs; j += (i << 1))
                for (int k = 0; k != i; ++k) {
                    int u=p[j+k],v=mul(fw[t][k<<(W-s-1)],p[i+j+k]);
                    p[j+k] = add(u, v), p[i+j+k] = sub(u, v);
                }
        for (int i=0,x=inv(fs);t&&i!=fs;++i) p[i]=mul(p[i],x);
    }

    vector<int> add(const vector<int>& p1, const vector<int>& p2) {
        int n3 = max(p1.size(), p2.size());
        vector<int> pr = p1; pr.resize(n3, 0);
        for (int i = 0; i != p2.size(); ++i) pr[i] = add(pr[i], p2[i]);
        return pr;
    }

    vector<int> sub(const vector<int>& p1, const vector<int>& p2) {
        int n3 = max(p1.size(), p2.size());
        vector<int> pr = p1; pr.resize(n3, 0);
        for (int i = 0; i != p2.size(); ++i) pr[i] = sub(pr[i], p2[i]);
        return pr;
    }

    vector<int> mul(const vector<int>& p1, ll k) {
        int n1 = p1.size(); vector<int> p2(n1);
        for (int i = 0; i != n1; ++i) p2[i] = mul(k, p1[i]);
        return p2;
    }

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
//    vector<int> mul(const vector<int>& p1, const vector<int>& p2, int n = 0) {
//        ll q[4] = { 469762049, 998244353, 1004535809 }; q[3] = q[0] * q[1];
//        int n1 = p1.size(), n2 = p2.size(), n3 = n1 + n2 - 1;
//        init(n3 + 1); vector<int> pr(n3);
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

    vector<int> mul0(const vector<int>& p1, const vector<int>& p2) {
        int n1 = p1.size(), n2 = p2.size(), n3 = n1 + n2 - 1;
        vector<int> p3(n3);
        for (int i = 0; i != n1; ++i)
            for (int j = 0; j != n2; ++j)
                p3[i + j] = add(p3[i + j], mul(p1[i], p2[j]));
        return p3;
    }

    vector<int> mul(const vector<int>& p1, const vector<int>& p2, int n = 0) {
        int n1 = p1.size(), n2 = p2.size(), n3 = n1 + n2 - 1;
        vector<int> pr(n3);
        if (n3 > 150) {
            init(n3 + 1);
            copy_n(p1.begin(), n1, pa); fill(pa + n1, pa + fs, 0);
            copy_n(p2.begin(), n2, pb); fill(pb + n2, pb + fs, 0);
            ntt(pa, 0); ntt(pb, 0);
            for (int i = 0; i != fs; ++i) pc[i] = mul(pa[i], pb[i]);
            ntt(pc, 1); copy(pc, pc + n3, pr.begin());
        }
        else pr = mul0(p1, p2);
        if (n && pr.size() > n) pr.resize(n, 0);
        return pr;
    }

    vector<int> egf(const vector<int>& g) {
        vector<int> r(g.size());
        for (int i = 0; i != g.size(); ++i)
            r[i] = mul(g[i], fi[i]);
        return r;
    }

    vector<int> iegf(const vector<int>& g) {
        vector<int> r(g.size());
        for (int i = 0; i != g.size(); ++i)
            r[i] = mul(g[i], f[i]);
        return r;
    }

    vector<int> scale(const vector<int>& a, ll d) {
        vector<int> b = a;
        for (int i = 0; i != b.size(); ++i)
            b[i] = mul(b[i], qpm(d, i));
        return b;
    }

    vector<int> shift(const vector<int>& a, ll d) {
        int n = a.size();
        vector<int> b = a, c(n);
        reverse(b.begin(), b.end());
        for (int i = 0; i != n; ++i) {
            b[i] = mul(b[i], f[n - i - 1]);
            if (!i) c[i] = 1;
            else c[i] = mul(c[i - 1], mul(d, invs[i]));
        }
        vector<int> r = mul(b, c, n);
        reverse(r.begin(), r.end());
        return egf(r);
    }

    vector<int> inv(const vector<int>& p1) {
        int n1 = p1.size(), n2 = (n1 + 1) >> 1;
        if (n1 == 1) return { ::inv(p1[0]) };
        else {
            vector<int> p2 = inv(vector<int>(p1.begin(), p1.begin() + n2));
            init(n1 << 1);
            copy_n(p1.begin(), n1, pa); fill(pa + n1, pa + fs, 0);
            copy_n(p2.begin(), n2, pb); fill(pb + n2, pb + fs, 0);
            ntt(pa, 0); ntt(pb, 0);
            for (int i = 0; i != fs; ++i)
                pc[i] = mul(sub(2, mul(pa[i], pb[i])), pb[i]);
            ntt(pc, 1);
            vector<int> r(n1);
            copy(pc, pc + n1, r.begin());
            return r;
        }
    }

    pair<vector<int>, vector<int>> div(const vector<int>& p1, const vector<int>& p2) {
        int n1 = p1.size(), n2 = p2.size(), n3 = n1 - n2 + 1;
        if (n3 <= 0) return { { 0 }, p1 };
        vector<int> p1r = p1, p2r = p2;
        reverse(p1r.begin(), p1r.end());
        reverse(p2r.begin(), p2r.end());
        p1r.resize(n3, 0); p2r.resize(n3, 0);
        vector<int> p3 = mul(p1r, inv(p2r), n3);
        reverse(p3.begin(), p3.end());
        vector<int> p4 = sub(p1, mul(p2, p3));
        p4.resize(n2 - 1, 0);
        return { p3, p4 };
    }

    vector<int> deriv(const vector<int>& p1) {
        int n1 = p1.size();
        vector<int> p2(n1 - 1);
        for (int i = 1; i != n1; ++i) p2[i - 1] = mul(i, p1[i]);
        return p2;
    }

    vector<int> integ(const vector<int>& p1) {
        int n1 = p1.size();
        vector<int> p2(n1 + 1, 0);
        for (int i = 0; i != n1; ++i) p2[i + 1] = mul(p1[i], invs[i + 1]);
        return p2;
    }

    vector<int> log(const vector<int>& p1) {
        return integ(mul(deriv(p1), inv(p1), p1.size() - 1));
    }

    vector<int> exp(const vector<int>& p1) {
        if (p1.size() == 1) return { 1 };
        else {
            vector<int> p2 = exp({p1.begin(),p1.begin()+(p1.size()+1>>1)});
            p2.resize(p1.size(), 0);
            return mul(p2, add(sub({ 1 }, log(p2)), p1), p1.size());
        }
    }

    vector<int> sqrt(const vector<int>& p1) {
        int n1 = p1.size(), n2 = (n1 + 1) >> 1;
        if (n1 == 1) return { ::msqrt(p1[0]) };
        else {
            vector<int> p2 = sqrt(vector<int>(p1.begin(), p1.begin() + n2));
            vector<int> p3 = mul(p2, 2); p3.resize(n1);
            p3 = inv(p3);
            return mul(add(mul(p2, p2, n1), p1), p3, n1);
        }
    }
    //  k mod P, not P - 1
    vector<int> pow(const vector<int>& p1, int k) {
        int n1 = p1.size(), n2 = n1;
        while (n2 && !p1[n1 - n2]) n2--;
        int n3 = max(n1 - 1ll * (n1 - n2) * k, 0ll);
        if (!n2 || !n3) return vector<int>(n1, 0);
        vector<int> p2(p1.begin() + n1 - n2, p1.begin() + n1 - n2 + n3);
        ll c = p2[0]; p2 = mul(exp(mul(log(mul(p2, ::inv(c))), k)), qpm(c, k));
        p2.resize(n1, 0); rotate(p2.begin(), p2.begin() + n3, p2.end());
        return p2;
    }

    //  f[i] = \sum f[i-j]g[j]
    vector<int> conv(const vector<int>& g) {
        return inv(sub({ 1 }, g));
    }

    int eval(const vector<int>& p, int x) {
        int r = 0;
        for (int i = (int)p.size() - 1; i >= 0; --i)
            r = add(p[i], mul(r, x));
        return r;
    }

    vector<int> est[N];

    void eval0(const vector<int>& x, int p, int lb, int rb) {
        if (lb + 1 == rb) est[p] = { sub(0, x[lb]), 1 };
        else {
            int mid = (lb + rb) >> 1;
            eval0(x, p << 1, lb, mid);
            eval0(x, p << 1 | 1, mid, rb);
            est[p] = mul(est[p << 1], est[p << 1 | 1]);
        }
    }

    void eval1(const vector<int>& r, const vector<int>& x,
               int p, int lb, int rb) {
        vector<int> w = div(r, est[p]).second;
        if (lb + 100 >= rb)
            for (int i = lb; i != rb; ++i)
                est[0][i] = eval(w, x[i]);
        else {
            int mid = (lb + rb) >> 1;
            eval1(w, x, p << 1, lb, mid);
            eval1(w, x, p << 1 | 1, mid, rb);
        }
    }

    vector<int> eval(const vector<int>& p, const vector<int>& x) {
        eval0(x, 1, 0, x.size());
        est[0].resize(x.size());
        eval1(p, x, 1, 0, x.size());
        return est[0];
    }
}

using namespace poly;

vector<int> stirling1_row0(int l, int r) {
    if (l == r) return { l, 1 };
    else {
        int n = r - l + 1, n1 = n / 2, n2 = n - n1;
        vector<int> a = stirling1_row0(l, l + n1 - 1);
        vector<int> b = shift(a, n1);
        vector<int> res = mul(a, b);
        if (n1 == n2) return res;
        vector<int> tmp(n + 1);
        copy(res.begin(), res.end(), tmp.begin() + 1);
        return add(mul(res, r), tmp);
    }
}

vector<int> stirling1_row(int n) {
    return stirling1_row0(0, n - 1);
}

vector<int> stirling1_col(int n, int m) {
    vector<int> a(n + 1, 0);
    for (int i = 1; i <= n; ++i) a[i] = invs[i];
    return iegf(mul(pow(a, m), fi[m]));
}

vector<int> stirling2_row(int n) {
    vector<int> a(n + 1, 0), b(n + 1, 0);
    for (int i = 0; i <= n; ++i)
        a[i] = (i & 1 ? sub(0, fi[i]) : add(0, fi[i]));
    for (int i = 0; i <= n; ++i)
        b[i] = mul(qpm(i, n), fi[i]);
    return mul(a, b, n + 1);
}

vector<int> stirling2_col0(int l, int r) {
    if (l == r) return { 1 };
    if (l + 1 == r) return { 1, sub(0, l) };
    else {
        int mid = (l + r) >> 1;
        return mul(stirling2_col0(l, mid)
                 , stirling2_col0(mid, r));
    }
}

vector<int> stirling2_col(int n, int m) {
    if (n < m) return vector<int>(n + 1, 0);
    vector<int> a = stirling2_col0(1, m + 1);
    a.resize(n - m + 1, 0);
    vector<int> b = inv(a); b.resize(n + 1, 0);
    rotate(b.begin(), b.begin() + n + 1 - m, b.end());
    return b;
}

int main(void) {
    freopen("02", "r", stdin);
    #ifndef ONLINE_JUDGE
    #endif // ONLINE_JUDGE
    init(); ginv();
    int T; scanf("%d", &T);
    while(T--) {
        int n, m; scanf("%d%d", &n, &m);
        vector<int> a(n), b1(n), b2(n), b3(n);
        for (int i = 0; i != n; ++i)
            scanf("%d", &a[i]);
        for (int i = 0; i < n; ++i) b1[i] = 1;
        for (int i = 0; i < n; i += 2) b2[i] = 1;
        for (int i = 0; i < n; i += 3) b3[i] = 1;
        int c1 = 0, c2 = 0, c3 = 0;
        for (int i = 1; i <= m; ++i) {
            int o; scanf("%d", &o);
            if (o == 1) c1++;
            if (o == 2) c2++;
            if (o == 3) c3++;
        }
        vector<int> r = mul(mul(a, pow(b1, c1), n), mul(pow(b2, c2), pow(b3, c3), n), n);
        ll ans = 0;
        for (int i = 0; i != n; ++i)
            //printf("%d%c", r[i], " \n"[i == n - 1]);
            ans ^= (1ll * (i + 1) * r[i]);
        printf("%lld\n", ans);
    }
    return 0;
}
