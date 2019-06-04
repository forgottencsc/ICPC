#include <bits/stdc++.h>
#define int unsigned
using namespace std;

#define W 1000000001
bool ip[W]; vector<int> ps;
vector<int> dc, px, pk;
//int dc[W], px[W], pk[W];
void eulersieve() {
    dc.resize(W);
    px.resize(W);
    pk.resize(W);
	ps.reserve(W * 1.2 / log(W));
	memset(ip, 1, sizeof(ip)); ip[1] = 0;
    dc[1] = 1; px[1] = 1; pk[1] = 0;
	for (int i = 2; i != W; ++i) {
        if (i % (W / 10) == 0) cout << (i / (W / 10)) << endl;
		if (ip[i]) {
			ps.push_back(i);
            pk[i] = 1;
            px[i] = i;
            dc[i] = 2;
		}
		for (int p : ps) {
			if (1ll * i * p >= W) break;
			ip[i * p] = 0;
			if (i % p) {
				pk[i * p] = 1;
				px[i * p] = p;
				dc[i * p] = dc[i] * 2;
			}
			else {
                pk[i * p] = pk[i] + 1;
                px[i * p] = px[i] * p;
                dc[i * p] = dc[i] / (pk[i] + 1) * (pk[i] + 2);
				break;
			}
		}
	}
}

void match() {
    int p = 0;
    for (char ch : t) {
        int o = ch - 'a';
        while (p && !g[p][o])
            p = f[p];
        p = g[p][o];
        for (int q = p; q; q = f[q])
            c[q]++;
    }
}

void build() {
    queue<int> q;
    for (int o = 0; o != 26; ++o) if (g[0][o]) q.push(g[0][o]);
    while(h != t) {
        int u = q.front(); q.pop();
        for (int o = 0; o != 26; ++o) {
            int& v = g[u][o];
            if (v) {
                int w = f[u];
                while(w && !g[w][o]) w = f[w];
                f[v] = g[w][o];
                q.push(v);
            }
        }
    }
}

signed main(void) {
    ios::sync_with_stdio(0); cin.tie(0);
    #ifndef ONLINE_JUDGE
    ifstream cin("1.in");
    #endif // ONLINE_JUDGE
    eulersieve();
    int mx = 0, mc = 0;
    for (int i = 1; i != W; ++i) {
        if (mc < dc[i]) {
            mx = i;
            mc = dc[i];
            cout << i << ": " << ' ' << mc << endl;
        }
    }
    return 0;
}