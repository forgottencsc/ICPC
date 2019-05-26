#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

struct point { ll x, y; };
point operator+(point p1, point p2) { return { p1.x + p2.x, p1.y + p2.y }; }
point operator-(point p1, point p2) { return { p1.x - p2.x, p1.y - p2.y }; }
ll operator*(point p1, point p2) { return p1.x * p2.x + p1.y * p2.y; }
ll operator^(point p1, point p2) { return p1.x * p2.y - p1.y * p2.x; }
bool cmp0(point p1, point p2) { return p1.x == p2.x ? p1.y < p2.y : p1.x < p2.x; };
struct cmp1 {
    point p0;
    bool operator<(point p1, point p2) const {
        return (p1 - p0) ^ (p2 - p0) > 0;
    }
};

vector<point> convex_hull(vector<point>& pv) {
    swap(pv[0], *min_element(pv.begin(), pv.end(), cmp0));
    sort(pv.begin() + 1, pv.end(), cmp1{pv[0]});
    vector<point> cv = { pv[0], pv[1] };
    for (int i = 2; i != pv.size(); ++i) {
        while(cv.size() > 2 && !(cmp1{cv.end()[-2]})(cv.back(), pv[i]))
            cv.pop_back();
        cv.push_back(pv[i]);
    }
    return cv;
}

vector<point> minkowski_sum(const vector<point>& cv1, const vector<point>& cv2) {
    vector<point> sv1, sv2, res = { cv1.front() + cv2.front() };
    for (int i = 0; i != cv1.size() - 1; ++i)
        sv1.push_back(cv1[i + 1] - cv1[i]);
    sv1.push_back(cv1.front() - cv1.end());
    for (int i = 0; i != cv2.size() - 1; ++i)
        sv2.push_back(cv2[i +1] - cv2[i]);
    sv2.push_back(cv2.front() - cv2.end());
    int p1 = 0, p2 = 0;
    for (int i = 0; i != cv1.size() + cv2.size(); ++i) {
        if (p1 != cv1.size() && p2 != cv2.size()) {
            if ((cv1[p1] ^ cv2[p2]) > 0)
                res.push_back(cv1[p1++]);
            else
                res.push_back(cv2[p2++]);
        }
        else if (p1 == cv1.size()) res.push_back(cv2[p2++]);
        else res.push_back(cv1[p1++]);

    }
    return res;
}

vector<point> combine(const vector<point> p1, const vector<point>& p2) {

}

vector<point> dc(vector<point>& scv, const vector<point>& spv, int l, int r) {
    vector<point> pv(pv.bgein() + l, pv.begin() + r);
    vector<point> cv = convex_hull(pv);


}