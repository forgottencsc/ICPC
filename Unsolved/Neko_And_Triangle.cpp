#include <bits/stdc++.h>
#define N 2000001
using namespace std;

typedef long long ll;
typedef ll dbl;
const dbl pi = acos(-1), eps = 1e-6, inf = 1e20;
dbl sgn(dbl x) { return x < -eps ? -1 : x > eps; }

struct vec { dbl x, y; };
vec operator+(vec v1, vec v2) { return { v1.x + v2.x, v1.y + v2.y }; }
vec operator-(vec v1, vec v2) { return { v1.x - v2.x, v1.y - v2.y }; }
dbl operator*(vec v1, vec v2) { return v1.x * v2.x + v1.y * v2.y; }
dbl operator^(vec v1, vec v2) { return v1.x * v2.y - v1.y * v2.x; }
vec operator*(vec v, dbl k) { return { v.x * k, v.y * k }; }
vec operator/(vec v, dbl k) { return { v.x / k, v.y / k }; }

bool operator<(vec v1, vec v2) { return v1.x == v2.x ? v1.y < v2.y : v1.x < v2.x; }
bool operator==(vec v1, vec v2) { return v1.x == v2.x && v1.y == v2.y; }
bool operator>(vec v1, vec v2) { return v2 < v1; }

dbl dot(vec v0, vec v1, vec v2) { return (v1 - v0) * (v2 - v0); }
dbl crx(vec v0, vec v1, vec v2) { return (v1 - v0) ^ (v2 - v0); }
dbl len(vec v) { return hypot(v.x, v.y); }
dbl len2(vec v) { return v * v; }
dbl arg(vec v) { dbl r = atan2(v.y, v.x); return r < 0? 2 * pi + r : r; }

vec unif(vec v) { return v / len(v); }
vec univ(dbl f) { return { cos(f), sin(f) }; }
vec rot(vec p, dbl f) { return { cos(f) * p.x - sin(f) * p.y, sin(f) * p.x + cos(f) * p.y }; }
vec rot(vec o, vec p, dbl f) { return o + rot(p - o, f); }
vec rot90(vec p) { return { -p.y, p.x }; }

struct line { vec p, v; };
vec proj(line l, vec p) { return p + l.v * ((l.p - p) * l.v / len2(l.v)); }
vec refl(vec o, vec p) { return o + o - p; }
vec refl(line l, vec p) { return refl(proj(l, p), p); }
vec litsc(line l1, line l2) { return l2.p + l2.v * ((l1.v ^ (l2.p - l1.p)) / (l2.v ^ l1.v)); }
dbl lpdis(line l, vec p) { return fabs(crx(p, l.p, l.p + l.v)) / len(l.v); }


int convex_hull(vec* p, int n, vec* c) {
    sort(p + 1, p + n + 1); n = unique(p + 1, p + n + 1) - p - 1;
    int m = 0;
    c[1] = p[++m];
    for (int i = 1; i <= n; ++i) {
        while (m > 1 && sgn(crx(c[m - 1], c[m], p[i])) != 1) m--;
        c[++m] = p[i];
    }
    int t = m;
    for (int i = n - 1; i; --i) {
        while (m > t && sgn(crx(c[m - 1], c[m], p[i])) != 1) m--;
        c[++m] = p[i];
    }
    if (m > 1) m--; c[m + 1] = c[1]; return m;
}

int minkowski_sum(vec* cv1, int n1, vec* cv2, int n2, vec* cv) {
    if (n1 == 1 || n2 == 1) {
        if (n1 == 1) swap(n1, n2), swap(cv1, cv2);
        for (int i = 1; i <= n1; ++i)
            cv[i] = cv1[i] + cv2[1];
        return n1;
    }
    static vec dv1[N], dv2[N], dv;
    cv1[n1 + 1] = cv1[1]; cv2[n2 + 1] = cv2[1];
    for (int i = 1; i <= n1; ++i) dv1[i] = cv1[i + 1] - cv1[i];
    for (int i = 1; i <= n2; ++i) dv2[i] = cv2[i + 1] - cv2[i];
    int m = 0; cv[++m] = cv1[1] + cv2[1];
    int p1 = 1, p2 = 1;
    while (p1 <= n1 || p2 <= n2) {
        if (p1 <= n1 && p2 <= n2)
            dv = (sgn((dv1[p1])^(dv2[p2]))!=-1?dv1[p1++]:dv2[p2++]);
        else if (p1 <= n1)
            dv = dv1[p1++];
        else
            dv = dv2[p2++];
        while (m > 1 && !sgn((cv[m] - cv[m - 1]) ^ dv)) {
            dv = dv + cv[m] - cv[m - 1];
            m--;
        }
        cv[m + 1] = cv[m] + dv;
        m++;
    }
    if (m > 1) m--; return m;
}

typedef pair<dbl, int> pdi;
namespace cvq {
    vec c[N];
    int w, n;

