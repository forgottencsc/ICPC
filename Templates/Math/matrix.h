#include <bits/stdc++.h>
#define R(m) (int)(m).size()
#define C(m) (int)((m)[0].size())
const dbl eps = 1e-8;
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

mat I(int n) {
    mat r(n, vec(n, 0));
    for (int i = 0; i != n; ++i) r[i][i] = 1;
    return r;
}

mat qpow(mat a, ul b) {
    mat r = I(R(a));
    do if (b & 1) r = r * a;
    while (a = a * a, b >>= 1);
    return r;
}

ostream& operator<<(ostream& os, const mat& w) {
    for (int i = 0; i != R(w); ++i)
        for (int j = 0; j != C(w); ++j)
            os << w[i][j] << " \n"[j == C(w) - 1];
    return os;
}

//  Gaussian Elimination
void row_reduction(mat& a) {
	const int n = R(a), m = C(a);
	for (int r = 0, c = 0; r != n && c != m; ++r, ++c) {
		do for (int i = r; i != n; ++i)
			if (abs(a[r][c]) < abs(a[i][c])) swap(a[r], a[i]);
		while (abs(a[r][c]) < eps && ++c != n);
		for (int j = m - 1; j >= c; --j) a[r][j] /= a[r][c];
		for (int i = 0; c != m && i != n; ++i)
			for (int j = m - 1; i != r && j >= c; --j)
				a[i][j] -= a[r][j] * a[i][c];
	}
}

//  Get a base of null space of a
mat nsp(mat& a) {
    const int n = C(a);
    while(R(a) < n) a.push_back(vec(n, 0));
    int w = row_reduction(a); mat b(n, vec(n - w, 0));
    vector<int> p, vis(n, 0);
    for (int c = 0, r = 0; c != n; ++c)
        if (abs(a[r][c]) > eps) ++r, vis[c] = 1;
    for (int i = 0; i != n; ++i) if (vis[i]) p.push_back(i);
    for (int i = 0; i != n; ++i) if (!vis[i]) p.push_back(i);
    for (int i = 0; i != n - w; ++i) {
        for (int j = 0; j != n; ++j)
            b[j][i] = a[p[j]][p[i + w]];
        b[p[i + w]][i] = -1;
    }
    return b;
}

//  Gram–Schmidt Orthogonalization
void gso(mat& a) {
    const int n = R(a), m = C(a);
    for (int i = 1; i != m; ++i) {
        for (int j = 0; j != i; ++j) {
            dbl u = 0, v = 0;
            for (int k = 0; k != n; ++k)
                u += a[k][j] * a[k][i],
                v += a[k][j] * a[k][j];
            for (int k = 0; k != n; ++k)
                a[k][i] -= u / v * a[k][j];
        }
    }
    for (int i = 0; i != m; ++i) {
        dbl len = 0;
        for (int k = 0; k != n; ++k)
            len += a[k][i] * a[k][i];
        len = sqrt(len);
        for (int k = 0; k != n; ++k)
            a[k][i] /= len;
    }
}


namespace LP {

//	a[0][1...n] = c^T; a[1...m][0] = b;
ui n, m, c[2 * N]; dbl a[N][N], x[N], z;

int dcmp(dbl d) { return d < -eps ? -1 : d <= eps ? 0 : 1; }

//	u in, v out
void pivot(ui u, ui v) {
    swap(c[n + u], c[v]);
    //	row u *= 1 / a[u][v]
    dbl k = a[u][v]; a[u][v] = 1;
    for (ui j = 0; j <= n; ++j) a[u][j] /= k;
    for (ui i = 0; i <= m; ++i) {
        if (i == u || !dcmp(a[i][v])) continue;
        k = a[i][v]; a[i][v] = 0;
        for (ui j = 0; j <= n; ++j)
            a[i][j] -= a[u][j] * k;
    }
}

bool init() {
    for (ui i = 1; i <= n; ++i) c[i] = i;
    while (1) {
        ui u = 0, v = 0;
        for (ui i = 1; i <= m && !u; ++i)
            if (dcmp(a[i][0]) == -1) u = i;	//	b[u] < 0
        if (!u) return 1;
        for (ui j = 1; j <= n && !v; ++j)
            if (dcmp(a[u][j]) == -1) v = j;	//
        if (!v) return 0;
        pivot(u, v);
    }
}

//	0 for infeasible, 1 for success, 2 for unbounded
int simplex() {
    if (!init()) return 0;
    else while (1) {
        ui u = 0, v = 0;
        for (ui j = 1; j <= n; ++j)
            if (dcmp(a[0][j]) == 1)
                v = j;

        if (!v) {
            z = -a[0][0];
            for (ui i = 1; i <= m; ++i)
                x[c[n + i]] = a[i][0];
            return 1;
        }

        dbl w = 1e80;
        for (ui i = 1; i <= m; ++i)
            if (dcmp(a[i][v]) == 1 &&
                dcmp(w - a[i][0] / a[i][v]) == 1) {
                w = a[i][0] / a[i][v];
                u = i;
            }

        if (!u) return 2;
        pivot(u, v);
    }
}

}