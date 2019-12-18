#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int P = 998244353, g = 3, W = 18, S = 1 << W;

int add(int a, int b) { int r = a + b; return r < P ? r : r - P; }
int sub(int a, int b) { int r = a - b; return r < 0 ? r + P : r; }
int mul(ll a, ll b) { return a * b % P; }
int inv(int a) { return a == 1 ? 1 : mul(inv(P % a), P - P / a); }
int qpm(int a, ll b) {
    int r = 1;
    do if (b & 1) r = mul(r, a);
    while (a = mul(a, a), b >>= 1);
    return r;
}

const int W = 18, S = 1 << W;
int w[S + 1], rev[S << 1], *r[W + 1];
void init() {
    for (int s = 0; s <= W&&(r[s]=rev+(1<<s),1); ++s)
        for (int i = 0; i != (1 << s); ++i)
            r[s][i] = (r[s][i >> 1] >> 1) | ((i & 1) << (s - 1));
    w[0] = 1; w[1] = qpm(g, (P - 1) / S);
    for (int i = 2; i <= S; ++i) w[i] = mul(w[i - 1], w[1]);
}

typedef vector<int> vec;
typedef vector<vec> mat;

ostream& operator<<(ostream& os, const mat& m) {
    for (int i = 0; i != m.size(); ++i) {
        for (int j = 0; j != m[i].size(); ++j)
            os << m[i][j] << ' ';
        os << endl;
    }
    return os;
}

mat resz(const mat& m) {
    int n = 1; while (n < max(m.size(), m[0].size())) n <<= 1;
    mat t = m; t.resize(n, vec());
    for (vec& v : t) v.resize(n, 0);
    return t;
}

mat ntt_bf(const mat& m) {
    mat t = resz(m); int n = t.size();
    mat r(n, vec(n, 0));
    int w = qpm(g, (P - 1) / n);
    for (int i = 0; i != n; ++i)
        for (int j = 0; j != n; ++j)
            for (int k = 0; k != n; ++k)
                for (int l = 0; l != n; ++l)
                    r[i][j] = add(r[i][j], mul(t[k][l],qpm(w,i*k+j*l)));
    return r;
}

mat ntt0(const mat& m) {
    int n = m.size();
    if (n == 1) return m;
    mat m00(n/2,vec(n/2,0));
    mat m01(n/2,vec(n/2,0));
    mat m10(n/2,vec(n/2,0));
    mat m11(n/2,vec(n/2,0));
    for (int i = 0; i != n; ++i) {
        for (int j = 0; j != n; ++j) {
            if (i % 2 == 0 && j % 2 == 0) m00[i/2][j/2] = m[i][j];
            if (i % 2 == 0 && j % 2 == 1) m01[i/2][j/2] = m[i][j];
            if (i % 2 == 1 && j % 2 == 0) m10[i/2][j/2] = m[i][j];
            if (i % 2 == 1 && j % 2 == 1) m11[i/2][j/2] = m[i][j];
        }
    }
    m00 = ntt0(m00); m01 = ntt0(m01);
    m10 = ntt0(m10); m11 = ntt0(m11);
    int w = qpm(g, (P - 1) / n);
    mat r(n, vec(n, 0));
    for (int i = 0; i != n / 2; ++i) {
        for (int j = 0; j != n / 2; ++j) {
            r[i][j] = add(add(m00[i][j],mul(qpm(w,j),m01[i][j])),add(mul(qpm(w,i),m10[i][j]),mul(qpm(w,i+j),m11[i][j])));
            r[i][j+n/2] = add(sub(m00[i][j],mul(qpm(w,j),m01[i][j])),sub(mul(qpm(w,i),m10[i][j]),mul(qpm(w,i+j),m11[i][j])));
            r[i+n/2][j] = sub(add(m00[i][j],mul(qpm(w,j),m01[i][j])),add(mul(qpm(w,i),m10[i][j]),mul(qpm(w,i+j),m11[i][j])));
            r[i+n/2][j+n/2] = sub(sub(m00[i][j],mul(qpm(w,j),m01[i][j])),sub(mul(qpm(w,i),m10[i][j]),mul(qpm(w,i+j),m11[i][j])));
        }
    }
    return r;
}

mat ntt1(mat m) {
    int n = m.size(), s = log2(n);
    for (int i = 0; i != n; ++i)
        for (int j = 0; j != n; ++j)
            if (i < r[s][i]) swap(a[i][j], a[r[s][i]][j]);
    for (int i = 0; i != n; ++i)
        for (int j = 0; j != n; ++j)
            if (j < r[s][j]) swap(a[i][j], a[i][r[s][j]]);
    for (int i = 1, z = 0; i != n; i <<= 1, ++z) {
        for (int j1 = 0; j1 != m; j1 += (i << 1)) {
            for (int j2 = 0; j2 != m; j2 += (i << 1)) {
                for (int k = 0; k != i; ++k) {
                    int a00 = a[j1+k][j2+k], a01 = a[j1+k][i+j2+k];
                    int a10 = a[i+j1+k][j2+k], a11 = a[i+j1+k][i+j2+k];
                }
            }
        }
    }
}

mat ntt(const mat& m) {
    mat t = ntt1(resz(m));
}



mt19937_64 mt(time(0));
uniform_int_distribution<int> uid(0,P-1);
mat get_rnd(int n) {
    mat m(n,vec(n,0));
    for (int i = 0; i != n; ++i)
        for (int j = 0; j != n; ++j)
            m[i][j] = uid(mt);
    return m;
}

int main(void) {
    ios::sync_with_stdio(0); cin.tie(0);
    #ifndef ONLINE_JUDGE
    ifstream cin("1.in");
    #endif // ONLINE_JUDGE

    mat m = get_rnd(64);

    while(1) {
    mat m1 = ntt(m);
    mat m2 = ntt_bf(m);

    cout << boolalpha << (m1 == m2) << endl;
    }

    return 0;
}

