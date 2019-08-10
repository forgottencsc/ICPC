namespace ufs {

int f[N], s[N];
int x[N], y[N], c;

void clr(int n) {
    fill(f + 1, f + n + 1, 0);
    fill(s + 1, s + n + 1, 1);
}

int find(int x) {
    while (f[x]) x = f[x];
    return x;
}

bool join(int u, int v) {
    u = find(u); v = find(v);
    if (u == v) return false;
    if (s[u] > s[v]) swap(u, v);
    ++c; x[c] = u; y[c] = v;
    s[v] += s[u]; f[u] = v;
    return true;
}

void rollback(int w) {
    for (; c != w; --c) {
        int u = x[c], v = y[c];
        f[u] = 0; s[v] -= s[u];
    }
}

}