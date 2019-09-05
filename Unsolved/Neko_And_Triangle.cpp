#include <bits/stdc++.h>
#define N 400001
#define M 4000001
using namespace std;
typedef long long dbl;
const dbl pi = acos(-1), eps = 0, inf=1.145e14;
int dc(dbl x) { return x < -eps ? -1 : x > eps ? 1 : 0; }
struct vec { dbl x, y; };
vec operator+(vec v1, vec v2) { return { v1.x + v2.x, v1.y + v2.y }; }
vec operator-(vec v1, vec v2) { return { v1.x - v2.x, v1.y - v2.y }; }
dbl operator*(vec v1, vec v2) { return v1.x * v2.x + v1.y * v2.y; }
dbl operator^(vec v1, vec v2) { return v1.x * v2.y - v1.y * v2.x; }
vec operator*(dbl k, vec v) { return { k * v.x, k * v.y }; }
bool operator<(vec v1, vec v2) { return v1.x==v2.x?v1.y<v2.y:v1.x<v2.x; }
bool operator>(vec v1, vec v2) { return v1.x==v2.x?v1.y>v2.y:v1.x>v2.x; }
dbl dot(vec v0, vec v1, vec v2) { return (v1 - v0) * (v2 - v0); }
dbl crx(vec v0, vec v1, vec v2) { return (v1 - v0) ^ (v2 - v0); }
dbl len(vec v) { return hypot(v.x, v.y); }
dbl arg(vec v) { dbl r = atan2(v.y, v.x); return r<0?2*pi+r:r; }
vec unif(vec v) { return (1./len(v))*v; }
vec univ(dbl f) { return { cos(f), sin(f) }; }
vec rot(vec p, dbl f) { return { cos(f)*p.x-sin(f)*p.y, sin(f)*p.x+cos(f)*p.y }; }
vec rot(vec o, vec p, dbl f) { return o + rot(p - o, f); }
vec rot90(vec p) { return { -p.y, p.x }; }

struct line { vec p, v; };
vec proj(line l, vec p) { return p+(((l.p-p)*l.v)/(l.v*l.v))*l.v; }
vec refl(vec o, vec p) { return o + o - p; }
vec refl(line l, vec p) { return refl(proj(l, p), p); }
vec litsc(line l1, line l2) { return l2.p+((l1.v^(l2.p-l1.p))/(l2.v^l1.v))*l2.v; }
dbl lpdis(line l, vec p) { return fabs(crx(p, l.p, l.p + l.v)) / len(l.v); }

struct seg { vec p1, p2; };
bool onseg(seg s, vec p){return!dc(crx(p,s.p1,s.p2))&&dc(dot(p, s.p1, s.p2))==-1;}

//  0为不相交，1为严格相交，2表示交点为某线段端点，3为线段平行且部分重合
int sitsc(seg s1, seg s2) {
    vec p1 = s1.p1, p2 = s1.p2, q1 = s2.p1, q2 = s2.p2;
    if (max(p1.x,p2.x)<min(q1.x,q2.x)||min(p1.x,p2.x)>max(q1.x,q2.x)) return 0;
    if (max(p1.y,p2.y)<min(q1.y,q2.y)||min(p1.y,p2.y)>max(q1.y,q2.y)) return 0;
    dbl x=crx(p2,p1,q1),y=crx(p2,p1,q2),z=crx(q2,q1,p1),w=crx(q2,q1,p2);
    if (dc(x)==0&&dc(y)==0) return 3;
    if (dc(x)*dc(y)<0&&dc(z)*dc(w)<0) return 1;
    if (dc(x)*dc(y)<=0&&dc(z)*dc(w)<=0) return 2;
    return 0;
}

dbl spdis(seg s, vec p) {
    if (dot(s.p1, s.p2, p) < eps) return len(p - s.p1);
    if (dot(s.p2, s.p1, p) < eps) return len(p - s.p2);
    return fabs(crx(p, s.p1, s.p2)) / len(s.p1 - s.p2);
}

