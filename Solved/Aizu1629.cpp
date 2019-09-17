#include <bits/stdc++.h>
#define N 10001
using namespace std;

typedef double dbl;
const dbl pi = acos(-1), eps = 1e-6;
struct vec { dbl x, y; };
inline bool operator<(vec v1, vec v2) { return v1.y == v2.y ? v1.x < v2.x : v1.y < v2.y; }
inline vec operator+(vec v1, vec v2) { return { v1.x + v2.x, v1.y + v2.y }; }
inline vec operator-(vec v1, vec v2) { return { v1.x - v2.x, v1.y - v2.y }; }
inline dbl operator*(vec v1, vec v2) { return v1.x * v2.x + v1.y * v2.y; }
inline dbl operator^(vec v1, vec v2) { return v1.x * v2.y - v1.y * v2.x; }
inline dbl crx(vec p0, vec p1, vec p2) { return (p1 - p0) ^ (p2 - p0); }

vec ps[N];
dbl w[N];
typedef pair<double, int> pdi;
pdi ep[N << 1]; int vis[N];
pdi p1[N], p2[N], q1[N], q2[N];
bool operator<(pdi p1, pdi p2) { return p1.first < p2.first - eps; }

int main(void) {
    int n, k;
    const dbl s3 = sqrt(3);
    const vec vl = { 1. / 2, s3 / 2 };
    const vec vr = { -1. / 2, s3 / 2 };
    while (scanf("%d", &n), n) {
        scanf("%d", &k);
        for (int i = 1; i <= n; ++i)
            scanf("%lf%lf", &ps[i].x, &ps[i].y);
        sort(ps + 1, ps + n + 1);
        for (int i = 1; i <= n; ++i) {
            p1[i] = { ps[i] * vec{ sqrt(3) / 2,  -1. / 2 }, i };
            p2[i] = { ps[i] * vec{ sqrt(3) / 2,  1. / 2 }, i };
        }
        sort(p1 + 1, p1 + n + 1);
        sort(p2 + 1, p2 + n + 1);
        for (int i = 1; i <= n; ++i) w[i] = ps[i].y;
        int m = unique(w + 1, w + n + 1) - w - 1;
        dbl ans = DBL_MAX;
        int c = 2 * n;
        for (int i = 1; i <= m; ++i) {
            int c1 = remove_if(p1 + 1, p1 + c / 2 + 1, [&](pdi p) { return ps[p.second].y < w[i]; }) - p1 - 1;
            int c2 = remove_if(p2 + 1, p2 + c / 2 + 1, [&](pdi p) { return ps[p.second].y < w[i]; }) - p2 - 1;
            for (int j = 1; j <= c1; ++j) {
                int j1 = p1[j].second, j2 = p2[j].second;
                q1[j] = { (w[i] - ps[j1].y) / s3 + ps[j1].x, -j1 };
                q2[j] = { -(w[i] - ps[j2].y) / s3 + ps[j2].x, j2 };
                vis[j1] = vis[j2] = 0;
            }
            if (c / 2 < n - k) break;
            c = c1 + c2;
            merge(q1 + 1, q1 + c1 + 1, q2 + 1, q2 + c2 + 1, ep + 1);
            int cnt = 0;
            for (int l = 1, r = 0; l <= c; ++l) {
                vec p = { ep[l].first, w[i] };
                while (cnt < n - k && r < c) {
                    ++r;
                    int id = ep[r].second;
                    if (id > 0 && !vis[id] && (vl ^ (ps[id] - p)) <= eps) {
                        vis[id] = 1;
                        cnt++;
                    }
                }
                if (cnt >= n - k)
                    ans = min(ans, (dbl)(ep[r].first - ep[l].first));
                else break;
                int id = ep[l].second;
                if (id < 0) {
                    if (vis[-id] == 1) {
                        vis[-id] = 0;
                        cnt--;
                    }
                    else {
                        vis[-id] = -1;
                    }
                }
            }
        }
        printf("%.7f\n", 3 * ans);
    }

    return 0;
}
