#include <bits/stdc++.h>
#define N 100001
using namespace std;

struct edge { int v, w; };
vector<edge> g[N];
int dep[N], mp[N][17], ms[N][17];

int bf_dfs(int u, int f, int v, int w) {
    int res = INT_MAX;
    if (u == v) return w;
    else {
        for (edge e : g[u]) {
            if (e.v == f) continue;
            int r = bf_dfs(e.v, u, v, e.w);
            if (r != INT_MAX)
                r = min(r, e.w);
            res = min(res, r);
        }
        return res;
    }
}

int brute_force(int u, int v) {
    return bf_dfs(u, 0, v, INT_MAX);
}

mt19937_64 mt(chrono::high_resolution_clock::now().time_since_epoch().count() * 1145141919ull);

void gen(int n, int q, int wmax, int id) {
    ofstream dout(to_string(id) + ".in");
    //ofstream aout(to_string(id) + ".out");

    vector<int> perm(n + 1);
    iota(perm.begin() + 1, perm.begin() + n + 1, 1);
    shuffle(perm.begin() + 1, perm.begin() + n + 1, mt);

    vector<tuple<int, int, int>> edges;
    vector<pair<int, int>> querys;
    uniform_int_distribution w(1, wmax);    //  Edge weight

    for (int i = 2; i <= n; ++i) {
        uniform_int_distribution<int> uid(1, i - 1);    //  another vertex
        int u = perm[i], v = perm[uid(mt)];
        if (w(mt) % 2) swap(u, v);
        edges.emplace_back(u, v, w(mt));
    }

    shuffle(edges.begin(), edges.end(), mt);

    uniform_int_distribution qw(1, n);
    for (int i = 1; i <= q; ++i) {
        int u = qw(mt), v = qw(mt);
        while(v == u) v = qw(mt);
        querys.emplace_back(u, v);
    }



    dout << n << ' ' << q << endl;
    for (auto[u, v, w] : edges)
        dout << u << ' ' << v << ' ' << w << endl;
    for (auto[u, v] : querys) {
        dout << u << ' ' << v << endl;
        //aout << brute_force(u, v) << endl;
    }

    dout.close();
    //aout.close();
    cout << id << endl;
}

void gen1(int n, int q, int wmax, int id) {
    ofstream dout(to_string(id) + ".in");
    vector<int> perm(n + 1);
    iota(perm.begin() + 1, perm.begin() + n + 1, 1);
    shuffle(perm.begin() + 1, perm.begin() + n + 1, mt);

    vector<tuple<int, int, int>> edges;
    vector<pair<int, int>> querys;

    uniform_int_distribution wd(1, wmax);    //  Edge weight
    uniform_int_distribution qd(1, n);

    for (int i = 2; i <= n; ++i) {
        int u = perm[i], v = perm[i - 1], w = wd(mt);
        if (wd(mt) % 2) swap(u, v);
        edges.emplace_back(u, v, w);
    }

    for (int i = 1; i <= q; ++i) {
        int u = qd(mt), v = qd(mt);
        while(v == u) v = qd(mt);
        querys.emplace_back(u, v);
    }

    shuffle(edges.begin(), edges.end(), mt);
    shuffle(querys.begin(), querys.end(), mt);

    dout << n << ' ' << q << endl;
    for (auto[u, v, w] : edges)
        dout << u << ' ' << v << ' ' << w << endl;
    for (auto[u, v] : querys)
        dout << u << ' ' << v << endl;
}

