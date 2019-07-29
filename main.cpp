#include <bits/stdc++.h>
using namespace std;

#define R(m) (int)(m).size()
#define C(m) (int)((m)[0].size())
typedef double dbl;
const dbl eps = 1e-8;
typedef vector<dbl> vec;
typedef vector<vec> mat;

ostream& operator<<(ostream& os, const mat& w) {
    for (int i = 0; i != R(w); ++i)
        for (int j = 0; j != C(w); ++j)
            os << w[i][j] << " \n"[j == C(w) - 1];
    return os;
}

mat operator*(const mat& a, const mat& b) {
    mat r(R(a), vec(C(b), 0));
    for (int i = 0; i != R(a); ++i)
        for (int j = 0; j != C(b); ++j)
            for (int k = 0; k != C(a); ++k)
                r[i][j] += a[i][k] * b[k][j];
    return r;
}

mat transpose(const mat& a) {
    int n = R(a), m = C(a);
    mat b(m, vec(n));
    for (int i = 0; i != n; ++i)
        for (int j = 0; j != m; ++j)
            b[j][i] = a[i][j];
    return b;
}

void gso(mat& a) {
    const int& n = R(a), m = C(a);
    for (int i = 0; i != m; ++i) {
        for (int j = 0; j != i; ++j) {
            dbl l = 0;
            for (int k = 0; k != n; ++k)
                l += a[k][i] * a[k][j];
            for (int k = 0; k != n; ++k)
                a[k][i] -= a[k][j] * l;
        }
        dbl l = 0;
        for (int k = 0; k != n; ++k)
            l += a[k][i] * a[k][i];
        l = sqrt(l);
        for (int k = 0; k != n; ++k)
            a[k][i] /= l;
    }
}

pair<mat, mat> QR(const mat& a) {
    mat q = a; gso(q);
    return { q, transpose(q) * a };
}

vector<dbl> eigenvalues(mat a) {
    pair<mat, mat> qr;
    for (int i = 0; i != 10; ++i) {
        qr = QR(a);
        a = qr.second * qr.first;
    }
    vector<dbl> res;
    for (int i = 0; i != R(a); ++i)
        res.push_back(a[i][i]);
    return res;
}

int main(void) {
    ios::sync_with_stdio(0); cin.tie(0);
    #ifndef ONLINE_JUDGE
    ifstream cin("1.in");
    #endif // ONLINE_JUDGE

    mat m = { {1, 2, 3}, { 2, 4, 5 }, { 3, 5, 6 } };
    auto v = eigenvalues(m);
    for (dbl w : v)
        cout << w << ' ';
    cout << endl;
    return 0;
}