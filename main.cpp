#include <bits/stdc++.h>
#define R(x) ((x).size())
#define C(x) ((x)[0].size())
using namespace std;

typedef long double dbl;
const dbl eps = 1e-7;
int dc(dbl f) { return f < -eps ? -1 : f > eps ? 1 : 0; }

typedef vector<dbl> vec;
typedef vector<vec> mat;

mat operator*(const mat& a, const mat& b) {
    mat r(R(a), vec(C(b), 0));
    for (int i = 0; i != R(a); ++i)
        for (int j = 0; j != C(b); ++j)
            for (int k = 0; k != C(a); ++k)
                r[i][j] += a[i][k] * b[k][j];
    return r;
}

//  returns rk(a)
int row_reduction(mat& a) {
    const int& n = R(a), m = C(a);
    for (int i = 0, j = 0; i != n; ++i) {
        do for (int k = i + 1; k != n; ++k)
            if (fabs(a[i][j]) < fabs(a[k][j]))
                swap(a[i], a[k]);
        while (!dc(a[i][j]) && ++j != n);
        if (j == n) return i;
        for (int l = m - 1; l >= i; --l)
            a[i][l] /= a[i][j];
        for (int k = 0; k != n; ++k)
            if (k != i) for (int l = m - 1; l >= i; --l)
                a[k][l] -= a[k][j] * a[i][l];
    }
    return n;
}

mat transpose(const mat& a) {
    int n = R(a), m = C(a);
    mat b(m, vec(n));
    for (int i = 0; i != n; ++i)
        for (int j = 0; j != m; ++j)
            b[j][i] = a[i][j];
    return b;
}

ostream& operator<<(ostream& os, const mat& w) {
    for (int i = 0; i != R(w); ++i)
        for (int j = 0; j != C(w); ++j)
            os << w[i][j] << " \n"[j == C(w) - 1];
    return os;
}


mat nsp(mat& a, int w0) {
    const int n = C(a);
    while(R(a) < n) a.push_back(vec(n, 0));
    int w = row_reduction(a); mat b(n, vec(n - w, 0));
    //cout << w << ' ' << w0 << endl;
    assert(w == w0);
    vector<int> p, vis(n, 0);
    for (int c = 0, r = 0; c != n; ++c)
        if (dc(a[r][c])) ++r, vis[c] = 1;
    for (int i = 0; i != n; ++i) if (vis[i]) p.push_back(i);
    for (int i = 0; i != n; ++i) if (!vis[i]) p.push_back(i);
    for (int i = 0; i != n - w; ++i) {
        for (int j = 0; j != n; ++j)
            b[j][i] = a[p[j]][p[i + w]];
        b[p[i + w]][i] = -1;
    }
    return b;
}

void gso(mat& b) {
    if (!R(b) || !C(b)) return;
    mat a = transpose(b);
    const int& n = R(a), m = C(a);
    //if (!n || !m) return;
    for (int i = 0; i != n; ++i) {
        for (int j = 0; j != i; ++j) {
            dbl l = 0;
            for (int k = 0; k != m; ++k)
                l += a[i][k] * a[j][k];
            for (int k = 0; k != m; ++k)
                a[i][k] -= a[j][k] * l;
        }
        dbl l = 0;
        for (int k = 0; k != m; ++k)
            l += a[i][k] * a[i][k];
        l = sqrt(l);
        for (int k = 0; k != m; ++k)
            a[i][k] /= l;
    }
    b = transpose(a);
}

dbl dis(const mat& a, const mat& b) {
    if (!R(a) || !C(a)) return 0;
    int n = R(a), m = C(a);
    dbl sum = 0;
    for (int i = 0; i != n; ++i) {
        for (int j = 0; j != m; ++j) {
            dbl res = a[i][j] - b[i][j];
            //assert(fabs(res) < 1e-3);
            sum += res * res;
        }
    }
    return sqrt(sum);
}

mt19937_64 mt(time(0));
uniform_real_distribution<dbl> urd(-1e2, 1e2);
uniform_int_distribution<int> uid;
mat gen(int n, int& w) {
    mat a(n, vec(n));
    for (int i = 0; i != n; ++i)
        for (int j = 0; j != n; ++j)
            a[i][j] = urd(mt);
    w = uid(mt) % n;
    vector<int> pos(n), res;
    iota(pos.begin(), pos.end(), 0);
    sample(pos.begin(), pos.end(), back_inserter(res), w, mt);
    set<int> npl(res.begin(), res.end());
    for (int x : npl) {
        for (int j = 0; j != n; ++j)
            a[x][j] = 0;
        for (int i = 0; i != n; ++i)
        if (npl.find(i) == npl.end()) {
            dbl r = urd(mt) / n;
            for (int j = 0; j != n; ++j)
                a[x][j] += r * a[i][j];
        }
    }
    w = n - w;
    return a;
}

mat I(int n) {
    mat r(n, vec(n, 0));
    for (int i = 0; i != n; ++i) r[i][i] = 1;
    return r;
}

dbl avg(const vector<dbl>& x) {
    dbl sum = 0;
    for (int i = 0; i != x.size(); ++i)
        sum += x[i];
    return sum / x.size();
}

dbl var(const vector<dbl>& x) {
    dbl a = avg(x), sum = 0;
    for (int i = 0; i != x.size(); ++i)
        sum += (x[i] - a) * (x[i] - a);
    return sqrt(sum / x.size());
}

int main(void) {
//    ios::sync_with_stdio(0); cin.tie(0);
//    #ifndef ONLINE_JUDGE
//    ifstream cin("1.in");
//    #endif // ONLINE_JUDGE
//
//    freopen("1.in", "r", stdin);
    int T = 100, n = 200;
    vector<dbl> x, y;
    while(T--) {
        int w0;
        mat a = gen(n, w0);
        mat b = a;
        mat c = nsp(b, w0);
        gso(c);
        mat d = a * c;
        mat e = mat(R(d), vec(C(d), 0));
        dbl d1 = dis(d, e), d2 = dis(transpose(c) * c, I(n - w0));
        x.push_back(d1); y.push_back(d2);
        cout << row_reduction(b) << ' ' << d1 << ' ' << d2 << endl;
    }
    cout << *max_element(x.begin(), x.end()) << ' ' << avg(x) << ' ' << var(x) << endl;
    cout << *max_element(x.begin(), x.end()) << ' ' << avg(y) << ' ' << var(y) << endl;
    return 0;
}