struct cir { vec o; dbl r; };
dbl ccarea(cir c1, cir c2) {
    dbl d = len(c1.o - c2.o);
    if (dc(d - (c1.r + c2.r)) != -1) return 0;
    if (dc(d - abs(c1.r - c2.r)) <= 0) {
        dbl r = min(c1.r, c2.r);
        return r * r * pi;
    }
    dbl x = (d * d + c1.r * c1.r - c2.r * c2.r) / 2 * d;
    dbl t1 = acos(x / c1.r), t2 = acos((d - x) / c2.r);
    return c1.r * c1.r * t1 + c2.r * c2.r * t2 - d * c1.r * sin(t1);
}

bool clitsc(cir c, line l, vec& p1, vec& p2) {
    dbl x = l.v * (l.p - c.o), y = l.v * l.v;
    dbl d = x * x - y * ((l.p - c.o) * (l.p - c.o) - c.r * c.r);
    if (dc(d) == -1) return false; d = max(d, 0ll);
    vec p = l.p - (x / y) * l.v, w = (sqrt(d) / y) * l.v;
    p1 = p + w; p2 = p - w; return true;
}

bool ccitsc(cir c1, cir c2, vec& p1, vec& p2) {
    //assert(c1 != c2);
    dbl s1 = len(c1.o - c2.o);
    if (dc(s1 - c1.r - c2.r)==1||dc(s1-abs(c1.r-c2.r))==-1)
        return false;
    dbl s2 = (c1.r*c1.r-c2.r*c2.r)/s1, a=(s1+s2)/2, b=(s1-s2)/2;
    vec o = (a/(a+b)) * (c2.o-c1.o) + c1.o;
    vec d = sqrt(c1.r*c1.r-a*a) * rot90(unif(c2.o - c1.o));
    p1 = o + d; p2 = o - d;
    return true;
}

bool cptan(cir c, vec p, vec& p1, vec& p2) {
    dbl x = (p-c.o)*(p-c.o), y=x-c.r*c.r;
    if (y < eps) return false;
    vec o = (c.r*c.r/x)*(p-c.o);
    vec d =rot90((-c.r*sqrt(y)/x)*(p-c.o));
    o = o + c.o; p1 = o + d; p2 = o - d;
    return true;
}

bool ccetan(cir c1, cir c2, line& l1, line& l2) {
    //  assert(c1 != c2)
    if (!dc(c1.r - c2.r)) {
        vec v = rot90(c1.r * unif(c2.o - c1.o));
        l1 = { c1.o + v, c2.o - c1.o };
        l2 = { c1.o - v, c2.o - c1.o };
        return true;
    }
    else {
        vec p = (1/(c1.r-c2.r))*(c1.r*c2.o-c2.r*c1.o);
        vec p1, p2, q1, q2;
        if (cptan(c1,p,p1,p2)&&cptan(c2,p,q1,q2)) {
            if (c1.r < c2.r) swap(p1, p2), swap(q1, q2);
            l1 = { p1, q1 - p1 }; l2 = { p2, q2 - p2 };
            return true;
        }
    }
    return false;
}

bool ccitan(cir c1, cir c2, line& l1, line& l2) {
    vec p = (1/(c1.r + c2.r)) * (c2.r * c1.o + c1.r * c2.o);
    vec p1, p2, q1, q2;
    if (cptan(c1, p, p1, p2) && cptan(c2, p, q1, q2)) {
        l1 = { p1, q1 - p1 }; l2 = { p2, q2 - p2 };
        return true;
    }
    return false;
}

vec incenter(vec a, vec b, vec c) {
    dbl d1 = len(b-c),d2=len(c-a),d3=len(a-b),
        s = fabs(crx(a,b,c));
    return (1/(d1+d2+d3))*(d1*a+d2*b+d3*c);
}

vec circumcenter(vec a, vec b, vec c) {
    b=b-a; c=c-a; dbl d1 = b*b, d2 = c*c, d = 2*(b^c);
    return a - (1/d)*vec{b.y*d2-c.y*d1,c.x*d1-b.x*d2};
}

vec orthocenter(vec a, vec b, vec c) {
    vec ba = b - a, ca = c - a, bc = b - c;
    dbl y = ba.y*ca.y*bc.y,A=ca.x*ba.y-ba.x*ca.y,
        x0=(1/A)*(y+ca.x*ba.y*b.x-ba.x*ca.y*c.x),
        y0=(-ba.x)*(x0-c.x)/ba.y+ca.y;
    return { x0, y0 };
    //return litsc({a,rot90(b-c)},{b,rot90(c-a)});
}

