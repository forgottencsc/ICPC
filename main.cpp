#include <iostream>
#include <fstream>
#include <cmath>
#include <algorithm>
#define N 101
using namespace std;

typedef long long ll;

typedef double dbl;
const dbl pi = acos(-1), eps = 1e-10;
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
struct seg { vec p1, p2; };
dbl spdis(seg s, vec p) {
    if (dot(s.p1, s.p2, p) < eps) return len(p - s.p1);
    if (dot(s.p2, s.p1, p) < eps) return len(p - s.p2);
    return fabs(crx(p, s.p1, s.p2)) / len(s.p1 - s.p2);
}

int sitsc(seg s1, seg s2) {
    vec p1 = s1.p1, p2 = s1.p2, q1 = s2.p1, q2 = s2.p2;
    if (max(p1.x,p2.x)<min(q1.x,q2.x)||min(p1.x,p2.x)>max(q1.x,q2.x)) return 0;
    if (max(p1.y,p2.y)<min(q1.y,q2.y)||min(p1.y,p2.y)>max(q1.y,q2.y)) return 0;
    dbl x=crx(p2,p1,q1),y=crx(p2,p1,q2);
    dbl z=crx(q2,q1,p1),w=crx(q2,q1,p2);
    if (dc(x)==0&&dc(y)==0) return 3;
    if (dc(x)*dc(y)<0&&dc(z)*dc(w)<0) return 1;
    if (dc(x)*dc(y)<=0&&dc(z)*dc(w)<=0) return 2;
    return 0;
}

bool judge(line l0, line l1, line l2) { return dc((litsc(l1, l2)-l0.p)^l0.v)==1; }
int halfplane_intersection(line* lv, int n, vec* pv) {
    static pair<pair<dbl,dbl>, int> a[N];
    for (int i = 1; i <= n; ++i) {
        dbl f = arg(lv[i].v);
        a[i] = { { f, lv[i].p * univ(f-pi/2) }, i };
    }
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

vec pv[N];
bool used[N];
int id[N], ord[N];

int main(void) {
    ios::sync_with_stdio(0); cin.tie(0);
    #ifndef ONLINE_JUDGE
    ifstream cin("1.in");
    #endif // ONLINE_JUDGE
    int T; cin >> T;
    while(T--) {
        int n; cin >> n;
        for (int i = 1; i <= n; ++i)
            cin >> id[i] >> pv[i].x >> pv[i].y;
        fill(used + 1, used + n + 1, 0);
        fill(ord + 1, ord + n + 1, 0);
        for (int i = 1; i <= n; ++i)
            if (!ord[1] || pv[i].y < pv[ord[1]].y)
                ord[1] = i;
        used[ord[1]] = 1;
        for (int i = 1; i <= n - 1; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (used[j]) continue;
                if (!ord[i + 1] || dc(crx(pv[ord[i]], pv[j], pv[ord[i + 1]])) == 1
                                || (dc(crx(pv[ord[i]], pv[j], pv[ord[i + 1]])) == 0
                                    && len(pv[ord[i]]-pv[j]) < len(pv[ord[i]]-pv[ord[i+1]])))
                {
                    ord[i + 1] = j;
                }
            }
            used[ord[i + 1]] = 1;
        }
        cout << n; for (int i = 1; i <= n; ++i) cout << ' ' << id[ord[i]];
        cout << endl;
    }
    return 0;
}