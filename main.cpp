#include <ctime>
#include <cstdio>
#include <algorithm>
#include <ctime>
#include <iostream>
#include <queue>
#include <bitset>
#include <string>
#include <cstring>
#include <set>
#include <cmath>
#define double long
using namespace std;
struct point{
    long double x, y;
    point(long double x = 0, long double y= 0):x(x),y(y){}
};
point operator-(point a, point b) {
    return point(a.x - b.x, a.y - b.y);
}
double operator*(point a, point b) {
    return a.x * b.y - a.y * b.x;
}
double cross(point a, point b, point c) {
    return (b - a) * (c - a);
}
bool operator==(point a, point b) {
    return a.x == b.x && a.y == b.y;
}
int T, n, m;
point a[10000], b;
int l[10000], r[10000];
int id[10000];
vector<int> d, ans;
int main() {
    //freopen("1.in", "r", stdin);
    scanf("%d", &T);
    while (T --) {
        scanf("%d %d", &n, &m);
        for (int i = 1; i <= n ; i ++)
            scanf("%lld%lld", &a[i].x, &a[i].y);
        for (int i = 1; i <= m ; i ++)
            id[i] = i, id[i+m]=i+m, id[i+m + m]=i+m + m;
        for (int id= 1; id <= m ; id ++){
            scanf("%lld%lld", &b.x, &b.y);
            point c[2];
            int tot = 0;
            for (int i = 1; i <= n ; i ++)
                if (cross(b, a[i], a[(i - 2 + n) % n + 1]) *cross(b, a[i], a[i % n + 1]) > 0 && cross(b, a[i], a[i % n + 1]) < 0)
                    c[tot++] = a[i];

            for (int i = 1; i <= n ; i ++)
                if (cross(b, a[i], a[(i - 2 + n) % n + 1]) *cross(b, a[i], a[i % n + 1]) > 0 && cross(b, a[i], a[i % n + 1]) > 0)
                    c[tot++] = a[i];
            for (int i = 1; i <=n ; i ++) {
                if (a[i] == c[0]) {
                    l[id] = i;
                }
                if (a[i] == c[1])
                    r[id] = i;
            }
            if (l[id] > r[id])
                r[id] += n;
            l[id + m] = l[id] + n;
            r[id + m] = r[id] + n;
            l[id + m+m] = l[id] + n+n;
            r[id + m+m] = r[id] + n+n;
        }
        sort(id +1, id + m + m + 1,[](int x, int y){return l[x] < l[y];});
        ans.resize(0);
        for (int i = 1; i <= m + m; i ++)
        {
            d.resize(0);
            d.push_back(id[i]);
            int cnt = i + 1, mx = -1;
            while (r[d[d.size() - 1]] - l[d[0]] + 1 < n + 1)
            {
                while (cnt <= m + m && l[id[cnt]] <= r[d[d.size() - 1]]) {
                    if (mx == -1 ||r[id[cnt]] > r[mx])
                        mx = id[cnt];
                    cnt ++;
                }
                if (mx == -1 || r[mx] <= r[d[d.size() - 1]])
                    break;
                d.push_back(mx);
            }
            if (r[d[d.size() - 1]] - l[d[0]] + 1 >= n + 1 && (d.size() < ans.size() || !ans.size()) )
                ans = d;
        }
        if (!ans.size())
            printf("-1\n");
        else {
            printf("%d\n", ans.size());
            for (auto u:ans)
                if (u > m + m )
                    printf("%d ", u - m - m);
                else
                if (u > m)
                    printf("%d ", u - m);
                else
                    printf("%d ", u);
            printf("\n");
        }
    }
    return 0;
}