int sa[N], rk[N], sh[N];
int st[N][21], lg2[N];
int sw1[N], sw2[N], sc[N];
void build_sa(const char* s) {
    int n = strlen(s + 1), m = 128, *x = sw1, *y = sw2;
    memset(sc + 1, 0, m << 2);
    for (int i = 1; i <= n; ++i) sc[x[i] = s[i]]++;
    for (int i = 1; i <= m; ++i) sc[i] += sc[i - 1];
    for (int i = 1; i <= n; ++i) sa[sc[x[i]]--] = i;
    for (int k = 1; k <= n; k <<= 1) {
        int p = 0;
        for (int i = n - k + 1; i <= n; ++i) y[++p] = i;
        for (int i = 1; i <= n; ++i) if (sa[i] > k) y[++p] = sa[i] - k;
        memset(sc + 1, 0, m << 2);
        for (int i = 1; i <= n; ++i) sc[x[i]]++;
        for (int i = 1; i <= m; ++i) sc[i] += sc[i - 1];
        for (int i = n; i >= 1; --i) sa[sc[x[y[i]]]--] = y[i];
        swap(x, y); p = x[sa[1]] = 1;
        for (int i = 2; i <= n; ++i)
            x[sa[i]] = (y[sa[i] + k] == y[sa[i - 1] + k]
            && y[sa[i]] == y[sa[i - 1]]) ? p: ++p;
        m = p; if (m == n) break;
    }
    for (int i = 1; i <= n; ++i) rk[sa[i]] = i;
    for (int i = 1, k = 0; i <= n; ++i) {
        if (rk[i] == 1) continue; if (k) --k;
        int j = sa[rk[i] - 1];
        while (j + k <= n && i + k <= n && s[i + k] == s[j + k])
            ++k;
        sh[rk[i]] = k;
    }
    for (int i = 2; i <= n; ++i) lg2[i] = lg2[i >> 1] + 1;
    for (int i = 1; i <= n; ++i) st[i][0] = sh[i];
    for (int j = 1; (1 << j) <= n; ++j)
        for (int i = 1; i + (1 << j) <= n + 1; ++i)
            st[i][j] = min(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
}

int lcp(int u, int v) {
    int l = rk[u], r = rk[v];
    if (l > r) swap(l, r); l++; r++;
    int k = lg2[r - l];
    return min(st[l][k], st[r - (1 << k)][k]);
}

int getl(int p, int w) {
    int l = 1, r = rk[p] - 1;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (lcp(p, sa[mid]) < w)
            l = mid + 1;
        else
            r = mid - 1;
    }
    return l;
}

int getr(int p, int w) {
    int l = rk[p] + 1, r = n;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (lcp(p, sa[mid]) < w)
            r = mid - 1;
        else
            l = mid + 1;
    }
    return r;
}