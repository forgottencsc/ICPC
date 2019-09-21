#include <bits/stdc++.h>
#define N 10005
using namespace std;
typedef double dbl;
const dbl pi = acos(-1), eps = 1e-6;
int sgn(dbl x) { return x < -eps ? -1 : x > eps ? 1 : 0; }
struct vec { dbl x, y; };
vec operator+(vec v1, vec v2) { return { v1.x + v2.x, v1.y + v2.y }; }
vec operator-(vec v1, vec v2) { return { v1.x - v2.x, v1.y - v2.y }; }
dbl operator*(vec v1, vec v2) { return v1.x * v2.x + v1.y * v2.y; }
dbl operator^(vec v1, vec v2) { return v1.x * v2.y - v1.y * v2.x; }
vec operator*(vec v, dbl k) { return { k * v.x, k * v.y }; }
vec operator/(vec v, dbl k) { return { v.x / k, v.y / k }; }
bool operator<(vec v1, vec v2) { return v1.x==v2.x?v1.y<v2.y:v1.x<v2.x; }
bool operator==(vec v1, vec v2) { return v1.x==v2.x && v1.y == v2.y; }
bool operator>(vec v1, vec v2) { return v1.x==v2.x?v1.y>v2.y:v1.x>v2.x; }
dbl dot(vec v0, vec v1, vec v2) { return (v1 - v0) * (v2 - v0); }
dbl crx(vec v0, vec v1, vec v2) { return (v1 - v0) ^ (v2 - v0); }
dbl len(vec v) { return hypot(v.x, v.y); }
dbl arg(vec v) { dbl r = atan2(v.y, v.x); return r<0?2*pi+r:r; }
vec unif(vec v) { return v/len(v); }
vec univ(dbl f) { return { cos(f), sin(f) }; }
vec rot(vec p, dbl f) { return { cos(f)*p.x-sin(f)*p.y, sin(f)*p.x+cos(f)*p.y }; }
vec rot(vec o, vec p, dbl f) { return o + rot(p - o, f); }
vec rot90(vec p) { return { -p.y, p.x }; }

struct line { vec p, v; };
vec proj(line l, vec p) { return p+l.v*(((l.p-p)*l.v)/(l.v*l.v)); }
vec refl(vec o, vec p) { return o + o - p; }
vec refl(line l, vec p) { return refl(proj(l, p), p); }
vec litsc(line l1, line l2) { return l2.p+l2.v*((l1.v^(l2.p-l1.p))/(l2.v^l1.v)); }
dbl lpdis(line l, vec p) { return fabs(crx(p, l.p, l.p + l.v)) / len(l.v); }

//  0为不相交，1为严格相交，2表示交点为某线段端点，3为线段平行且部分重合
struct seg { vec p1, p2; };
bool onseg(seg s, vec p){return!sgn(crx(p,s.p1,s.p2))&&sgn(dot(p, s.p1, s.p2))==-1;}
bool lsitsc(seg s, line l) {
    return sgn(crx(l.p,l.p+l.v,s.p1))*sgn(crx(l.p,l.p+l.v,s.p2))<=0;
}
int sitsc(seg s1, seg s2) {
    vec p1 = s1.p1, p2 = s1.p2, q1 = s2.p1, q2 = s2.p2;
    if (max(p1.x,p2.x)<min(q1.x,q2.x)||min(p1.x,p2.x)>max(q1.x,q2.x)) return 0;
    if (max(p1.y,p2.y)<min(q1.y,q2.y)||min(p1.y,p2.y)>max(q1.y,q2.y)) return 0;
    dbl x=crx(p2,p1,q1),y=crx(p2,p1,q2),z=crx(q2,q1,p1),w=crx(q2,q1,p2);
    if (sgn(x)==0&&sgn(y)==0) return 3;
    if (sgn(x)*sgn(y)<0&&sgn(z)*sgn(w)<0) return 1;
    if (sgn(x)*sgn(y)<=0&&sgn(z)*sgn(w)<=0) return 2;
    return 0;
}

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


typedef long long ll;
typedef pair<dbl, int> pdi;
const dbl inf = 1e10;
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

    pdi crxmax0(int l, int r, vec p) {
        int r0 = r;
        while (l <= r) {
            int m = (l + r) >> 1;
            if ((p ^ (c[m + 1] - c[m])) >= 0) l = m + 1;
            else r = m - 1;
        }
        return pdi(p^c[l],l % n);
    }

    pdi crxmax(vec p) {
        pdi res = p.x <= 0 ? crxmax0(0, w - 1, p) : crxmax0(w, n - 1, p);
        return max({ res, pdi(p ^ c[0], 0), pdi(p ^ c[w], w) });
    }
    pdi crxmin(vec p) { return crxmax(p * -1); }

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

    int secant0(line s, int l, int r) {
        while (l <= r) {
            int m = (l + r) >> 1;
            if (crx(s.p, s.p + s.v, c[m%n]) <= 0)
                r = m - 1;
            else l = m + 1;
        }
        return r % n;
    }

    bool secant(line s, int& p1, int& p2) {
        pdi lc = crxmax(s.v), rc = crxmin(s.v);
        int lp = lc.second, rp = rc.second;
        if (crx(s.p, s.p + s.v, c[lp]) * crx(s.p, s.p + s.v, c[rp]) > 0)
            return false;
        p1 = secant0(s, lp, rp < lp ? rp + n : rp);
        p2 = secant0({ s.p, s.v * -1 }, rp, lp < rp ? lp + n : lp);
        return true;
    }
};

int main(void) {
    cout << setprecision(20) << fixed;
    ios::sync_with_stdio(0); cin.tie(0);
    #ifndef ONLINE_JUDGE
    ifstream cin("1.fi");
    #endif // ONLINE_JUDGE

//    int n, m; cin >> n >> m;
//    for (int i = 1; i <= n; ++i)
//        cin >> cv[i].x >> cv[i].y;
//
//    cvq::init(cv, n);
//    for (int i = 1; i <= m; ++i) {
//        cin >> lv[i].p.x >> lv[i].p.y;
//        cin >> lv[i].v.x >> lv[i].v.y;
//        int p1, p2;
//        bool fail = 0;
//        if (!cvq::secant(lv[i], p1, p2)) {
//            for (int j = 0; j != n; ++j)
//                if (lsitsc({ cvq::c[j], cvq::c[j + 1]}, lv[i]))
//                    fail = 1;
//        }
//        else {
//            if (!lsitsc({ cvq::c[p1], cvq::c[p1 + 1] }, lv[i]))
//                fail = 1;
//            if (!lsitsc({ cvq::c[p2], cvq::c[p2 + 1] }, lv[i]))
//                fail = 1;
//        }
//        if (fail)
//            cout << i << ' ';
//        cout << endl;
//    }


    check();

    return 0;
}