#include <bits/stdc++.h>
#define P 1004535809

using namespace std;

typedef long long ll;

inline int add(int a, int b) { int r = a + b; return r < P ? r : r - P; }
inline int sub(int a, int b) { int r = a - b; return r < 0 ? r + P : r; }
inline int mul(ll a, ll b) { ll r = a * b; return r % P; }
inline int inv(int a) { return a == 1 ? a : mul(inv(P % a), P - P / a); }
inline int qpm(int a, int b) {
    int r = 1;
    do if (b & 1) r = mul(r, a);
    while (a = mul(a, a), b >>= 1);
    return r;
}

namespace NTT {

const int W = 19, S = 1 << W, g = 3;
int fr[W][S], fw[2][S];

void init() {
    for (int s = 1; s != W; ++s)
        for (int i = 0; i != (1 << s); ++i)
            fr[s][i] = (fr[s][i>>1]>>1)|((i&1)<<(s-1));
    fw[0][0] = fw[1][0] = 1;
    fw[0][1] = qpm(g, (P - 1) / (1 << W));
    fw[1][1] = inv(fw[0][1]);
    for (int i = 2; i != (1 << W); ++i) {
        fw[0][i] = mul(fw[0][i - 1], fw[0][1]);
        fw[1][i] = mul(fw[1][i - 1], fw[1][1]);
    }
}

int fs, ft;
int init(int n) { for (fs=1,ft=0; fs<n; fs<<=1,++ft); return fs; }

void ntt(int* p, int t) {
    for (int i=0;i!=fs;++i) if (i<fr[ft][i]) swap(p[i],p[fr[ft][i]]);
    for (int i = 1, s = 0; i != fs; i <<= 1, s++)
        for (int j = 0; j != fs; j += (i << 1))
            for (int k = 0; k != i; ++k) {
                int u=p[j+k],v=mul(fw[t][k<<(W-s-1)],p[i+j+k]);
                p[j+k] = add(u, v), p[i+j+k] = sub(u, v);
            }
    for (int i=0,x=inv(fs);t&&i!=fs;++i) p[i]=mul(p[i],x);
}


int p1[S], p2[S];
vector<int> conv(const vector<int>& b1, const vector<int>& b2) {
    int n1 = b1.size(), n2 = b2.size(), n3 = n1 + n2; init(n3);
    copy_n(b1.begin(), n1, p1); fill(p1 + n1, p1 + fs, 0);
    copy_n(b2.begin(), n2, p2); fill(p2 + n2, p2 + fs, 0);
    ntt(p1, 0); ntt(p2, 0);
    for (int i = 0; i != fs; ++i) p1[i] = mul(p1[i], p2[i]);
    ntt(p1, 1); return vector<int>(p1, p1 + n3 - 1);
}

}

struct biu;

string to_string(const biu& b);
biu from_string(const string& s);


const size_t rad = 10;
const char* rch = "0123456789ABCDEF";
struct biu : vector<int> {

    biu(ll x = 0) {  while (x) push_back(x % rad), x /= rad; }


    void clear() { while (!empty() && !back()) pop_back(); }

    friend int cmp(const biu& b1, const biu& b2) {
        int n1 = b1.size(), n2 = b2.size();
        if (n1 != n2) return n1 < n2 ? -1 : 1;
        for (int i = n1 - 1; i >= 0; --i)
            if (b1[i] != b2[i]) return b1[i] < b2[i] ? -1 : 1;
        return 0;
    }

    friend biu operator+(const biu& b1, const biu& b2) {
        int n1 = b1.size(), n2 = b2.size();
        biu b; b.assign(max(n1, n2) + 1, 0);
        for (int i = 0; i != max(n1, n2); ++i) {
            b[i] += (i < n1 ? b1[i] : 0) + (i < n2 ? b2[i] : 0);
            b[i + 1] += b[i] / rad, b[i] %= rad;
        }
        return b.clear(), b;
    }

    friend biu operator-(const biu& b1, const biu& b2) {
        int n2 = b2.size(), j; biu b = b1;
        for (int i = n2 - 1; i >= 0; --i) {
            if (b[i] < b2[i]) {
                for (j = i + 1; !b[j]; ++j) b[j] = rad - 1;
                b[j]--, b[i] += rad;
            }
            b[i] -= b2[i];
        }
        return b.clear(), b;
    }

//    //  Karatsuba
//    friend biu operator*(const biu& b1, const biu& b2) {
//        if (b1.empty() || b2.empty()) return {};
//        if (b1.size() <= 9 && b2.size() <= 9) return biu(to_llong(b1)*to_llong(b2));
//        biu u(b1), v(b2), a, b, c, d; int n = (max(u.size(), v.size()) + 1) / 2;
//        if (u.size() < n) u.resize(n, 0); if (v.size() < n) v.resize(n, 0);
//        a.assign(u.begin(), u.begin() + n); b.assign(u.begin() + n, u.end());
//        c.assign(v.begin(), v.begin() + n); d.assign(v.begin() + n, v.end());
//        biu res, e = a * c, f = b * d, g = (a + b) * (c + d) - e - f;
//        g.insert(g.begin(), n, 0); f.insert(f.begin(), 2 * n, 0); res = e + f + g;
//        return res.clear(), res;
//    }

    // Use with NTT
    friend biu operator*(const biu& b1, const biu& b2) {
        if (b1.empty() || b2.empty()) return {};
        vector<int> v = NTT::conv(b1, b2);
        int n3 = v.size(); biu b; b.assign(n3 + 1, 0);
        for (int i=0;i!=n3;++i)b[i]+=v[i],b[i + 1]+=b[i]/rad,b[i]%=rad;
        return b.clear(), b;
    }

    friend biu operator/(const biu& b1, const biu& b2) {
        int r = cmp(b1, b2); if (r != 1) return r + 1;
        int n1 = b1.size(), n2 = b2.size(), s = 2;
        biu x1; x1.assign(2, 0); x1.back() = 100 / (b2.back() * 10 + (b2.size() > 1 ? b2.end()[-2] : 0));
        for (int i = 1; s <= n1; ++i, s <<= 1) {
            biu w(b2);
            if (w.size() < s) w.insert(w.begin(), s - w.size(), 0);
            else w.erase(w.begin(), w.end() - s);
            w = w * x1;
            biu t; t.assign(w.size() + (w.back() != 1), 0); t.back() = 2;
            x1 = x1 * (t - w);
            x1.erase(x1.begin(), x1.begin() + s);
        }
        biu b = b1 * x1;
        b.erase(b.begin(), b.begin() + x1.size());
        cout << to_string(b1) << endl << to_string(b * b2) << endl;
        biu e = b2 * b;
        if (cmp(e + b2, b1) <= 0)
            b = b + 1;
        return b;
    }
};

string to_string(const biu& b) {
    int n = b.size(); if (!n) return "0";
    string s; for (int i = n - 1; i >= 0; --i) s += rch[b[i]];
    return s;
}

biu from_string(const string& s) {
    biu b; for (char ch : s) b.push_back(strchr(rch, ch) - rch);
    reverse(b.begin(), b.end()); return b;
}

int main(void) {
    ios::sync_with_stdio(0); cin.tie(0);
    #ifndef ONLINE_JUDGE
    ifstream cin("1.in");
    #endif // ONLINE_JUDGE

    NTT::init();

    string sa, sb; cin >> sa >> sb;
    biu a = from_string(sa), b = from_string(sb);
    biu q = a / b, r = a - b * q;
    cout << to_string(q) << endl << to_string(r) << endl;
    return 0;
}

