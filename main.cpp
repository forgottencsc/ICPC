#include <bits/stdc++.h>
#define N 1005
using namespace std;


typedef double dbl;
const dbl pi = acos(-1), eps = 1e-6;
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

typedef pair<dbl, int> pdi;

namespace cvq {
    vec c[N];
    int w, n;

    void init(vec* cv, int m) {
        copy_n(cv + 1, m, c); n = m; c[n] = c[0];
        rotate(c, min_element(c, c + n), c + n);
        w = 0; while (c[w] < c[w + 1]) ++w;
    }

    //  0：在凸包外，1：在凸包内，2：在凸包上
    int contain(vec p) {
        if (p.x < c[0].x || c[w].x < p.x) return false;
        int p1 = lower_bound(c, c + w + 1, p);
        int p2 = lower_bound(c + w, c + n + 1, p, greater<vec>());

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

    bool tangent(vec p, int l, int r) {

    }


};

const dbl mm = 1e3;

mt19937_64 mt(time(0));

int ui(int l, int r) { return uniform_int_distribution<int>(l, r)(mt);}

dbl ud(dbl l = -mm, dbl r = mm) {
    uniform_real_distribution<dbl> urd(l, r);
    return urd(mt);
}

vec up(dbl m = 1e3) { return { ud(-m, m), ud(-m, m) }; }

bool is_convex(vec* pv, int n) {
    pv[n + 1] = pv[1];
    pv[n + 2] = pv[2];
    for (int i = 1; i <= n; ++i) {
        if (sgn(crx(pv[i], pv[i + 1], pv[i + 2])) < 0)
            cout << crx(pv[i], pv[i + 1], pv[i + 2]) << endl;
    }
    return true;
}

void uc(vec* cv, int n) {
    vector<dbl> fv(n);
    for (int i = 0; i != n; ++i)
        fv[i] = ud(0, 2 * pi);
    sort(fv.begin(), fv.end());
    rotate(fv.begin(), fv.begin() + ui(0, n - 1), fv.end());
    vec p = up(10); dbl r = ud(0, 10);
    for (int i = 0; i != n; ++i)
        cv[i + 1] = p + univ(fv[i]) * r;
    cv[n + 1] = cv[1];
}

vec cv[N];

pair<dbl, int> crxmax(vec p, int n) {
    pair<dbl, int> res = { -DBL_MAX, -1 };
    for (int i = 0; i != n; ++i)
        res = max(res, pair<dbl, int>(p ^ cvq::c[i], i));
    return res;
}


signed main(void) {
    ios::sync_with_stdio(0); cin.tie(0);
    #ifndef ONLINE_JUDGE
    ifstream cin("1.in");
    #endif // ONLINE_JUDGE
    cout << setprecision(7) << fixed;
    int T = 1000;
    while (T--) {
        int n = 1000, q = 1000;
        uc(cv, n);
        is_convex(cv, n);
        cvq::init(cv, n);
        while(q--) {
            vec p = up(20); bool flg = 1;
            for (int i = 1; i <= n; ++i)
                if (sgn(crx(cv[i], cv[i + 1], p) < 0))
                    flg = 0;
            if (flg) continue;
            pair<dbl, int> r1 = crxmax(p, n);
            pair<dbl, int> r2 = cvq::crxmax(p);
            if (sgn(r1.first - r2.first)) {
                cout << abs(r1.first - r2.first) << endl;
                cout << r1.second << ' ' << r2.second << endl;
                cout << (p ^ cvq::c[r1.second]) << ' ' << r1.first << endl;
            }
            //if (r1.second != r2.second) cout << r1.second << ' ' << r2.second << endl;
        }
    }
    return 0;
}
