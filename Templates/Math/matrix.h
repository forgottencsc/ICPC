#include <bits/stdc++.h>
#define R(m) (int)(m).size()
#define C(m) (int)((m)[0].size())
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

//  Calculate det(a), O(n^3)
dbl det(mat& a) {
    const int n = R(a); dbl res = 1;
    for (int i = 0; i != n; ++i) {
        for (int j = i + 1; j != n; ++j)
            if (fabs(a[j][i]) > fabs(a[i][i]))
                swap(a[i], a[j]), res = -res;
        if (!dc(a[i][i])) return 0;
        else res *= a[i][i];
        for (int k = n - 1; k >= i; --k)
            a[i][k] /= a[i][i];
        for (int j = i + 1; j != n; ++j)
            for (int k = n - 1; k >= i; --k)
                a[j][k] -= a[i][k] * a[j][i];
    }
    return res;
}

//  Gaussian Elimination, O(n^3)
int row_reduction(mat& a) {
    const int& n = R(a), m = C(a);
    for (int i = 0, j = 0; i != n; ++i) {
        do for (int k = i + 1; k != n; ++k)
            if (fabs(a[i][j]) < fabs(a[k][j]))
                swap(a[i], a[k]);
        while (!dc(a[i][j]) && ++j != n);
        if (j == n) return i; //  rk(a)
        for (int l = m - 1; l >= i; --l)
            a[i][l] /= a[i][j];
        for (int k = 0; k != n; ++k) {
            if (k != i) for (int l = m - 1; l >= i; --l)
                a[k][l] -= a[k][j] * a[i][l];
    }
    return n;
}

//  Get a base of null space of a, O(n^2)
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

//  Gram–Schmidt Orthogonalization, O(n^3)
void gso(mat& a) {
    const int& n = R(a), m = C(a);
    for (int i = 0; i != n; ++i) {
        for (int j = 0; j != i; ++j) {
            dbl l = 0;
            for (int k = 0; k != m; ++k) l += a[i][k] * a[j][k];
            for (int k = 0; k != m; ++k) a[i][k] -= a[j][k] * l;
        }
        dbl l = 0;
        for (int k = 0; k != m; ++k) l += a[i][k] * a[i][k];
        l = sqrt(l);
        for (int k = 0; k != m; ++k) a[i][k] /= l;
    }
}

//  QR Decomposition
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

int dcmp(const dbl &x) { return x < -eps ? -1 : x > eps; }
struct simplex_t {

    struct cstr_t {
        vector<pair<int, dbl>> a;
        dbl b; int t, r;
    };

    vector<cstr_t> cstrs;
	int m, n; vector<int> c;
	vector<vector<dbl>> a;
	vector<dbl> x;

    // -1 for coeff, 0 for less, 1 for equal, 2 for greater
    void add_cstr(const vector<pair<int, dbl>>& a, dbl b, int t) {
        cstrs.push_back({ a, b, t });
    }

	void pivot(int u, int v) {
		swap(c[n + u], c[v]);
		dbl k = a[u][v]; a[u][v] = 1;
		for (int j = 0; j <= n; ++j) a[u][j] /= k;
		for (int i = 0; i <= m; ++i) {
			if (i == u || !dcmp(a[i][v])) continue;
			k = -a[i][v]; a[i][v] = 0;
			for (int j = 0; j <= n; ++j)
				a[i][j] += a[u][j] * k;
		}
	}

	bool simplex0() {
		while (1) {
			int u = 0, v = 0;
			for (int j = 1; !v && j <= n; ++j)
				if (dcmp(a[0][j]) == 1) v = j;
			if (!v)
				return true;
			dbl w = 1e100;
			for (int i = 1; i <= m; ++i)
				if (dcmp(a[i][v]) == 1 &&
					dcmp(w - a[i][0] / a[i][v]) == 1) {
					w = a[i][0] / a[i][v];
					u = i;
				}
			if (!u)
                return false;
			pivot(u, v);
		}
	}

	//  0 for Infeasible, 2 for Unbounded
	int simplex() {
        int r = 0;
        m = cstrs.size() - 1; n = 0;
	    for (cstr_t& cstr : cstrs) {
            for (const pair<int, dbl>& p : cstr.a)
                n = max(n, p.first);
            if (cstr.t == 0 || cstr.t == 2)
                cstr.r = ++r;
            if (cstr.t == -1)
                swap(cstr, cstrs.front());
	    }

	    c.resize(1 + n + r + m, 0);
        a.resize(m + 1, vector<dbl>(n + r + 1, 0));
        x.resize(1 + n + r, 0);

        for (const pair<int, dbl>& p : cstrs[0].a)
            a[0][p.first] = p.second;
        for (int i = 1; i <= m; ++i) {
            const cstr_t& cstr = cstrs[i];
            for (const pair<int, dbl>& p : cstr.a)
                a[i][p.first] = p.second;
            if (cstr.t == 0) a[i][cstr.r + n] = 1;
            if (cstr.t == 2) a[i][cstr.r + n] = -1;
            a[i][0] = cstr.b;
        }

        n += r;

		for (int i = 1; i <= n + m; ++i) c[i] = i;

		vector<dbl> a0(n + 1, 0); swap(a0, a[0]);
		for (int i = 1; i <= m; ++i) {
			if (a[i][0] < 0)
				for (int j = 0; j <= n; ++j)
					a[i][j] = -a[i][j];
			for (int j = 0; j <= n; ++j)
				a[0][j] += a[i][j];
		}

		simplex0();

		if (dcmp(a[0][0])) return 0;

		vector<int> cv(1, 0), rv(1, 0);
		for (int i = 1; i <= m; ++i) {
			bool del = 0;
			if (c[n + i] > n) {
				int p = i, q = 0;
				for (int j = 1; !q && j <= n; ++j)
					if (dcmp(a[i][j]) && c[j] <= n) q = j;
				if (!q) del = 1;
				else pivot(p, q);
			}
			if (!del) rv.push_back(i);
		}
		for (int j = 1; j <= n + m; ++j)
			if (c[j] <= n) cv.push_back(j);

		m = rv.size() - 1; n = n - m;
		vector<vector<dbl>> a1(m + 1, vector<dbl>(n + 1, 0));

		for (int j = 1; j <= n; ++j) a1[0][j] = a0[c[cv[j]]];
		for (int i = 1; i <= m; ++i)
			for (int j = 0; j <= n; ++j)
				a1[i][j] = a[rv[i]][cv[j]];

		for (int i = 1; i <= m; ++i)
			for (int j = 0; j <= n; ++j)
				a1[0][j] -= a0[c[cv[n + i]]] * a1[i][j];

		for (int i = 1; i <= m + n; ++i) cv[i] = c[cv[i]];
		swap(c, cv);
		swap(a, a1);

		if (!simplex0()) return 2;

		x[0] = -a[0][0];
		for (int i = 1; i <= m; ++i)
			x[c[n + i]] = a[i][0];

		return 1;
	}

};

//  Incomplete
struct integer_programming {

    vector<cstr_t> cstrs;
    unordered_set<int> cstri;

    dbl res; bool flg;

    integer_programming() : flg(0) {}

    void int_cstr(int i) { cstri.insert(i); }

    // -1 for coeff, 0 for less, 1 for equal, 2 for greater
    void add_cstr(const vector<pair<int, dbl>>& a, dbl b, int t) {
        cstrs.push_back({ a, b, t });
    }

    pair<double, int> branch_and_bound(simplex_t s) {
        pair<dbl, int> r;
        r.second = s.simplex();
        if (r.second != 1) return { 0, res };
        else {
            r.first = s.x[0];
            if (flg && r.first < res) return { r.first, 0 };
            for (int i : cstri) {
                if (!dc(s.x[i] - round(s.x[i])))
                    continue;
                simplex_t s1, s2;
                s1.cstrs = s2.cstrs = s.cstrs;
                s1.add_cstr({ i, 1 }, floor(s.x[i]), 0);
                s2.add_cstr({ i, 1 }, ceil(s.x[i]), 2);
                pair<dbl, int> r1 = branch_and_bound(s1);
                pair<dbl, int> r2 = branch_and_bound(s2);
                if (!r1.second) return r2;
                if (!r2.second) return r1;
                return { max(r1.first, r2.first), r1.second };
            }
            res = r.first; flg = 1;
            return r;
        }
    }

};

//  Simple simplex method, maximize cTx, s.t.Ax<=B;
int n, m, c[5001]; dbl a[4001][201], x[201], z;

int dcmp(dbl d) { return d < -eps ? -1 : d <= eps ? 0 : 1; }

void pivot(int u, int v) {
	swap(c[n + u], c[v]);
	dbl k = a[u][v]; a[u][v] = 1;
	for (int j = 0; j <= n; ++j) a[u][j] /= k;
	for (int i = 0; i <= m; ++i) {
		if (i == u || !dcmp(a[i][v])) continue;
		k = a[i][v]; a[i][v] = 0;
		for (int j = 0; j <= n; ++j)
			a[i][j] -= a[u][j] * k;
	}
}

bool init() {
	for (int i = 1; i <= n; ++i) c[i] = i;
	while (1) {
		int u = 0, v = 0;
		for (int i = 1; i <= m; ++i)
			if (dcmp(a[i][0]) == -1 && (!u || dcmp(a[u][0] - a[i][0]) == 1)) u = i;
		if (!u) return 1;
		for (int j = 1; j <= n && !v; ++j)
			if (dcmp(a[u][j]) == -1) v = j;
		if (!v) return 0;
		pivot(u, v);
	}
}

int simplex() {
	if (!init()) return 0;
	while (1) {
		int u = 0, v = 0;
		for (int j = 1; j <= n; ++j)
			if (dcmp(a[0][j]) == 1 && (!v || a[0][j] > a[0][v])) v = j;

		if (!v) {
			z = -a[0][0];
			for (int i = 1; i <= m; ++i)
				x[c[n + i]] = a[i][0];
			return 1;
		}

		dbl w = 1e20;
		for (int i = 1; i <= m; ++i)
			if (dcmp(a[i][v]) == 1 &&
				dcmp(w - a[i][0] / a[i][v]) == 1) {
				w = a[i][0] / a[i][v];
				u = i;
			}
		if (!u) return 2;
		pivot(u, v);
	}
}
