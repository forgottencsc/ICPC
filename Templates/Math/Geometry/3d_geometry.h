#pragma once
#include <queue>
#include <cmath>

using namespace std;

typedef unsigned ui;
typedef double dbl;

const dbl eps = 1e-8, pi = acos(-1);
int dc(dbl d) { return d < -eps ? -1 : d > eps ? 1 : 0; }

struct point { dbl x, y, z; };
point operator+(point v1, point v2) { return { v1.x + v2.x, v1.y + v2.y, v1.z + v2.z }; }
point operator-(point v1, point v2) { return { v1.x - v2.x, v1.y - v2.y, v1.z - v2.z }; }
dbl operator*(point v1, point v2) { return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z; }
point operator^(point v1, point v2) {
	return { v1.y * v2.z - v1.z * v2.y,
		v1.z * v2.x - v1.x * v2.z,
		v1.x * v2.y - v1.y * v2.x };
}

namespace cv {
	struct edge { ui u, v; };
	char vis[N]; point ps[N]; ui n;
	int lnk[N][N];

	dbl S(ui u, ui v, ui w) {
		return 0.5 * len((ps[u] - ps[v]) ^ (ps[u] - ps[w]));
	}

	dbl convex_hull() {
		ui i1 = 0, i2; point p1;
		for (ui i = 1; i != n; ++i)
			if (ps[i].x > ps[i1].x)
				i1 = i;
		p1 = ps[i1]; vis[i1] = 1;


		i2 = i1 ? 0 : 1;
		for (ui i = 0; i != n; ++i) {
			point p2 = ps[i2], v1 = p2 - p1, v2 = v2 = ps[i] - p1;
			if (v1.x * v2.y - v1.y * v2.x > 0) i2 = i;
		}

		dbl sum = 0;
		queue<edge> q; q.push({ i1, i2 });
		while (q.size()) {
			edge e = q.front(); q.pop();
			ui u0 = e.u, v0 = e.v, u, v;
			point p1 = ps[u0], p2 = ps[v0], v1 = p2 - p1;
			for (u = 0; u == u0 || u == v0; ++u); v = u;

			for (ui i = 0; i != n; ++i) {
				if (i == e.u || i == e.v) continue;
				point v2 = ps[u] - p1, v3 = ps[v] - p1, v4 = ps[i] - p1;
				if (det(v1, v2, v4) < 0) u = i;
				if (det(v1, v3, v4) > 0) v = i;
			}

			if (lnk[u0][v0] != 2 && lnk[u0][u] != 2 && lnk[v0][u] != 2) {
				lnk[u0][v0]++; lnk[v0][u0]++;
				lnk[u0][u]++; lnk[u][u0]++;
				lnk[v0][u]++; lnk[u][v0]++;
				sum += S(u0, v0, u);
			}

			if (lnk[u0][v0] != 2 && lnk[u0][v] != 2 && lnk[v0][v] != 2) {
				lnk[u0][v0]++; lnk[v0][u0]++;
				lnk[u0][v]++; lnk[v][u0]++;
				lnk[v0][v]++; lnk[v][v0]++;
				sum += S(u0, v0, v);
			}

			if (lnk[u0][u] != 2) q.push({ u0, u });
			if (lnk[u0][v] != 2) q.push({ u0, v });
			if (lnk[v0][u] != 2) q.push({ v0, u });
			if (lnk[v0][v] != 2) q.push({ v0, v });
		}
		return sum;
	}
}