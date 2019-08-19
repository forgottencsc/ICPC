#include <bits/stdc++.h>
using namespace std;
typedef double dbl;
const dbl pi = acos(-1), eps = 1e-8;
int dc(dbl x) { return x < -eps ? -1 : x > eps ? 1 : 0; }
struct vec { dbl x, y; };
vec operator+(vec v1, vec v2) { return { v1.x + v2.x, v1.y + v2.y }; }
vec operator-(vec v1, vec v2) { return { v1.x - v2.x, v1.y - v2.y }; }
dbl operator*(vec v1, vec v2) { return v1.x * v2.x + v1.y * v2.y; }
dbl operator^(vec v1, vec v2) { return v1.x * v2.y - v1.y * v2.x; }
vec operator*(dbl k, vec v) { return { k * v.x, k * v.y }; }
bool operator<(vec v1, vec v2) { return v1.x==v2.x?v1.y<v2.y:v1.x<v2.x; }
dbl dot(vec v0, vec v1, vec v2) { return (v1 - v0) * (v2 - v0); }
dbl crx(vec v0, vec v1, vec v2) { return (v1 - v0) ^ (v2 - v0); }
dbl len(vec v) { return hypot(v.x, v.y); }
dbl arg(vec v) { dbl r = atan2(v.y, v.x); return r<0?2*pi+r:r; }
struct line { vec p, v; };
vec unif(vec v) { return (1./len(v))*v; }
vec univ(dbl f) { return { cos(f), sin(f) }; }
vec rot(vec p, dbl f) { return { cos(f)*p.x-sin(f)*p.y, sin(f)*p.x+cos(f)*p.y }; }
vec proj(line l, vec p) { return p+(((l.p-p)*l.v)/(l.v*l.v))*l.v; }
vec litsc(line l1, line l2) { return l2.p+((l1.v^(l2.p-l1.p))/(l2.v^l1.v))*l2.v; }
dbl lpdis(line l, vec p) { return fabs(crx(p, l.p, l.p + l.v)) / len(l.v); }
dbl area(vec* pv, int n) {
    dbl sum = pv[n] ^ pv[1];
    for (int i = 1; i <= n - 1; ++i)
        sum += (pv[i] ^ pv[i + 1]);
    return sum / 2;
}

int convex_hull(vec* pv, int n, vec* cv) {
    sort(pv + 1, pv + n + 1);
    int m = 0;
    for (int i = 1; i <= n; ++i) {
        while (m>1 && dc(crx(cv[m-1], cv[m], pv[i]))==-1) m--;
        cv[++m] = pv[i];
    }
    int k = m;
    for (int i = n - 1; i; --i) {
        while (m>k && dc(crx(cv[m-1], cv[m], pv[i]))==-1) m--;
        cv[++m] = pv[i];
    }
    return m>1?m-1:m;
}

bool judge(line l0, line l1, line l2) { return dc((litsc(l1, l2)-l0.p)^l0.v)==1; }
int halfplane_intersection(line* lv, int n, vec* pv) {
    static pair<pair<dbl,dbl>, int> a[N];
    for (int i = 1; i <= n; ++i)
        a[i] = { { arg(lv[i].v), lv[i].p*univ(arg(lv[i].v)-pi/2) }, i };
    sort(a + 1, a + n + 1);
    static int b[N], q[N]; int w = 0, l = 1, r = 0;
    for (int i = 1; i <= n; ++i)
        if (i == 1 || dc(a[i].first.first-a[i-1].first.first))
            b[++w] = a[i].second;
    for (int i = 1; i <= w; ++i) {
        while (l<r&&judge(lv[b[i]],lv[q[r]],lv[q[r-1]]))--r;
        while (l<r&&judge(lv[b[i]],lv[q[l]],lv[q[l+1]]))++l;
        q[++r]=b[i];
    }
    while(l<r&&judge(lv[q[l]],lv[q[r]],lv[q[r-1]]))--r;
    while(l<r&&judge(lv[q[r]],lv[q[l]],lv[q[l+1]]))++l;
    int m = 0; q[r+1]=q[l];
    for (int i = l; i <= r; ++i)
        pv[++m]=litsc(lv[q[i]],lv[q[i+1]]);
    return m;
}

int minkowski_sum(vec* cv1, int n1, vec* cv2, int n2, vec* cv) {
    static vec dv1[N], dv2[N], dv;
    for (int i = 1; i <= n1; ++i) dv1[i] = cv1[i + 1] - cv1[i];
    for (int i = 1; i <= n2; ++i) dv2[i] = cv2[i + 1] - cv2[i];
    int m = 0, p = 1, q = 1; cv[++m] = cv1[1] + cv2[1];
    while (p<=n1 || q<=n2) {
        if (p<=n1&&q<=n2) dv=dc(dv1[p]^dv2[q])==-1?dv1[p++]:dv2[q++];
        else if(p<=n1) dv=dv1[p++]; else dv=dv2[q++];
        while (m>1&&!dc((cv[m]-cv[m-1])^dv)) --m;
        cv[m+1]=cv[m]+dv;m++;
    }
    return m>1?m-1:m;
}

struct seg { vec p1, p2; };
dbl spdis(seg s, vec p) {
    if (dot(s.p1, s.p2, p) < eps) return len(p - s.p1);
    if (dot(s.p2, s.p1, p) < eps) return len(p - s.p2);
    return fabs(crx(p, s.p1, s.p2)) / len(s.p1 - s.p2);
}

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
