//  blocks
int bi[N], bl[M], br[M], bs, bc;
void block_init() {
    bs = sqrt(n); bc = 1; bl[1] = 1;
    for (int i = 1; i <= n; ++i) {
        if (i - bl[bc] == bs) {
            br[bc++] = i - 1;
            bl[bc] = i;
        }
        bi[i] = bc;
    }
    br[bc] = n;
}

//  Union-Find Set, Rollback supported, O(logn)
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
    for (; c != w; --c)
        f[x[c]] = 0, s[y[c]] -= s[x[c]];
}

}

//  Sparse Table
int lg2[N], st[18][N];
void build() {
    for (int i = 2; i <= n; ++i) lg2[i] = lg2[i >> 1] + 1;
    for (int i = 1; i <= n; ++i) st[0][i] = a[i];
    for (int j = 1; (1 << j) <= n; ++j)
        for (int i = 1; i + (1 << j) - 1 <= n; ++i)
            st[j][i] = max(st[j - 1][i], st[j - 1][i + (1 << j - 1)]);
}

int query(int l, int r) {
    int w = lg2[r - l];
    return max(st[w][l], st[w][r - (1 << w)]);
}