    void init(vec* cv, int m) {
        copy_n(cv + 1, m, c); n = m;
        rotate(c, min_element(c, c + n), c + n);
        c[n] = c[0]; c[n + 1] = c[1];
        w = 0; while (c[w] < c[w + 1]) ++w;
    }

    //  0：在凸包外，1：在凸包上或凸包内
    int contain(vec p) {
        if (p.x < c[0].x || c[w].x < p.x) return false;
        if (crx(c[0], c[w], p) > 0) {
            int e = lower_bound(c + w, c + n + 1, vec{ p.x, inf }, greater<vec>()) - c;
            if (!sgn(p.x - c[e].x)) return p.y <= c[e].y;
            else return crx(c[e - 1], c[e], p) >= 0;
        }
        else {
            int e = lower_bound(c, c + w + 1, vec{ p.x, -inf }) - c;
            if (!sgn(p.x - c[e].x)) return p.y >= c[e].y;
            else return crx(c[e - 1], c[e], p) >= 0;
        }
    }

    pdi crxmax(int l, int r, vec p) {
        int r0 = r;
        while (l <= r) {
            int m = (l + r) >> 1;
            if ((p ^ (c[m + 1] - c[m])) >= 0) l = m + 1;
            else r = m - 1;
        }
        return pdi(p^c[l],l);
    }

    pair<dbl, int> crxmax(vec p) {
        pdi res = sgn(p.x) <= 0 ? crxmax(0, w - 1, p) : crxmax(w, n - 1, p);
        return max({ res, pdi(p ^ c[0], 0), pdi(p ^ c[w], w) });
    }
    pair<dbl, int> crxmin(vec p) { return crxmax(p * -1); }

    bool ltan(vec p, int i) { return crx(p,c[i],i?c[i-1]:c[n-1])<=0&&crx(p,c[i],c[i+1])<=0; }
    bool rtan(vec p, int i) { return crx(p,c[i],i?c[i-1]:c[n-1])>=0&&crx(p,c[i],c[i+1])>=0; }

    int ltan(int l, int r, vec p) {
        if (ltan(p, r)) return r; r--;
        while (l <= r) {
            int m = (l + r) >> 1;
            if (crx(p,c[m],c[m+1])<0) r = m - 1;
            else l = m + 1;
        }
        return l;
    }

    int rtan(int l, int r, vec p) {
        if (rtan(p, r)) return r; l++;
        while (l <= r) {
            int m = (l + r) >> 1;
            if (crx(p,c[m],m?c[m - 1]:c[n - 1])>0) l = m + 1;
            else r = m - 1;
        }
        return r;
    }

    bool tangent(vec p, int& lp, int& rp) {
        if (contain(p)) return false;
        if (p.x < c[0].x) { lp = ltan(w, n, p); rp = rtan(0, w, p); }
        else if (p.x > c[w].x) { lp = ltan(0, w, p); rp = rtan(w, n, p); }
        else if (crx(c[0], c[w], p) > 0) {
            int e = lower_bound(c + w, c + n + 1, p, greater<vec>()) - c;
            lp = ltan(w, e, p); rp = rtan(e, n, p);
        }
        else {
            int e = lower_bound(c + 0, c + w + 1, p) - c;
            lp = ltan(0, e, p); rp = rtan(e, w, p);
        }
        lp %= n; rp %= n;
        return true;
    }
};

vec pv[N], mv[N], sv[N], qv[N]; int s;
vec pv1[N], pv2[N], cv1[N], cv2[N];

void dc(int l, int r) {
    if (l > r) return;
    int m = (l + r) >> 1;
    int n1 = 0, n2 = 0;
    for (int i = m; i <= r; ++i) pv1[++n1] = pv[i];
    for (int i = l - 1; i <= m - 1; ++i) pv2[++n2] = pv[i];
    int m1 = convex_hull(pv1, n1, cv1);
    int m2 = convex_hull(pv2, n2, cv2);
    int w = minkowski_sum(cv1, m1, cv2, m2, mv);
    for (int i = 1; i <= w; ++i) sv[++s] = mv[i];
    fill(pv1 + 1, pv1 + n1 + 1, pv1[0]);
    fill(pv2 + 1, pv2 + n2 + 1, pv2[0]);
    fill(mv + 1, mv + w + 1, mv[0]);
    dc(l, m - 1); dc(m + 1, r);
}

int main(void) {
    ios::sync_with_stdio(0); cin.tie(0);
    #ifndef ONLINE_JUDGE
    ifstream cin("1.in");
    #endif // ONLINE_JUDGE
    int n, q; cin >> n >> q;
    for (int i = 1; i <= n; ++i)
        cin >> pv[i].x >> pv[i].y;

    dc(1, n);
    int m = convex_hull(sv, s, qv);
    cvq::init(qv, m);
    for (int i = 1; i <= q; ++i) {
        vec p; cin >> p.x >> p.y;
        if (i > 84476) exit(-114514);
        cout << cvq::crxmax(p).first << endl;
    }
    return 0;
}
