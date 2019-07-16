#include <bits\stdc++.h>
#define sq(x) ((x) * (x))
using namespace std;

typedef double dbl;
static const dbl eps = 1e-9;
static const dbl pi = acos(-1);

int sgn(dbl d) { return d < -eps ? -1 : d > eps ? 1 : 0; }
int dc(dbl d1, dbl d2) { return sgn(d1 - d2); }

struct vec { dbl x, y; }; struct vlst { int s; vec v[4]; };
struct seg { vec p1, p2; }; struct slst { int s; seg v[4]; };


vec operator+(vec p1, vec p2) { return { p1.x + p2.x, p1.y + p2.y }; }
vec operator-(vec p1, vec p2) { return { p1.x - p2.x, p1.y - p2.y }; }
dbl operator*(vec p1, vec p2) { return p1.x * p2.x + p1.y * p2.y; }
dbl operator^(vec p1, vec p2) { return p1.x * p2.y - p1.y * p2.x; }
vec operator*(dbl k, vec p) { return { k * p.x, k * p.y }; }
vec operator-(vec p) { return { -p.x, -p.y }; }

dbl len(vec p) { return hypot(p.x, p.y); }
dbl dis(vec p1, vec p2) { return len(p1 - p2); }
dbl arg(vec p) { return atan2(p.y, p.x); }

dbl crx(vec p0, vec p1, vec p2) { return (p1 - p0) ^ (p2 - p1); }
dbl det3(vec v1, vec v2, vec v3) { return (v1 ^ v2) + (v2 ^ v3) + (v3 ^ v1); }

vec univ(dbl f) { return { cos(f), sin(f) }; }
vec unif(vec p) { return (1 / len(p)) * p; }

vec rot(vec p, dbl f) { return { p.x * cos(f) - p.y * sin(f), p.x * sin(f) + p.y * cos(f) }; }
vec rot(vec p, dbl f, vec o) { return o + rot(p - o, f); }

//	line and circles
struct line {
	dbl a, b, c;
	vec v() const { return { -b, a }; }
};

struct cir {
	vec p; dbl r;
	vec operator[](dbl f) { return p + r * univ(f); }
};

struct ray {
	vec p; dbl f;
	vec v() const { return univ(f); }
	vec operator[](dbl t) const { return p + t * v(); }
	dbl operator[](vec px) const { return (px - p) * v(); }
};

line to_line(ray r) {
	vec v = univ(r.f);
	return { v.x, v.y, -r.p * v };
}

dbl dis(ray r, vec p) {
	return (p - r.p) * r.v() < 0 ? dis(p, r.p) : dis(to_line(r), p);
}

vec operator^(line l1, line l2) {
	vec v1 = { l1.a , l2.a }, v2 = { l1.b, l2.b }, v3 = { l1.c, l2.c };
	dbl D1 = v2 ^ v3, D2 = v3 ^ v1, D = v1 ^ v2;
	return { D1 / D, D2 / D };
}


line con(vec p1, vec p2) { return { p1.y - p2.y, p2.x - p1.x, p1 ^ p2 }; }
line prl(line l, vec p) { return { l.a, l.b, -l.a * p.x - l.b * p.y }; }
line ppd(line l, vec p) { return { -l.b, l.a, l.b * p.x - l.a * p.y }; }
line vbs(seg s) { return ppd(con(s.p1, s.p2), 0.5 * (s.p1 + s.p2)); }

vec proj(line l, vec p) { return ppd(l, p) ^ l; }
vec sym(line l, vec p) { return 2 * proj(l, p) - p; }

dbl dis0(line l, vec p) { return l.a * p.x + l.b * p.y + l.c; }
dbl dis(line l, vec p) { return abs(dis0(l, p)) / hypot(l.a, l.b); }
dbl ang(line l1, line l2) { return acos(fabs(unif(l1.v()) * unif(l2.v()))); }


vlst intersection(cir c, line l) {
	dbl d = dis(l, c.p);
	if (d > c.r) return { 0, {} };
	if (d == c.r) return { 1, { ppd(l, c.p) ^ l } };
	else {
		vec p = ppd(l, c.p) ^ l, v = unif(p - c.p);
		dbl w = sqrt(sq(c.r) - sq(d)); v = { -v.y, v.x };
		return { 2, { p + w * v, p - w * v } };
	}
}

