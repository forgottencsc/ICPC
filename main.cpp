#include <bits/stdc++.h>
#define N 1<<18
using namespace std;

typedef long long ll;
typedef vector<int> vi;

const int P = 998244353, g = 3;

int add(int a, int b) { int r = a + b; return r < P ? r : r - P; }
int sub(int a, int b) { int r = a - b; return r < 0 ? r + P : r; }
int mul(ll a, ll b) { return a * b % P; }
int inv(int a) { return a == 1 ? 1 : mul(inv(P % a), P - P / a); }
int qpm(int a, ll b) {
    int r = 1;
    do if (b & 1) r = mul(r, a);
    while (a = mul(a, a), b >>= 1);
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

int fac[N], ifac[N], invs[N];
void ginv() {
    invs[1] = 1; for (int i = 2; i != N; ++i) invs[i] = mul(invs[P % i], P - P / i);
    fac[0] = 1; for (int i = 1; i != N; ++i) fac[i] = mul(fac[i - 1], i);
    ifac[0] = 1; for (int i = 1; i != N; ++i) ifac[i] = mul(ifac[i - 1], invs[i]);
}


const int W = 18, S = 1 << W;

int w[S + 1], rev[S << 1], *r[W + 1];

void init() {
    for (int s = 0; s <= W&&(r[s]=rev+(1<<s),1); ++s)
        for (int i = 0; i != (1 << s); ++i)
            r[s][i] = (r[s][i >> 1] >> 1) | ((i & 1) << (s - 1));
    w[0] = 1; w[1] = qpm(g, (P - 1) / S);
    for (int i = 2; i <= S; ++i) w[i] = mul(w[i - 1], w[1]);
}

int m, s, im;
int init(int n) {
    for (s = 0, m = 1; m < n; m <<= 1, ++s);
    im = inv(m); return m;
}

int px[N], py[N];
void ntt(int* p, int t) {
    for (int i = 0; i != m; ++i) if (i < r[s][i]) swap(p[i], p[r[s][i]]);
    for (int i = 1, z = 0; i != m; i <<= 1, z++)
        for (int j = 0; j != m; j += (i << 1))
            for (int k = 0, u, v; k != i; k++)
                u = p[j+k], v = mul(w[(t?(i<<1)-k:k)<<W-z-1], p[i+j+k]),
                p[j + k] = add(u, v), p[i + j + k] = sub(u, v);
    if (t) for (int i = 0; i != m; ++i) p[i] = mul(p[i], im);
}


istream& operator>>(istream& is, vi& p) {
    for (int& w : p) is >> w;
    return is;
}

ostream& operator<<(ostream& os, const vi& p) {
    for (int w : p) os << w << ' ';
    return os;
}

vi mul(const vi& p1, const vi& p2, int n = 0) {
    int n1 = p1.size(), n2 = p2.size(), n3 = n1 + n2 - 1;
    init(n3);
    copy_n(p1.begin(), n1, px); fill(px + n1, px + m, 0);
    copy_n(p2.begin(), n2, py); fill(py + n2, py + m, 0);
    ntt(px, 0); ntt(py, 0);
    for (int i = 0; i != m; ++i) px[i] = mul(px[i], py[i]);
    ntt(px, 1); vi p3(n3); copy_n(px, n3, p3.begin());
    if (n && n3 > n) p3.resize(n); return p3;
}

vi add(const vi& p1, const vi& p2) {
    int n3 = max(p1.size(), p2.size());
    vi pr = p1; pr.resize(n3, 0);
    for (int i = 0; i != p2.size(); ++i) pr[i] = add(pr[i], p2[i]);
    return pr;
}

vi sub(const vi& p1, const vi& p2) {
    int n3 = max(p1.size(), p2.size());
    vi pr = p1; pr.resize(n3, 0);
    for (int i = 0; i != p2.size(); ++i) pr[i] = sub(pr[i], p2[i]);
    return pr;
}

vector<int> mul(const vector<int>& p1, ll k) {
    int n1 = p1.size(); vector<int> p2(n1);
    for (int i = 0; i != n1; ++i) p2[i] = mul(k, p1[i]);
    return p2;
}

vi egf(const vi& g) {
    vi r(g.size());
    for (int i = 0; i != g.size(); ++i)
        r[i] = mul(g[i], ifac[i]);
    return r;
}

vi iegf(const vi& g) {
    vi r(g.size());
    for (int i = 0; i != g.size(); ++i)
        r[i] = mul(g[i], fac[i]);
    return r;
}

vi shift(const vi& a, ll d) {
    int n = a.size();
    vi b = a, c(n);
    reverse(b.begin(), b.end());
    for (int i = 0; i != n; ++i) {
        b[i] = mul(b[i], fac[n - i - 1]);
        if (!i) c[i] = 1;
        else c[i] = mul(c[i - 1], mul(d, invs[i]));
    }
    vi r = mul(b, c, n);
    reverse(r.begin(), r.end());
    return egf(r);
}

vi inv(const vi& p1) {
    int n1 = p1.size(), n2 = (n1 + 1) >> 1;
    if (n1 == 1) return { inv(p1[0]) };
    else {
        vi p2 = inv(vi(p1.begin(), p1.begin() + n2));
        init(n1 << 1);
        copy_n(p1.begin(), n1, px); fill(px + n1, px + m, 0);
        copy_n(p2.begin(), n2, py); fill(py + n2, py + m, 0);
        ntt(px, 0); ntt(py, 0);
        for (int i = 0; i != m; ++i)
            px[i] = mul(sub(2, mul(px[i], py[i])), py[i]);
        ntt(px, 1); vi p3(n1); copy_n(px, n1, p3.begin());
        return p3;
    }
}

pair<vi, vi> div(const vi& p1, const vi& p2) {
    int n1 = p1.size(), n2 = p2.size(), n3 = n1 - n2 + 1;
    if (n3 <= 0) return { { 0 }, p1 };
    vi p1r = p1, p2r = p2;
    reverse(p1r.begin(), p1r.end());
    reverse(p2r.begin(), p2r.end());
    p1r.resize(n3, 0); p2r.resize(n3, 0);
    vi p3 = mul(p1r, inv(p2r), n3);
    reverse(p3.begin(), p3.end());
    vi p4 = sub(p1, mul(p2, p3));
    p4.resize(n2 - 1, 0);
    return { p3, p4 };
}

vi deriv(const vi& p1) {
    int n1 = p1.size();
    vi p2(n1 - 1);
    for (int i = 1; i != n1; ++i) p2[i - 1] = mul(i, p1[i]);
    return p2;
}

vi integ(const vi& p1) {
    int n1 = p1.size();
    vi p2(n1 + 1, 0);
    for (int i = 0; i != n1; ++i) p2[i + 1] = mul(p1[i], invs[i + 1]);
    return p2;
}

vi log(const vi& p1) {
    return integ(mul(deriv(p1), inv(p1), p1.size() - 1));
}

vi exp(const vi& p1) {
    if (p1.size() == 1) return { 1 };
    else {
        vi p2 = exp({p1.begin(),p1.begin()+(p1.size()+1>>1)});
        p2.resize(p1.size(), 0);
        return mul(p2, add(sub({ 1 }, log(p2)), p1), p1.size());
    }
}

vi sqrt(const vi& p1) {
    int n1 = p1.size(), n2 = (n1 + 1) >> 1;
    if (n1 == 1) return { ::msqrt(p1[0]) };
    else {
        vi p2 = sqrt(vi(p1.begin(), p1.begin() + n2));
        vi p3 = mul(p2, 2); p3.resize(n1);
        p3 = inv(p3);
        return mul(add(mul(p2, p2, n1), p1), p3, n1);
    }
}
//  k mod P, not P - 1
vi pow(const vi& p1, int k) {
    int n1 = p1.size(), n2 = n1;
    while (n2 && !p1[n1 - n2]) n2--;
    int n3 = max(n1 - 1ll * (n1 - n2) * k, 0ll);
    if (!n2 || !n3) return vi(n1, 0);
    vi p2(p1.begin() + n1 - n2, p1.begin() + n1 - n2 + n3);
    ll c = p2[0]; p2 = mul(exp(mul(log(mul(p2, ::inv(c))), k)), qpm(c, k));
    p2.resize(n1, 0); rotate(p2.begin(), p2.begin() + n3, p2.end());
    return p2;
}

//  f[i] = \sum f[i-j]g[j]
vi conv(const vi& g) {
    return inv(sub({ 1 }, g));
}

int eval(const vi& p, int x) {
    int r = 0;
    for (int i = (int)p.size() - 1; i >= 0; --i)
        r = add(p[i], mul(r, x));
    return r;
}

vi est[N];

void eval0(const vi& x, int p, int lb, int rb) {
    if (lb + 1 == rb) est[p] = { sub(0, x[lb]), 1 };
    else {
        int mid = (lb + rb) >> 1;
        eval0(x, p << 1, lb, mid);
        eval0(x, p << 1 | 1, mid, rb);
        est[p] = mul(est[p << 1], est[p << 1 | 1]);
    }
}

void eval1(const vi& r, const vi& x,
           int p, int lb, int rb) {
    vi w = div(r, est[p]).second;
    if (lb + 100 >= rb)
        for (int i = lb; i != rb; ++i)
            est[0][i] = eval(w, x[i]);
    else {
        int mid = (lb + rb) >> 1;
        eval1(w, x, p << 1, lb, mid);
        eval1(w, x, p << 1 | 1, mid, rb);
    }
}

vi eval(const vi& p, const vi& x) {
    eval0(x, 1, 0, x.size());
    est[0].resize(x.size());
    eval1(p, x, 1, 0, x.size());
    return est[0];
}

int main(void) {
    ios::sync_with_stdio(0); cin.tie(0);
    #ifndef ONLINE_JUDGE
    ifstream cin("1.in");
    #endif // ONLINE_JUDGE

    init();
    ginv();


    return 0;
}

