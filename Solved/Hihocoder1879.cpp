#include <bits/stdc++.h>
#define P 998244353
#define N 2005
using namespace std;
typedef long long ll;
typedef __int128 lll;

int add(int a, int b) { int r = a + b; return r < P ? r : r - P; }
int sub(int a, int b) { int r = a - b; return r < 0 ? r + P : r; }
int mul(ll a, ll b) { return a * b % P; }
int mod(ll a) { a %= P; return a < 0 ? a + P : a; }
int inv(int x) { return x == 1 ? 1 : mul(inv(P % x), P - P / x); }
const int inv3 = inv(3);

struct vec { ll x, y; int mx, my; };
vec operator-(vec v) { return { -v.x, -v.y, sub(0, v.mx), sub(0, v.my) }; }
vec operator+(vec v1, vec v2) { return { v1.x + v2.x, v1.y + v2.y, add(v1.mx, v2.mx), add(v1.my, v2.my) }; }
vec operator-(vec v1, vec v2) { return { v1.x - v2.x, v1.y - v2.y, sub(v1.mx, v2.mx), sub(v1.my, v2.my) }; }
lll operator*(vec v1, vec v2) { return (lll)v1.x * v2.x + (lll)v1.y * v2.y; }
lll operator^(vec v1, vec v2) { return (lll)v1.x * v2.y - (lll)v1.y * v2.x; }
lll dot(vec v0, vec v1, vec v2) { return (v1 - v0) * (v2 - v0); }
lll crx(vec v0, vec v1, vec v2) { return (v1 - v0) ^ (v2 - v0); }

vec pv[N], qv[N << 2], sv[N << 2];
int p[N << 2];

inline void gen(vec& v) {
    v.mx = mod(v.x);
    v.my = mod(v.y);
}

inline vec sum(int l, int r) { return sv[r] - sv[l - 1]; }
inline int area(vec v1, vec v2) { return sub(mul(v1.mx, v2.my), mul(v1.my, v2.mx)); }

int main(void) {
    #ifndef ONLINE_JUDGE
    freopen("1.in", "r", stdin);
    #endif // ONLINE_JUDGE

    int T; scanf("%d", &T);
    while(T--){
        int n; scanf("%d", &n);
        for (int i = 1; i <= n; ++i) {
            scanf("%lld%lld", &pv[i].x, &pv[i].y);
        }

        int sum1 = 0, sum2 = 0;
        for (int o = 1; o <= n; ++o) {
            vec c = pv[o];
            int m = 0;
            for (int i = 1; i <= n; ++i) {
                if (i == o) continue;
                qv[++m] = pv[i] - c; gen(qv[m]);
                qv[++m] = c - pv[i];
            }
            for (int i = 1; i <= m; ++i) p[i] = i;
            int w = partition(p + 1, p + m + 1, [&](int i) { return qv[i].y > 0 || (qv[i].y == 0 && qv[i].x > 0); }) - p;
            sort(p + 1, p + w, [&](int i, int j) { return (qv[i] ^ qv[j]) > 0; });
            sort(p + w, p + m + 1, [&](int i, int j) { return (qv[i] ^ qv[j]) > 0; });
            copy_n(qv + 1, m, qv + m + 1);
            copy_n(p + 1, m, p + m + 1);
            for (int i = 1; i <= m; ++i) p[m + i] += m;
            for (int i = 1; i <= 2 * m; ++i)
                sv[i] = sv[i - 1] + qv[p[i]];

            for (int l = 1, r = 1, r1, r2; l <= m; l++) {
                while ((qv[p[l]] ^ qv[p[r]]) == 0)
                    ++r;
                if (l == 1) r1 = r;
                while ((qv[p[l]] * qv[p[r1]]) > 0)
                    ++r1;
                if (l == 1) r2 = r1;
                while ((qv[p[l]] ^ qv[p[r2]]) > 0)
                    ++r2;
                sum1 = add(sum1, area(qv[p[l]], sum(r, r2 - 1)));
                sum2 = add(sum2, area(qv[p[l]], sum(r1, r2 - 1)));
            }
        }
        printf("%d\n", sub(mul(sum1, inv3), sum2));
    }
    return 0;
}
