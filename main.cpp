#include <bits/stdc++.h>
#define N 10005
using namespace std;
typedef double dbl;
const dbl pi = acos(-1), eps = 1e-15;
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

const dbl mm = 1e9;

mt19937_64 mt(time(0));

int ui(int l, int r) { return uniform_int_distribution<int>(l, r)(mt);}

dbl ud(dbl l = -mm, dbl r = mm) {
    uniform_real_distribution<dbl> urd(l, r);
    return urd(mt);
}

vec up(dbl m = mm) { return { ud(-m, m), ud(-m, m) }; }

bool is_convex(vec* pv, int n) {
    pv[n + 1] = pv[1];
    pv[n + 2] = pv[2];
    for (int i = 1; i <= n; ++i) {
        if (sgn(crx(pv[i], pv[i + 1], pv[i + 2])) < 0)
            cout << crx(pv[i], pv[i + 1], pv[i + 2]) << endl;
    }
    return true;
}

int uc(vec* cv, int n) {
    static vec pv[N];
    vector<dbl> fv(n);
    for (int i = 0; i != n; ++i)
        fv[i] = ud(0, 2 * pi);
    sort(fv.begin(), fv.end());
    rotate(fv.begin(), fv.begin() + ui(0, n - 1), fv.end());
    dbl r = ud(1, mm);
    bool rec = (ui(0, 2) == 0);
    for (int i = 0; i != n; ++i) {
        pv[i + 1] = univ(fv[i]) * r;
        //pv[i + 1].x = round(pv[i + 1].x);
        //pv[i + 1].y = round(pv[i + 1].y);
    }
    return convex_hull(pv, n, cv);
}

pair<dbl, int> crxmax(vec p) {
    pair<dbl, int> res = { -DBL_MAX, -1 };
    for (int i = 0; i != cvq::n; ++i)
        res = max(res, pair<dbl, int>(p ^ cvq::c[i], i));
    return res;
}

bool chk_cont(vec* cv, int n, vec p) {
    for (int i = 0; i != n; ++i)
        if (sgn(crx(cv[i], cv[i + 1], p)) < 0)
            return false;
    return true;
}

bool chk_ltan(vec* cv, int n, vec p, vec q) {
    for (int i = 0; i != n; ++i)
        if (crx(p, q, cv[i]) > 0)
            return false;
    return true;
}

bool chk_rtan(vec* cv, int n, vec p, vec q) {
    for (int i = 0; i != n; ++i)
        if (crx(p, q, cv[i]) < 0)
            return false;
    return true;
}

int tc = 0;

vec cv[N], pv[N]; dbl ans[N];

bool chk_crxmax(int n, int m) {
    bool fail = 0;
    n = uc(cv, n);
    cvq::init(cv, n);
    for (int i = 1; i <= m; ++i) {
        pv[i] = up();
        ans[i] = crxmax(pv[i]).first;
        if (sgn(ans[i] - cvq::crxmax(pv[i]).first))
            fail = 1;
    }
    if (fail) {
        ++tc;
        ofstream os1(to_string(tc) + ".fi");
        ofstream os2(to_string(tc) + ".fo");
        os1 << n << ' ' << m << endl;
        for (int i = 1; i <= n; ++i) {
            os1 << cv[i].x << ' ' << cv[i].y << endl;
        }
        for (int i = 1; i <= m; ++i) {
            os1 << pv[i].x << ' ' << pv[i].y << endl;
            os2 << ans[i] << endl;
        }
    }
    return !fail;
}

bool chk_tan(int n, int m) {bool fail = 0;
    n = uc(cv, n);
    cvq::init(cv, n);
    for (int i = 1; i <= m; ++i) {
        pv[i] = up();
        int lp, rp;
        if (!cvq::tangent(pv[i], lp, rp)) {
            if (!chk_cont(cvq::c, n, pv[i]))
                fail = 1;
        }
        else {
            if (!chk_ltan(cvq::c, n, pv[i], cvq::c[lp]))
                fail = 1;
            if (!chk_rtan(cvq::c, n, pv[i], cvq::c[rp]))
                fail = 1;
        }
    }
    if (fail) {
        ++tc;
        ofstream os1(to_string(tc) + ".fi");
        ofstream os2(to_string(tc) + ".fo");
        os1 << n << ' ' << m << endl;
        for (int i = 1; i <= n; ++i) {
            os1 << cv[i].x << ' ' << cv[i].y << endl;
        }
        for (int i = 1; i <= m; ++i) {
            os1 << pv[i].x << ' ' << pv[i].y << endl;
        }
        res = rs[i];
        while (!pq.empty()) res += pq.top(), pq.pop();
        ans = max(ans, res);
        for (int j = 0; j != n2; ++j)
            cs[j] += a[i][j];
    }

    for (int i = 0; i != n2; ++i) {
        pq.push(cs[i]);
        if (pq.size() > 4) pq.pop();
    }
    return !fail;
}

int main(void) {
    ios::sync_with_stdio(0); cin.tie(0);
    #ifndef ONLINE_JUDGE
    ifstream cin("1.in");
    #endif // ONLINE_JUDGE

    int succ = 0, w = 0;
    while(tc <= 10) {
        ++w;
        bool f;
        if (w % 2) {
            f = chk_crxmax(1000,1000);
        }
        else {
            f = chk_tan(1000, 1000);
        }
        if (!f)
            cout << "Failed: " << tc <<endl;
        else succ++;
        if (succ % 100 == 0)
            cout << "Success: " << succ << endl;
    }

    return 0;
}