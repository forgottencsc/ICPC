
char s[N]; int n;
int sa[N], rk[N], sc[N], sv[2][N];
void cmp(int i, int j, int k) {
    return y[i + k] == y[j + k]
            && y[i] == y[j];
}
void build_sa(int m = 26) {
    int* x = sv[0], *y = sv[1];
    for (int i = 1; i <= m; ++i) x[i] = 0;
    for (int i = 1; i <= n; ++i) c[x[i] = s[i] - 'a' + 1]++;
    for (int i = 1; i <= m; ++i) c[i] += c[i - 1];
    for (int i = 1; i <= n; ++i) sa[c[x[i]]--] = i;
    for (int k = 1; (1 << k) < n; k <<= 1) {
        int p = 0;
        for (int i = n - k + 1; i <= n; ++i) y[++p] = i;
        for (int i = 1; i <= n; ++i) if (sa[i] > k) y[++p] = sa[i] - k;
        for (int i = 1; i <= m; ++i) c[i] = 0;
        for (int i = 1; i <= n; ++i) c[x[i]]++;
        for (int i = 1; i <= m; ++i) c[i] += c[i - 1];
        for (int i = 1; i <= n; ++i) sa[c[x[y[i]]]--] = i;
        swap(x, y); p = x[sa[1]] = 1;
        for (int i = 2; i <= n; ++i)
            x[sa[i]] = cmp(sa[i], sa[i - 1], k) ? p : ++p;
        if (p == n) break; else m = p;
    }
}