int convex_hull(vec* p, int n, vec* c) {
    sort(p + 1, p + n + 1);
    int m = 0;
    c[1] = p[++m];
    for (int i = 1; i <= n; ++i) {
        while (m > 1 && dc(crx(c[m - 1], c[m], p[i])) != 1) m--;
        c[++m] = p[i];
    }
    int t = m;
    for (int i = n - 1; i; --i) {
        while (m > t && dc(crx(c[m - 1], c[m], p[i])) != 1) m--;
        c[++m] = p[i];
    }
    return m - (m > 1);
}

int minkowski_sum(vec* cv1, int n1, vec* cv2, int n2, vec* cv) {
    static vec dv1[N], dv2[N], dv;
    cv1[n1 + 1] = cv1[1]; cv2[n2 + 1] = cv2[1];
    for (int i = 1; i <= n1; ++i) dv1[i] = cv1[i + 1] - cv1[i];
    for (int i = 1; i <= n2; ++i) dv2[i] = cv2[i + 1] - cv2[i];
    int m = 0; cv[++m] = cv1[1] + cv2[1];
    int p1 = 1, p2 = 1;
    while (p1 <= n1 && p2 <= n2)
        ++m, cv[m] = cv[m - 1] + (dc((dv1[p1])^(dv2[p2]))!=-1?dv1[p1++]:dv2[p2++]);
    while (p1 <= n1)
        ++m, cv[m] = cv[m - 1] + dv1[p1++];
    while (p2 <= n2)
        ++m, cv[m] = cv[m - 1] + dv2[p2++];
    assert(cv[m].x == cv[1].x && cv[m].y == cv[1].y);
    return m - 1;
}

namespace cvq {
    vec c[M], lw[M], up[M];
    int n, n1, n2;

    void build(vec* cv, int n_) {
        copy(cv + 1, cv + n_ + 1, c); n = n_;
        int p = 0;
        for (int i = 1; i != n; ++i)
            if (c[p]<c[i]) p = i;
        copy(c, c + p + 1, lw);
        copy(c + p, c + n, up); up[n] = c[0];
        n1 = p + 1; n2 = n - p + 1;
    }

    pair<dbl, int> get_tangent(vec* cv, int n, vec p) {
        int l = 0, r = n - 2;
        while(l+1<r) {
            int m = (l+r)/2;
            if (dc((cv[m+1]-cv[m])^p)==1)r=m;
            else l = m;
        }
        pair<dbl,int> p1(p^cv[r],r),p2(p^cv[0],0);
        return max(p1, p2);
    }

    void upd_tangent(vec p, int id, int& i0, int& i1) {
        if (dc(crx(p,c[i0],c[id]))==1) i0=id;
        if (dc(crx(p,c[i1],c[id]))==-1) i1=id;
    }

    void bin_search(int l, int r, vec p, int& i0, int &i1) {
        if (l == r) return;
        upd_tangent(p, l % n, i0, i1);
        int sl = dc(crx(p,c[l%n],c[(l+1)%n]));
        while(l+1<r){
            int m = (l + r) / 2;
            int sm = dc(crx(p, c[m%n], c[(m+1)%n]));
            if (sm == sl) l = m;
            else r = m;
        }
        upd_tangent(p, r % n, i0 , i1);
    }

    bool contain(vec p) {
        if (p.x<lw[0].x||p.x>up[0].x) return false;
        int id = lower_bound(lw, lw + n1, vec{p.x,-inf})-lw;
        if (!dc(lw[id].x-p.x)) {
            if (dc(lw[id].y-p.y)==1)
                return false;
        }
        else if (dc(crx(p,lw[id-1],lw[id]))==-1)
            return false;
        id = lower_bound(up, up + n2, vec{ p.x, inf }, greater<vec>())-up;
        if (!dc(up[id].x-p.x)) {
            if (dc(up[id].y-p.y)==-1)
                return false;
        }
        else if (dc(crx(p,up[id-1],up[id]))==-1)
            return false;
        return true;
    }

    bool get_tangent(vec p, int& i0, int& i1) {
        if (contain(p)) return false;
        i0 = i1 = 0;
        int id = lower_bound(lw, lw + n1, p) - lw;
        bin_search(0, id, p, i0, i1);
        bin_search(id, n1, p, i0, i1);
        id = lower_bound(up, up + n2, p, greater<vec>()) - up;
        bin_search(n1 - 1, n1 - 1 + id, p, i0, i1);
        bin_search(n1 - 1 + id, n1 - 1 + n2, p, i0, i1);
        return true;
    }

