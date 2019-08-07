#include <bits/stdc++.h>
using namespace std;
typedef double dbl;
const dbl pi = acos(-1), eps = 1e-8;
struct vec { dbl x, y; };
vec operator+(vec v1, vec v2) { return { v1.x + v2.x, v1.y + v2.y }; }
vec operator-(vec v1, vec v2) { return { v1.x - v2.x, v1.y - v2.y }; }
dbl operator*(vec v1, vec v2) { return v1.x * v2.x + v1.y * v2.y; }
dbl operator^(vec v1, vec v2) { return v1.x * v2.y - v1.y * v2.x; }
vec operator*(dbl k, vec v) { return { k * v.x, k * v.y }; }
bool operator<(vec v1, vec v2) { return v1.x==v2.x?v1.y<v2.y:v1.x<v2.x; }
dbl crx(vec v0, vec v1, vec v2) { return (v1 - v0) ^ (v2 - v0); }
dbl len(vec v) { return hypot(v.x, v.y); }
dbl arg(vec v) { return atan2(v.y, v.x); }

vector<vec> convex_hull(vector<vec>& ps) {
    swap(pv[0], *min_element(pv.begin(), pv.end()));
    sort(pv.begin() + 1, pv.end(), [&](vec v1, vec v2) {
        v1 = v1 - pv[0]; v2 = v2 - pv[0];
        return (v1 ^ v2) == 0 ? v1 * v1 < v2 * v2 : (v1 ^ v2) > 0;
    });
    vector<vec> res = { ps[0], ps[1] };
    for (int i = 2; i != ps.size(); ++i) {
        while (res.size() >= 2 &&
               crx(res.end()[-2],res.back(),ps[i]) <= 0)
                res.pop_back();
        res.push_back(ps[i]);
    }
    return res;
}

vector<vec> minkovski_sum(const vector<vec>& v1, const vector<vec>& v2) {
    const int n1 = v1.size(), n2 = v2.size();
    if (!n1) return v2; if (!n2) return v1;
    vector<vec> d1(n1), d2(n2);
    for (int i = 0; i != n1; ++i) d1[i] = v1[(i + 1) % n1] - v1[i];
    for (int i = 0; i != n2; ++i) d2[i] = v2[(i + 1) % n2] - v2[i];
    d2[n2 - 1] = v2[0] - v2[n2 - 1];
    int p = 0, q = 0; res.push_back(v1[0] + v2[0]);
    while (p != n1 && q != n2) {
        if ((d1[p] ^ d2[q]) > 0) res.push_back(res.back() + d1[p++]);
        else res.push_back(res.back() + d2[q++]);
    }
    for (; p != n1; ++p) res.push_back(res.back() + d1[p]);
    for (; q != n2; ++q) res.push_back(res.back() + d2[q]);
    res.pop_back();
    return res;
}
