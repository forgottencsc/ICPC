#include <bits/stdc++.h>
#define N 100001
using namespace std;

typedef double dbl;
typedef long long ll;
typedef pair<int, int> pii;

typedef set<pii, function<bool(pii p1, pii p2)>> bst;
typedef bst::iterator iter;

const dbl eps = 1e-8;
int sgn(dbl x) { return x < -eps ? -1 : x > eps; }

struct vec { dbl x, y; };
vec operator+(vec v1, vec v2) { return { v1.x + v2.x, v1.y + v2.y }; }
vec operator-(vec v1, vec v2) { return { v1.x - v2.x, v1.y - v2.y }; }
dbl operator*(vec v1, vec v2) { return v1.x * v2.x + v1.y * v2.y; }
dbl operator^(vec v1, vec v2) { return v1.x * v2.y - v1.y * v2.x; }
vec operator*(vec v, dbl k) { return { v.x * k, v.y * k }; }
vec operator/(vec v, dbl k) { return { v.x / k, v.y / k }; }
dbl len(vec v) { return hypot(v.x, v.y); }
dbl crx(vec p0, vec p1, vec p2) { return (p1 - p0) ^ (p2 - p0); }

struct line { vec p, v; };
vec litsc(line l1, line l2) { return l2.p + l2.v * ((l1.v ^ (l2.p - l1.p)) / (l2.v ^ l1.v)); }

pii iv[N];
vec pv[N];
int pc[N];
int cnt[N], lid[N], rid[N];

pii ss[N]; iter pos[N];

vector<int> ei[N], eo[N];

int main(void) {
    ios::sync_with_stdio(0); cin.tie(0);
    #ifndef ONLINE_JUDGE
    ifstream cin("1.in");
    #endif // ONLINE_JUDGE

    int n = 0, m, k, sc = 0; cin >> m;
    for (int i = 1; i <= m; ++i) {
        cin >> cnt[i];
        for (int j = 1; j <= cnt[i]; ++j) {
            int x, y; cin >> x >> y;
            pv[n + j].x = x; pv[n + j].y = y;
            int d = gcd(x, y);
            iv[n + j].first = x / d;
            iv[n + j].second = y / d;
        }
        lid[i] = n + 1;
        n += cnt[i];
        rid[i] = n;
    }

    vector<pii> is(iv + 1, iv + n + 1);
    sort(is.begin(), is.end()); is.erase(unique(is.begin(), is.end()), is.end());
    k = is.size();

    auto icmp = [](pii p1, pii p2) { return p1.first * p2.second - p1.second * p2.first > 0; };
    auto ipar = partition(is.begin(), is.end(), [](pii p) { return p.second >= 0; });
    sort(is.begin(), ipar, icmp); sort(ipar, is.end(), icmp);
    vec o = { 0, 0 };
    line dir0 = { o, { is[0].first, is[0].second } }, dir1, dir2;
    dir1.p = dir2.p = o;
    map<pii, int> im;
    for (int i = 0; i != k; ++i) im[is[i]] = i + 1;
    for (int i = 1; i <= n; ++i) pc[i] = im[iv[i]];

    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= cnt[i]; ++j) {
            int u = j - 1, v = j % cnt[i];
            u += lid[i]; v += lid[i];
            if (pc[u] == pc[v]) continue;
            if (sgn(pv[u] ^ pv[v]) < 0)
                swap(u, v);
            if (pc[u] < pc[v] || pc[v] == 1) {
                int id = ++sc;
                ss[id] = { u, v };
                ei[pc[u]].push_back(id);
                eo[pc[v]].push_back(id);
            }
            else {
                line sd = { pv[u], pv[v] - pv[u] };
                pv[++n] = litsc(sd, dir0); pc[n] = 1;
                int id = ++sc;
                ss[id] = { u, n };
                ei[pc[u]].push_back(id);
                eo[pc[n]].push_back(id);
                id = ++sc;
                ss[id] = { n, v };
                ei[pc[n]].push_back(id);
                eo[pc[v]].push_back(id);
            }
        }
    }

    bst s([&](pii p1, pii p2) {
        line l1 = { pv[p1.first], pv[p1.second] }; l1.v = l1.v - l1.p;
        line l2 = { pv[p2.first], pv[p2.second] }; l2.v = l2.v - l2.p;
        dbl del = len(litsc(dir1, l1)) - len(litsc(dir1, l2));
        if (!sgn(del)) {
            assert(p1.first == p2.first);
            del = crx(pv[p1.first], pv[p1.second], pv[p2.second]);
        }
        return del < 0;
    });

     dbl ans = 0;
    for (int i = 1; i <= k; ++i) {
        pii du = is[i - 1], dv = is[i % k];
        if (i != 1) {
            for (int si : eo[i])
                s.erase(pos[si]);
        }
        dir1.v = { du.first, du.second };
        dir2.v = { dv.first, dv.second };
        for (int si : ei[i]) {
            pair<iter, bool> ires = s.insert(ss[si]);
            pos[si] = ires.first;
            assert(ires.second);
        }
        if (s.empty()) continue;
        pii p1 = *s.begin(), p2 = *next(s.begin());
        line l1 = { pv[p1.first], pv[p1.second] }; l1.v = l1.v - l1.p;
        line l2 = { pv[p2.first], pv[p2.second] }; l2.v = l2.v - l2.p;
        vec i11 = litsc(l1, dir1), i12 = litsc(l1, dir2);
        vec i21 = litsc(l2, dir1), i22 = litsc(l2, dir2);
        ans += (i21 ^ i22) - (i11 ^ i12);
    }

    cout << fixed << setprecision(10) << ans / 2 << endl;

    return 0;
}