    pair<dbl, int> get_crxmax(vec p) {
        pair<dbl, int> r = get_tangent(up, n2, p);
        r.second += n1 - 1;
        r = max(r, get_tangent(lw, n1, p));
        return r;
    }

//    bool get_itsc(line l, int& i0, int& i1) {
//        int p0 = get_crxmax(u - v), p1 = get_crxmax(v - u);
//        if (dc(crx(u,v,c[p0]))*dc(crx(u,v,c[p1]))>=0)
//            return false;
//        if (p0 > p1) swap(p0, p1);
//        i0 = binary_search(u, v, p0, p1);
//        i1 = binary_search(u, v, p1, p0 + n);
//        return true;
//    }

}

vec pv0[N], pv[N], qv[N], mv[N], cvs[M], cv[M]; int cc;


vec pv1[N], pv2[N], cv1[N], cv2[N];
//long long sum = 0;
void dc(int l, int r) {
    if (l > r) return;
    int m = (l + r) >> 1;
    dc(l, m - 1); dc(m + 1, r);
    int n1 = 0, n2 = 0;
    for (int i = m; i <= r; ++i)
        pv1[++n1] = pv[i];
    int m1 = convex_hull(pv1, n1, cv1);
    for (int i = m - 1; i >= l - 1; --i)
        pv2[++n2] = -1 * pv[i];
    //sum += 1ll * n1 * n2;
    int m2 = convex_hull(pv2, n2, cv2);
    int w = minkowski_sum(cv1, m1, cv2, m2, mv);
    for (int i = 1; i <= w; ++i)
        cvs[++cc] = mv[i];
}

void gen() {
    ofstream cout("1.in");
    ofstream cans("1.out");
    srand(time(0));
    int n = 100000, m = 100000;
    cout << n << ' ' << m << endl;
    vector<vec> p(n), q(m);
    vector<vec> s(n + 1, { 0, 0 });
    for (int i = 0; i != n; ++i) {
        p[i] = { rand() + rand(), rand() + rand() };
        cout << p[i].x << ' ' << p[i].y << endl;
        s[i + 1] = s[i] + p[i];
    }


    for (int e = 0; e != m; ++e) {
        q[e] = { rand() + rand(), rand() + rand() };
        cout << q[e].x << ' ' << q[e].y << endl;
//        dbl ans = LLONG_MIN;
//        for (int i = 0; i != n; ++i)
//            for (int j = i + 1; j <= n; ++j)
//                ans = max(ans, q[e] ^ (s[j] - s[i]));
//        cans << ans << endl;
    }
    cout.close();
    cans.close();
}



int main(void) {
//    int tc = 0;
//    while (++tc) {
//        cout << tc << endl;
//        gen();

    ios::sync_with_stdio(0); cin.tie(0);
    #ifndef ONLINE_JUDGE
    ifstream cin("1.in");
    //ifstream cans("1.out");
    #endif // ONLINE_JUDGE

    int n, m; cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        cin >> pv[i].x >> pv[i].y;
        pv0[i] = pv[i];
        pv[i] = pv[i - 1] + pv[i];
    }

    cc = 0;
    dc(1, n);
    //assert(sum == 1ll * n * (n + 1) / 2);
    //cout << cc << endl;

    int w = convex_hull(cvs, cc, cv);
    cvq::build(cv, w);
    for (int i = 1; i <= m; ++i) {
        cin >> qv[i].x >> qv[i].y;
        auto res = cvq::get_crxmax(qv[i]);
        vec v = cvq::c[res.second];
        //cout << res.first << endl;

        dbl a = LLONG_MIN;
        for (int j = 1; j <= w; ++j)
            a = max(a, qv[i] ^ cv[j]);
        cout << a << endl;
        //dbl ans; cans >> ans;
//        if (ans != res.first) {
//            cout << tc << ' ' << i  << endl;
//            cout << boolalpha << (a == ans) << ' ' << (a == res.first) << ' '<< (ans == res.first) << endl;
//            cout << a << ' ' << ans << endl;
            //assert(a == ans);
            //assert(ans == res.first);
//        }
    }
//
//}
    return 0;
}