void gen2(int n, int q, int wmax, int id) {
    ofstream dout(to_string(id) + ".in");

    vector<int> perm(n + 1);
    iota(perm.begin() + 1, perm.begin() + n + 1, 1);
    shuffle(perm.begin() + 1, perm.begin() + n + 1, mt);
    uniform_int_distribution wd(1, wmax);    //  Edge weight
    uniform_int_distribution qd(1, n);

    vector<tuple<int, int, int>> edges;
    vector<pair<int, int>> querys;

    for (int i = 1; i < n; ++i) {
        int o = (i - 1) % 3, u = perm[i], v, w = wd(mt);
        if (o == 0) v = perm[i + 1];
        if (o == 2) v = perm[i - 1];
        if (o == 1) v = perm[i + 3 - (i + 2 == n)];
        if (wd(mt) % 2) swap(u, v);
        edges.emplace_back(u, v, w);
    }

    for (int i = 1; i <= q / 2; ++i)
        querys.emplace_back((wd(mt) % 2) + 1, n - (wd(mt) % 2));

    for (int i = 1; i <= q; ++i) {
        int u = qd(mt), v = qd(mt);
        while(v == u) v = qd(mt);
        querys.emplace_back(u, v);
    }

    shuffle(edges.begin(), edges.end(), mt);
    shuffle(querys.begin(), querys.end(), mt);

    dout << n << ' ' << q << endl;
    for (auto[u, v, w] : edges)
        dout << u << ' ' << v << ' ' << w << endl;
    for (auto[u, v] : querys)
        dout << u << ' ' << v << endl;
}

void test(int id, bool chk) {
    cout << id << endl;
    ifstream cin(to_string(id) + ".in");
    ofstream aout(to_string(id) + ".out");
    int n, m; cin >> n >> m;
    for (int i = 1; i <= n; ++i) g[i].clear();
    memset(mp, 0, sizeof(mp));
    memset(dep, 0, sizeof(dep));
    memset(ms, 0, sizeof(ms));

    for (int i = 0; i != n - 1; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        g[u].push_back({ v, w });
        g[v].push_back({ u, w });
    }

    for (int i = 0; i <= n; ++i)
        for (int j = 1; (1 << j) < n; ++j)
            ms[i][j] = INT_MAX;

    queue<int> q; q.push(1);
    while(!q.empty()) {
        int u = q.front(); q.pop();
        dep[u] = dep[mp[u][0]] + 1;
        for (edge e : g[u]) {
            if (e.v == mp[u][0]) continue;
            mp[e.v][0] = u;
            ms[e.v][0] = e.w;
            q.push(e.v);
        }
    }


    for (int j = 1; (1 << j) < n; ++j) {
        for (int i = 1; i <= n; ++i) {
            mp[i][j] = mp[mp[i][j - 1]][j - 1];
            ms[i][j] = min(ms[i][j - 1], ms[mp[i][j - 1]][j - 1]);
        }
    }

    while(m--) {
        int u, v, u0, v0,res = INT_MAX;
        cin >> u >> v; u0 = u, v0 = v;
        if (dep[u] < dep[v]) swap(u, v);
        for (int i = 16; dep[u] > dep[v]; --i) {
            if ((1 << i) & (dep[u] - dep[v])) {
                res = min(res, ms[u][i]);
                u = mp[u][i];
            }
        }
        if (u != v) {
            for (int i = 16; i >= 0; --i) {
                if (mp[u][i] != mp[v][i]) {
                    res = min({ res, ms[u][i], ms[v][i] });
                    u = mp[u][i];
                    v = mp[v][i];
                }
            }
            res = min({ res, ms[u][0], ms[v][0] });
            if (chk) assert(res == brute_force(u0, v0));
        }
        aout << res << endl;
    }
}

void gen_data(void) {
    for (int i = 2; i <= 6; ++i)
        gen(10, 10, 10, i);
    for (int i = 7; i <= 11; ++i)
        gen(1000, 1000, 1000, i);

    gen1(1000,1000,1000000000, 12);
    gen2(1000,1000,1000000000, 13);
    for (int i = 14; i <= 23; ++i)
        gen(100000, 100000, 1000000000, i);
    gen1(100000,100000,1000000000, 24);
    gen2(100000,100000,1000000000, 25);

    for (int i = 1; i <= 13; ++i)
        test(i, true);
    for (int i = 14; i <= 25; ++i)
        test(i, false);
}


int main(void) {
    gen_data();
}