#include <bits/stdc++.h>
using namespace std;
typedef double dbl;
const dbl pi = acos(-1), eps = 1e-6;
int dc(dbl x) { return x < -eps ? -1 : x > eps ? 1 : 0; }
struct vec { dbl x, y; };
vec operator+(vec v1, vec v2) { return { v1.x + v2.x, v1.y + v2.y }; }
vec operator-(vec v1, vec v2) { return { v1.x - v2.x, v1.y - v2.y }; }
dbl operator*(vec v1, vec v2) { return v1.x * v2.x + v1.y * v2.y; }
dbl operator^(vec v1, vec v2) { return v1.x * v2.y - v1.y * v2.x; }
vec operator*(dbl k, vec v) { return { k * v.x, k * v.y }; }
bool operator<(vec v1, vec v2) { return v1.x==v2.x?v1.y<v2.y:v1.x<v2.x; }
bool operator==(vec v1, vec v2) { return v1.x==v2.x && v1.y == v2.y; }
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
    if (c1.r > c2.r) swap(c1, c2);
    dbl d = len(c1.o - c2.o);
    if (dc(d - (c1.r + c2.r)) >=0) return 0;
    if (dc(d - abs(c1.r - c2.r)) <= 0) {
        dbl r = min(c1.r, c2.r);
        return r * r * pi;
    }
    dbl x = (d * d + c1.r * c1.r - c2.r * c2.r) / (2 * d);
    dbl t1 = acos(x / c1.r), t2 = acos((d - x) / c2.r);
    return c1.r * c1.r * t1 + c2.r * c2.r * t2 - d * c1.r * sin(t1);
}

bool clitsc(cir c, line l, vec& p1, vec& p2) {
    dbl x = l.v * (l.p - c.o), y = l.v * l.v;
    dbl d = x * x - y * ((l.p - c.o) * (l.p - c.o) - c.r * c.r);
    if (dc(d) == -1) return false; d = max(d, 0.);
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