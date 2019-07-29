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
        while (crx(res.end()[-2],res.back(),ps[i]) <= 0) res.pop_back();
        res.push_back(ps[i]);
    }
    return res;
}

vector<vec> combine(const vector<vec>& c1, const vector<vec>& c2) {
    const int n1 = c1.size(), n2 = c2.size();
    vector<vec> res = { min(c1[0], c2[0]) };
    int p0 = n1 - 1, p1 = 0, p2;
    int q0 = n2 - 1, q1 = 0, q2;
    do {
        p2 = (p1 + 1) % n1; q2 = (q1 + 1) % n2;
        vec v1 = c1[p1], v2 = c2[p2];
        if (crx(v1, v2, c1[p0]) > 0 && crx(v1, v2, c1[p2]) > 0
         && crx(v1, v2, c2[q0]) > 0 && crx(v1, v2, c2[q2]) > 0)
            res.push_back(v2);
        dbl r = (c1[p2] - c1[p1]) ^ (c2[q2] - c2[q1]);
        if (r <= 0) p0 = p1, p1 = p2;
        if (r >= 0) q0 = q1, q1 = q2;
    } while (p0 || q0);
}

vector<vec> minkovski_sum(const vector<vec>& c1, const vector<vec>& c2) {
    int n1 = c1.size(), n2 = c2.size();
    vector<vec> res = { c1[0] + c2[0] };
    int p1 = 0, p2 = 0;
    while (p1 != n1 || p2 != n2) {
        vec v1, v2;
        if (p1 != n1) v1 = (c1[(p1 == n1 - 1 ? 0 : p1)] - c1[p1]);
        if (p2 != n2) v2 = (c2[(p2 == n2 - 1 ? 0 : p2)] - c2[p2]);
        if (p1 == n1) res.push_back(v2), p2++;
        if (p2 == n2) res.push_back(v1), p1++;
        if (p1 != n1 && p2 != n2) {
            if ((v1 ^ v2) >= 0) res.push_back(v1), p1++;
            else res.push_back(v2), p2++;
        }
    }
    for (int i = 1; i != n1 + n2; ++i)res[i] = res[i] + res[i - 1];
    return res;
}

vector<vec> combine(const vector<vec>& c1, const vector<vec>& c2) {
    int n1 = c1.size(), n2 = c2.size();
    vector<vec> res;
    int p1 = 0, p2 = max_element(c2.begin(), c2.end(), cvh_cmp1()) - c2.begin();

}
