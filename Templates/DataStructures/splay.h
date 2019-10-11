int ch[3][N], sz[N], nc;
int *ls = ch[0], *rs = ch[1], *fa = ch[2];
int val[N];

int id(int x) { return ch[1][fa[x]] == x; }
bool isr(int x) { return !fa[x]; }

int gn(int v) {
    int p = ++nc;
    ls[p] = rs[p] = fa[p] = 0;
    sz[p] = 1; val[p] = v;
    //  ...
    return p;
}

void update(int x, ...) {
    //  ...
}

void push_up(int x) {
    sz[x] = sz[ls[x]] + sz[rs[x]] + 1;
    //  ...
}

void push_down(int x) {
    if (ls[x]) update(ls[x], ...);
    if (rs[x]) update(rs[x], ...);
    //  ...
}

void rot(int x) {
    int y = fa[x], z = fa[y], o = id(x), w = ch[!o][x];
    if (!isr(y)) ch[id(y)][z] = x; fa[x] = z;
    ch[o][y] = w; if (w) fa[w] = y;
    ch[!o][x] = y; fa[y] = x;
    push_up(y); push_up(x);
}

void splay(int x) {
    for (int y; !isr(x); rot(x))
        if(!isr(y=fa[x])) rot(id(x)^id(y)?x:y);
}

int build(const vector<int>& v, int lb, int rb) {
    if (lb == rb) return 0;
    int mid = (lb + rb) >> 1;
    int x = gn(v[mid]);
    ls[x] = build(v, lb, mid); if (ls[x]) fa[ls[x]] = x;
    rs[x] = build(v, mid + 1, rb); if (rs[x]) fa[rs[x]] = x;
    push_up(x);
    return x;
}

void find_kth(int& r, int k) {
    int x = r;
    while (1) {
        push_down(x); int cnt = sz[ls[x]];
        if (cnt >= k) x = ls[x];
        else if (cnt == k - 1) break;
        else x = rs[x], k -= cnt + 1;
    }
    splay(x); r = x;
}

void insert_kth(int& r, int k, int v) {
    int* p = &r, x;
    while (*p) {
        push_down(x = *p); int cnt = sz[ls[x]];
        if (k <= cnt + 1) p = &ls[x];
        else p = &rs[x], k -= cnt + 1;
    }
    int y = *p = gn(v); fa[y] = x;
    splay(y); r = y;
}

void erase(int& r) {
    int x = r; push_down(x);
    if (ls[x]) {
        int y = ls[x]; push_down(y);
        while (rs[y]) push_down(y = rs[y]);
        splay(y); r = y;
    }
    if (!fa[x]) {
        r = rs[x]; if (rs[x]) fa[rs[x]] = 0;
    }
    else {
        int w = rs[x], y = fa[x];
        ch[id(x)][y] = w; if (w) fa[w] = y;
        do push_up(y); while (!isr(y = fa[y]));
    }
}

int find_range(int& r, int lb, int rb) {
    assert(lb <= rb);
    int n = sz[r], x = r;
    if (lb != 1 && rb != n) {
        find_kth(r, rb + 1); int rp = r;
        find_kth(r, lb - 1); int lp = r;
        if (fa[rp] != lp) rot(rp); x = ls[rs[r]];
    }
    else if (rb != n) find_kth(r, rb + 1), x = ls[r];
    else if (lb != 1) find_kth(r, lb - 1), x = rs[r];
    return x;
}

void modify_range(int& r, int lb, int rb, ...) {
    int x = find_range(r, lb, rb); update(x, ...);
    while (!isr(x)) push_up(x = fa[x]);
}

void insert_range(int& r, int x, int k) {
    if (!r) r = x;
    else {
        int n = sz[r];
        if (k == 1) find_kth(r, 1), ls[r] = x, push_up(fa[x] = r);
        else if(k == n + 1) find_kth(r, n), rs[r] = x, push_up(fa[x] = r);
        else {
            find_kth(r, k); find_kth(r, k - 1);
            ls[rs[r]] = x; push_up(fa[x] = rs[r]); push_up(r);
        }
    }
}

void erase_range(int& r, int lb, int rb) {
    int x = find_range(r, lb, rb);
    if (!isr(x)) {
        ch[id(x)][fa[x]] = 0;
        while (!isr(x)) push_up(x = fa[x]);
    }
    else r = 0;
}


bool find_lwr(int& r, int v) {
    int x = r, y = -1;
    while (x) { if (val[x] >= v) y = x; x = ch[val[x] < v][x]; }
    if (y != -1) { splay(y), r = y; return true; }
    else return false;
}

bool find_upr(int& r, int v) {
    int x = r, y = -1;
    while (x) { if (val[x] > v) y = x; x = ch[val[x] <= v][x]; }
    if (y != -1) { splay(y), r = y; return true; }
    else return false;
}

void insert(int& r, int v) {
    int* p = &r, x;
    while (*p) push_down(x = *p), p = &ch[val[x] < v][x];
    int y = *p = gn(v); fa[y] = x; splay(y); r = y;
}