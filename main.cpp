#include <bits/stdc++.h>
#define W 20
#define N 1<<20
#define P 1000000007
using namespace std;

typedef long long ll;

inline int add(int a, int b) { int r = a + b; return r < P ? r : r - P; }
inline int sub(int a, int b) { int r = a - b; return r < 0 ? r + P : r; }
inline int mul(ll a, ll b) { ll r = a * b; return r % P; }

void fzt(int* f, int w) {
    for (int i = 0; i != w; ++i)
        for (int j = 0; j != (1 << w); ++j)
            if (j & (1 << i)) f[j] = add(f[j], f[j ^ (1 << i)]);
}

void fmt(int* f, int w) {
    for (int i = 0; i != w; ++i)
        for (int j = 0; j != (1 << w); ++j)
            if (j & (1 << i)) f[j] = sub(f[j], f[j ^ (1 << i)]);
}

void ssconv(int* f, int* g, int* h, int w) {
    static int pc[N], fi[W+1][N], gi[W+1][N], hi[W+1][N];
    //  Initialize pc && fi, gi, hi
    for (int i = 1; i != 1 << w; ++i)
        pc[i] = pc[i >> 1] + (i & 1);
    for (int i = 0; i <= w; ++i) {
        fill_n(fi[i], 1 << w, 0);
        fill_n(gi[i], 1 << w, 0);
        fill_n(hi[i], 1 << w, 0);
    }
    for (int i = 0; i != 1 << w; ++i) {
        fi[pc[i]][i] = f[i];
        gi[pc[i]][i] = g[i];
    }
    for (int i = 0; i <= w; ++i)
        fzt(fi[i], w), fzt(gi[i], w);
    for (int i = 0; i <= w; ++i)
        for (int j = 0; j <= i; ++j)
            for (int k = 0; k != 1 << w; ++k)
                hi[i][k] = add(hi[i][k], mul(fi[j][k], gi[i - j][k]));
    for (int i = 0; i <= w; ++i)
        fmt(hi[i], w);
    for (int i = 0; i != 1 << w; ++i)
        h[i] = hi[pc[i]][i];
}

void ssconv0(int* f, int* g, int* h, int w) {
    for (int i = 0; i != 1 << w; ++i) {
        h[i] = mul(f[0], g[i]);
        for (int j = i; j; j = i & (j - 1))
            h[i] = add(h[i], mul(f[j], g[i ^ j]));
    }
}

int f[N], g[N], h1[N], h2[N];

int main(void) {
    ios::sync_with_stdio(0); cin.tie(0);
    #ifndef ONLINE_JUDGE
    ifstream cin("1.in");
    #endif // ONLINE_JUDGE

    mt19937_64 mt(time(0));
    uniform_int_distribution<int> uid(0, P - 1);
    auto gen = bind(uid, ref(mt));
    int w = 3, n = 1 << w;
    generate_n(f, n, gen);
    generate_n(g, n, gen);

    for (int i = 0; i != n; ++i)
        cout << f[i] << " \n"[i == n - 1];

    for (int i = 0; i != n; ++i)
        cout << g[i] << " \n"[i == n - 1];

    ssconv0(f, g, h2, w);
    ssconv(f, g, h1, w);

    for (int i = 0; i != n; ++i)
        cout << h1[i] << " \n"[i == n - 1];

    for (int i = 0; i != n; ++i)
        cout << h2[i] << " \n"[i == n - 1];


    return 0;
}