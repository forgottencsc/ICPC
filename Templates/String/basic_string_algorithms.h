#include <string>
using namespace std;

//  f[i]为s以i结束的能作为s前缀的最长串长
void getf(const string& s, vector<int>& f) {
    int n = s.size(); f.resize(n, 0);// f[0] = -1;
    for (int i = 1, j = 0; i != n; ++i) {
        while (j && s[i] != s[j]) j = f[j - 1];
        if (s[i] == s[j]) ++j;
        f[i] = j;
    }
    //for (int i = 0; i != n; ++i) cout << f[i] << " \n"[i == n - 1];
}

//  l[i]为t以i结束的能作为s前缀的的最长串长
void getl(const string& s, const string& t, const vector<int>& f, vector<int>& l) {
    int n = s.size(), m = t.size(); l.resize(m, 0);
    for (int i = 0, j = 0; i != m; ++i) {
        while(j && t[i] != s[j]) j = f[j - 1];
        if (t[i] == s[j]) ++j;
        l[i] = j;
        if (j == n) j = f[j - 1];
    }
    for (int i = 0; i != m; ++i) cout << l[i] << " \n"[i == m - 1];
}

//  z[i]为s以i为起始的能作为s前缀的最长串长
void getz(const string& s, vector<int>& z) {
    int n = s.size(); z.resize(n, 0);
    for (int i = 1, l = 0, r = 0; i != n; ++i) {
        int j = z[i - l];
        if (i+j>r) for (j=max(0, r-i); i+j!=n&&s[ia+j]==s[j]; ++j);
        z[i] = j; if (i+j-1>r) l=i, r=i+j-1;
    }
    z[0] = n;
    //for(int i = 0; i != n; ++i) cout << z[i] << " \n"[i == n - 1];
}

//  e[i]为t以i起始的能作为s前缀的最长串长
void gete(const string& s, const string& t, const vector<int>& z, vector<int>& e) {
    int n = s.size(), m = t.size(); e.resize(m, 0);
    for (int i = 0, l = 0, r = 0; i != m; ++i) {
        int j = z[i - l];
        if (i+j>r) for (j=max(0, r-i); i+j!=m&&t[i+j]==s[j]; ++j);
        e[i] = j; if (i+j-1>r) l=i, r=i+j-1;
    }
    //for (int i = 0; i != m; ++i) cout << e[i] << " \n"[i == m - 1];
}

//  r[i]为t串以i为中心的回文半径：t[i+r[i]]==t[i-r[i]]
void getr(const string& s, vector<int>& r) {
    int n = s.size(), m = 2 * n + 1; r.resize(m, 0);
    string t(m, '#');
    for (int i = 0; i != n; ++i) t[2 * i + 1] = s[i];
    for (int i = 1, p = 0, w = 0; i != m; ++i) {
        int j = (i>p+w ? 0 : min(r[p-(i-p)], p+w-i));
        while(0<=i-j-1 && i+j+1<m && t[i-j-1]==t[i+j+1]) ++j;
        r[i] = j; if (i + j > p + w)  p = i, w = j;
    }
    //for (int i = 0; i != m; ++i) cout << r[i] << " \n"[i == m - 1];
}

//  判断区间[l,u)是否为回文
bool ispal(vector<int>& r, int l, int u) {
    return r[l + u] >= u - l;
}


//  Hashing
typedef long long ll;
typedef pair<ll, ll> pll;
const ll p1 = 1145140019, b1 = 893;
const ll p2 = 1919810021, b2 = 364;
ll hs1[N], hb1[N];
ll hs2[N], hb2[N];

char s[N]; int n;
void genh() {
    hb1[0] = hb2[0] = 1;
    for (int i = 1; i <= n; ++i) {
        hs1[i] = (hs1[i - 1] * b1 + s[i]) % p1;
        hb1[i] = hb1[i - 1] * b1 % p1;
        hs2[i] = (hs2[i - 1] * b2 + s[i]) % p2;
        hb2[i] = hb2[i - 1] * b2 % p2;
    }
}

pll geth(int l, int r) {
    ll v1 = (hs1[r] - hs1[l - 1] * hb1[r - l + 1]) % p1;
    ll v2 = (hs2[r] - hs2[l - 1] * hb2[r - l + 1]) % p2;
    if (v1 < 0) v1 += p1; if (v2 < 0) v2 += p2;
    return { v1, v2 };
}

pll concat(pll lh, int ln, pll rh, int rn) {
    pll r;
    r.first = (lh.first * hb1[rn] + rh.first) % p1;
    r.second = (lh.second * hb2[rn] + rh.second) % p2;
    return r;
}

int lcp(int u, int v) {
    if (s[u] != s[v]) return 0;
    int l = 1, r = n - max(u, v) + 1;
    while (l <= r) {
        int mid = (l + r) / 2;
        if (geth(u, u + mid - 1) == geth(v, v + mid - 1))
            l = mid + 1;
        else
            r = mid - 1;
    }
    return r;
}

int lcs(int u, int v) {
    if (s[u] != s[v]) return 0;
    int l = 1, r = min(u, v);
    while (l <= r) {
        int mid = (l + r) / 2;
        if (geth(u - mid + 1, u) == geth(v - mid + 1, v))
            l = mid + 1;
        else
            r = mid - 1;
    }
    return r;
}