vlst intersection(cir c1, cir c2) {
	if (c1.r < c2.r) swap(c1, c2);
	dbl d = dis(c1.p, c2.p);
	if (d < c1.r - c2.r || d > c1.r + c2.r) return { 0, {} };
	else if (c1.r - c2.r < d && d < c1.r + c2.r) {
		dbl f = arg(c2.p - c1.p),
			df = acos((sq(c1.r) + sq(d) - sq(c2.r)) / (2 * c1.r * d));
		return { 2, { c1[f + df], c1[f - df] } };
	}
	else return { 1, { c1[arg(c2.p - c1.p)] } };
}


vlst tangent(cir c, vec p) {
	dbl d = dis(p, c.p);
	if (d < c.r) return { 0, {} };
	else if (d == c.r) return { 1, { p } };
	else {
		dbl f = arg(p - c.p), df = acos(c.r / d);
		return { 2, { c[f + df], c[f - df] } };
	}
}

slst tangent(cir c1, cir c2) {
	if (c1.r < c2.r) swap(c1, c2);
	dbl d = dis(c1.p, c2.p);
	if (d < c1.r - c2.r) return { 0, {} };
	dbl f = arg(c2.p - c1.p);
	if (c1.r - c2.r == d) return { 1, { c1[f], c1[f] } };
	else if (c1.r - c2.r < d) {
		slst res;
		dbl df = acos((c1.r - c2.r) / d);
		res.s = 2;
		res.v[0] = { c1[f + df], c2[f + df] };
		res.v[1] = { c1[f - df], c2[f - df] };
		if (c1.r + c2.r == d) {
			res.s = 3;
			res.v[2] = { c1[f], c1[f] };
		}
		else if (c1.r + c2.r < d) {
			df = acos((c1.r + c2.r) / d); res.s = 4;
			res.v[2] = { c1[f + df], c2[f + df + pi] };
			res.v[3] = { c1[f - df], c2[f - df + pi] };
		}
		return res;
	}
}



//	Triangles
dbl S(vec p1, vec p2, vec p3) { return fabs(crx(p1, p2, p3)) / 2; }

cir incircle(vec p1, vec p2, vec p3) {
	dbl d12 = dis(p1, p2), d13 = dis(p1, p3), d23 = dis(p2, p3);
	dbl c = d12 + d13 + d23;
	vec I = { (p1.x * d23 + p2.x * d13 + p3.x * d12) / c,
			  (p1.y * d23 + p2.y * d13 + p3.y * d12) / c };
	return { I , 2 * S(p1, p2, p3) / c };
}

cir circumcircle(vec p1, vec p2, vec p3) {
	dbl d1 = p1 * p1, d2 = p2 * p2, d3 = p3 * p3;
	dbl D = 2 * det3(p1, p2, p3),
		D1 = det3({ d1, p1.y }, { d2, p2.y }, { d3, p3.y }),
		D2 = det3({ p1.x, d1 }, { p2.x, d2 }, { p3.x, d3 });
	vec O = { D1 / D, D2 / D };
	return { O, dis(p1, O) };
}


//	Predicative functions
bool on(line l, vec p) { return !dis0(l, p); }
bool ppd(line l1, line l2) { return !sgn(l1.v() * l2.v()); }
bool prl(line l1, line l2) { return !sgn(l1.v() ^ l2.v()); }

//	to be tested
bool on(seg s, vec p) {
	return ((s.p1 - p) ^ (s.p2 - p)) == 0
		&& min(s.p1.x, s.p2.x) <= p.x
		&& p.x <= max(s.p1.x, s.p2.x);
}

//	to be tested
dbl dis(seg s, vec p) {
	line l = con(s.p1, s.p2), l1 = ppd(l, s.p1), l2 = ppd(l, s.p2);
	dbl s1 = dis0(l1, p), s2 = dis0(l2, p);
	if (s1 * s2 < 0) return dis(l, p);
	else if (abs(s1) < abs(s2)) return dis(s.p1, p);
	else return dis(s.p2, p);
}
