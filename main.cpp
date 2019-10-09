#include <bits/stdc++.h>
#define N 200006
using namespace std;
int ch[3][N], nc; int rec = 0;
int *ls = ch[0], *rs = ch[1], *fa = ch[2];
int val[N], tag[N], tag2[N], ans[N];

inline int gn(int v) {
    int p;
    if (rec) p = rec;
    else p = ++nc;
    ls[p] = rs[p] = fa[p] = 0;
    val[p] = v;
    return p;
}

inline void update(int x, int v, int v2) {
    tag[x] += v;
    val[x] += v;
    tag2[x] += v2;
    ans[x] += v2;
}

inline void push_down(int x) {
    if (tag[x] || tag2[x]) {
        if (ls[x]) update(ls[x], tag[x], tag2[x]);
        if (rs[x]) update(rs[x], tag[x], tag2[x]);
        tag[x] = tag2[x] = 0;
    }
}

inline bool isr(int x) { return !fa[x]; }
inline int id(int x) { return ch[1][fa[x]] == x; }

inline void rot(int x) {
    int y = fa[x], z = fa[y], o = id(x), w = ch[!o][x];
    fa[x] = z; if (!isr(x)) ch[id(y)][z] = x;
    ch[o][y] = w; if (w) fa[w] = y;
    ch[!o][x] = y; fa[y] = x;
}

//void push_tag(int x) {
//    static int s[100], t = 0;
//    s[++t] = x; while (!isr(x)) s[++t] = (x = fa[x]);
//    while (t) push_down(s[t--]);
//}

void splay(int x) {
    for (int y; !isr(x); rot(x)) if (!isr(y = fa[x])) rot(id(x)^id(y)?x:y);
}

void find_lwr(int& r, int v) {
    int x = r, y = -1;
    while (x) {
        push_down(x);
        if (val[x] >= v) y = x;
        x = ch[val[x] < v][x];
    }
    if (y != -1) splay(y), r = y;
}

void ins(int& r, int v) {
    int* p = &r, x;
    while (*p) push_down(x = *p), p = &ch[val[x] < v][x];
    int y = *p = gn(v); fa[y] = x;
    splay(y); r = y;
}

int split(int& r, int v) {
    find_lwr(r, v);
    if (val[r] < v)
        return 0;
    else {
        int x = ls[r], y = r;
        fa[x] = ls[r] = 0;
        r = x;
        return y;
    }
}

void merge(int& r, int r2) {
    if (!r) r = r2;
    else {
        int x = r; while (rs[x]) x = rs[x];
        splay(x); r = x;
        rs[r] = r2; fa[r2] = r;
    }
}

void merge2(int& r, int r2) {
    if (!r2) return;
    push_down(r2);
    if (ls[r2]) merge2(r, ls[r2]);
    if (rs[r2]) merge2(r, rs[r2]);
    rec = r2;
    int v = val[r2];
    ins(r, v);
}

void push_all(int x) {
    if (!x) return;
    push_down(x);
    push_all(ls[x]);
    push_all(rs[x]);
}

int main(void) {
	ios::sync_with_stdio(0); cin.tie(0);
#ifndef ONLINE_JUDGE
	ifstream cin("1.in");
#endif
    typedef pair<int, int> pii;
    int n, q; cin >> n;
    vector<pii> v(n);
    for (int i = 0; i != n; ++i)
        cin >> v[i].second >> v[i].first;
    sort(v.begin(), v.end(), [](pii p1, pii p2) { return p1.first == p2.first ? p1.second < p2.second : p1.first > p2.first; });
    cin >> q;

    int r = 0;
    for (int i = 1; i <= q; ++i) {
        int m; cin >> m;
        ins(r, m);
    }

    for (int i = 0; i != n; ++i) {
        int c = v[i].second, q = v[i].first;
        int r2 = split(r, c);
        if (r2) {
            update(r2, -c, 1);
            int r3 = split(r2, c);
            merge(r, r3);
            merge2(r, r2);
        }
    }

//    vector<int> w(q + 1);
//    for (int i = 1; i <= q; ++i)
//        w[idd[i]] = ans[i];

    push_all(r);
    for (int i = 1; i <= q; ++i)
        cout << ans[i] << " \n"[i == q];

	return 0;
}
