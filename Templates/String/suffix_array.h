
char s[N]; int n;
int sa[N], rk[N], sc[N], sv[2][N];
void build_sa(int m = 256) {
    int* x = sv[0], *y = sv[1];
    for (int i = 1; i <= m; ++i) sc[i] = 0;
    for (int i = 1; i <= n; ++i) sc[x[i] = s[i]]++;
    for (int i = 1; i <= m; ++i) sc[i] += sc[i - 1];
    for (int i = 1; i <= n; ++i) sa[sc[x[i]]--] = i;
    for (int k = 1; k <= n; k <<= 1) {
        int p = 0;
        for (int i = n - k + 1; i <= n; ++i) y[++p] = i;
        for (int i = 1; i <= n; ++i) if (sa[i] > k) y[++p] = sa[i] - k;
        for (int i = 1; i <= m; ++i) sc[i] = 0;
        for (int i = 1; i <= n; ++i) sc[x[i]]++;
        for (int i = 1; i <= m; ++i) sc[i] += sc[i - 1];
        for (int i = n; i >= 1; --i) sa[sc[x[y[i]]]--] = y[i];
        swap(x, y); p = x[sa[1]] = 1;
        for (int i = 2; i <= n; ++i)
            x[sa[i]] = (y[sa[i] + k] == y[sa[i - 1] + k]
            && y[sa[i]] == y[sa[i - 1]]) ? p: ++p;
        if (p == n) break; else m = p;
    }
    for (int i = 1; i <= n; ++i)
        rk[sa[i]] = i;
}
