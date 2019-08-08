#include <bits/stdc++.h>
#define M(x) (((x) + P) % P)
#define N 1<<18
using namespace std;
typedef long long ll;

ll P;

ll s1[N], s2[N], s3[N], s4[N];

void push_up(int p) {
    s1[p] = M(s1[p << 1] + s1[p << 1 | 1]);
    s2[p] = M(s2[p << 1] + s2[p << 1 | 1]);
    s3[p] = M(s3[p << 1] + s3[p << 1 | 1]);
    s4[p] = M(s4[p << 1] + s4[p << 1 | 1]);
}

void modify(int x, int v, int p, int lb, int rb) {
    if (lb + 1 == rb) {
        s1[p] = M(M(s1[p] + v));
        s2[p] = M(s1[p] * s1[p]);
        s3[p] = M(s1[p] * s2[p]);
        s4[p] = M(s2[p] * s2[p]);
    }
    else {
        int mid = (lb + rb) >> 1;
        if (x < mid) modify(x, v, p << 1, lb, mid);
        else modify(x, v, p << 1 | 1, mid, rb);
        push_up(p);
    }
}

ll r1, r2, r3, r4;
void query(int l, int r, int p, int lb, int rb){
    if (l <= lb && rb <= r) {
        r1 = M(r1 + s1[p]);
        r2 = M(r2 + s2[p]);
        r3 = M(r3 + s3[p]);
        r4 = M(r4 + s4[p]);
    }
    else {
        int mid = (lb + rb) >> 1;
        if (l < mid) query(l, r, p << 1, lb, mid);
        if (r > mid) query(l, r, p << 1 | 1, mid, rb);
    }
}

int a[N];
void build(int p, int lb, int rb) {
    if (lb + 1 == rb) {
        s1[p] = M(M(a[lb]));
        s2[p] = M(s1[p] * s1[p]);
        s3[p] = M(s1[p] * s2[p]);
        s4[p] = M(s2[p] * s2[p]);
    }
    else {
        int mid = (lb + rb) >> 1;
        build(p << 1, lb, mid);
        build(p << 1 | 1, mid, rb);
        push_up(p);
    }
}

ll i2, i6, i24;
ll inv(ll x) { return x == 1 ? 1 : M(inv(P % x) * (P - P / x)); }

int main(void){
    ios::sync_with_stdio(0); cin.tie(0);
    #ifndef ONLINE_JUDGE
    ifstream cin("1.in");
    #endif // ONLINE_JUDGE
    int n, q; cin >> n >> q >> P;
    i2 = inv(2);
    i6 = inv(6);
    i24 = inv(24);
    for (int i = 1; i <= n; ++i)
        cin >> a[i];
    build(1, 1, n + 1);
    while(q--) {
        char b[2]; cin >> b;
        if (b[0] == 'C') {
            int l, r, k; cin >> l >> r >> k;
            r1 = r2 = r3 = r4 = 0;
            query(l, r + 1, 1, 1, n + 1);
            ll t[5] = {
                1,
                r1,
                M(M(M(r1 * r1) - r2) * i2),
                M(M(M(M(M(r1 * r1) * r1) - M(3 * M(r1 * r2))) + M(2 * r3)) * i6),
                M(M(M(M(M(r1*r1)*M(r1*r1))-M(M(6*r2)*M(r1*r1)))+M(3*M(r2*r2))+M(M(8*M(r3*r1))-M(6*r4)))*i24)
            };
            for (int i = 0; i <= k; ++i)
                cout << t[i] << " \n"[i == k];
        }
        else {
            int x, v;
            cin >> x >> v;
            modify(x, v, 1, 1, n + 1);
        }
    }
    cout.flush();
    return 0;
}


//#include <bits/stdc++.h>
//#define N 200005
//using namespace std;
//
//int g[N][26], f[N], w[N], nc;
//int gn() {
//    int p = nc++; f[p] = w[p] = 0;
//    memset(g[p], 0, sizeof(g[p]));
//    return p;
//}
//
//void clr() { nc = 0; gn(); }
//
//void ins(const string& s) {
//    int p = 0;
//    for (char ch : s) {
//        int o = ch - 'a';
//        if (!g[p][o]) g[p][o] = gn();
//        p = g[p][o];
//    }
//    w[p]++;
//}
//
//void build() {
//    queue<int> q;
//    for (int o = 0; o != 26; ++o)
//        if (g[0][o]) q.push(g[0][o]);
//    while (!q.empty()) {
//        int u = q.front(); q.pop();
//        w[u] += w[f[u]];
//        for (int o = 0; o != 26; ++o) {
//            int& v = g[u][o];
//            if (!v) v = g[f[u]][o];
//            else f[v] = g[f[u]][o], q.push(v);
//        }
//    }
//}
//
//char t[N]; int ans1[N], ans2[N];
//void match(int* ans) {
//    int p = 0;
//    for (int i = 0; t[i]; ++i) {
//        int o = t[i] - 'a';
//        p = g[p][o];
//        ans[i] += w[p];
//    }
//}
//
//int main() {
//    ios::sync_with_stdio(0);
//    #ifndef ONLINE_JUDGE
//    ifstream cin("1.in");
//    #endif // ONLINE_JUDGE
//    cin >> t; int m = strlen(t);
//    int n; cin >> n;
//    vector<string> sv(n);
//    for (int i = 0; i != n; ++i)
//        cin >> sv[i];
//    clr();
//    for (int i = 0; i != n; ++i)
//        ins(sv[i]);
//    build();
//    match(ans1);
//    clr();
//    reverse(t, t + m);
//    for (int i = 0; i != n; ++i) {
//        reverse(sv[i].begin(), sv[i].end());
//        ins(sv[i]);
//    }
//    build();
//    match(ans2);
//    typedef long long ll;
//    ll ans = 0;
//    for (int i = 0; i != m - 1; ++i)
//        ans += 1ll * ans1[i] * ans2[m - i - 2];
//    cout << ans << endl;
//    return 0;
//}