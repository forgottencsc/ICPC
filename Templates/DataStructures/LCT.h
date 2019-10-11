int ch[3][N], sz[N], nc;
int* ls = ch[0], *rs = ch[1], *fa = ch[2];
int val[N], sv[N], rev[N];

inline int id(int x) { return ch[1][fa[x]] == x; }
inline bool isr(int x) {
    return ch[id(x)][fa[x]] != x;
}

int gn(int v) {
    int x = ++nc;
    ls[x] = rs[x] = fa[x] = 0;
    sz[x] = 1; val[x] = v;
    sv[x] = v; rev[x] = 0;
    return x;
}

inline void update(int x, int v) {
    if (v) {
        swap(ls[x], rs[x]);
        rev[x] ^= 1;
    }
}

inline void push_up(int x) {
    sz[x] = sz[ls[x]] + sz[rs[x]] + 1;
    sv[x] = sv[ls[x]] ^ val[x] ^ sv[rs[x]];
}

inline void push_down(int x) {
    if (ls[x]) update(ls[x], rev[x]);
    if (rs[x]) update(rs[x], rev[x]);
    rev[x] = 0;
}

inline void rot(int x) {
    if (isr(x))
        assert(false);
    int y = fa[x], z = fa[y], o = id(x), w = ch[!o][x];
    if (!isr(y)) ch[id(y)][z] = x; fa[x] = z;
    ch[o][y] = w; if (w) fa[w] = y;
    ch[!o][x] = y; fa[y] = x;
    push_up(y); push_up(x);
}

void push_tag(int x) {
    static int s[N];
    static int t; s[++t] = x;
    while (!isr(x)) s[++t] = x = fa[x];
    while (t) push_down(s[t--]);
}

void splay(int x) {
    push_tag(x);
    for (int y; !isr(x); rot(x))
        if (!isr(y = fa[x])) rot(id(x)^id(y)?x:y);
}

void access(int x) {
    for (int y = 0; x; x = fa[y = x])
        splay(x), rs[x] = y, push_up(x);
}

int find_root(int x) {
    access(x); splay(x); push_down(x);
    while (ls[x]) push_down(x = ls[x]);
    splay(x); return x;
}

void make_root(int x) {
    access(x); splay(x);
    update(x, 1);
}

void split(int x, int y) {
    make_root(x); access(y); splay(y);
}

bool link(int x, int y) {
    make_root(x);
    if (find_root(y) == x) return false;
    fa[x] = y; return true;
}

bool cut(int x, int y) {
    make_root(x);
    if (find_root(y) != x || fa[y] != x || ls[y]) return false;
    fa[y] = rs[x] = 0; push_up(x); return true;
}