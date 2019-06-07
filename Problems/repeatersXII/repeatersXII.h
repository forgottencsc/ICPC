#include <bits/stdc++.h>
#define N 200001
#define M (19 * N)
using namespace std;

vector<int> g[N];
int pos[N], len[N], n;
int dlb[N], drb[N], dfc;
int mp[N][18];

int ls[M], rs[M], val[M], sc, rt[N];
inline int cp(int p) {
    int q = ++sc;
    ls[q] = ls[p];
    rs[q] = rs[p];
    val[q] = val[p];
    return q;
}

void modify(int x, int p, int lb, int rb) {
    if (lb + 1 == rb) val[p]++;
    else {
        int mid = (lb + rb) >> 1;
        if (x < mid) modify(x, ls[p] = cp(ls[p]), lb, mid);
        else modify(x, rs[p] = cp(rs[p]), mid, rb);
        val[p] = val[ls[p]] + val[rs[p]];
    }
}

int query(int l, int r, int lp, int rp, int lb, int rb) {
    if (l <= lb && rb <= r) return val[rp] - val[lp];
    else {
        int mid = (lb + rb) >> 1, res = 0;
        if (l < mid) res += query(l, r, ls[lp], ls[rp], lb, mid);
        if (r > mid) res += query(l, r, rs[lp], rs[rp], mid, rb);
        return res;
    }
}

void mp_init() {
    for (int i = 1; i <= n; ++i)
        for (int v : g[i])
            mp[v][0] = i;

    for (int j = 1; (1 << j) < n; ++j)
        for (int i = 1; i <= n; ++i)
            mp[i][j] = mp[mp[i][j - 1]][j - 1];
}

int mp_find(int l1, int r1) {
    int p = pos[r1];
    for (int j = 16; j >= 0; j--) {
        if (len[mp[p][j]] >= r1 - l1 + 1)
            p = mp[p][j];
    }
    return p;
}

void dfs(int u) {
    dlb[u] = ++dfc;
    for (int v : g[u]) dfs(v);
    drb[u] = dfc + 1;
}


struct sam_t {
	struct tn { tn* c[26], *f; int l, id; };
	tn ns[N], *nt;

	tn* r, *p;
	void clear() { nt = ns; }

	tn* gn(int l, tn* q = 0, int id = 0) {
		tn* np = nt++; np->l = l; np->id = id;
		if (q) {
			np->f = q->f;
			memcpy(np->c, q->c, sizeof(tn::c));
		}
		return np;
	}

	tn* extend(tn* p, int o, int id) {
		tn* np = gn(p->l + 1, 0, id);
		for (; p && !p->c[o]; p = p->f) p->c[o] = np;
		if (!p) np->f = r;
		else {
			tn* q = p->c[o];
			if (p->l + 1 == q->l) np->f = q;
			else {
				tn* nq = gn(p->l + 1, q);
				q->f = np->f = nq;
				for (; p && p->c[o] == q; p = p->f) p->c[o] = nq;
			}
		}
		return np;
	}

	void build(const string& str) {
		clear(); r = p = gn(0);
		for (int i = 1; i <= str.size(); ++i)
			p = extend(p, str[i - 1] - 'a', i);
        for (tn* p = ns; p != nt; ++p) {
            if (p->id)
                pos[p->id] = p - ns + 1;
            len[p - ns + 1] = p->l;
            if (p->f)
                g[p->f - ns + 1].push_back(p - ns + 1);
        }
        n = nt - ns;
	}

} sam;

int bf(const string& str, int l1, int r1, int l2, int r2) {
    string s = str.substr(l1 - 1, r1 - l1 + 1),
           t = str.substr(l2 - 1, r2 - l2 + 1);
    //cout << s << ' ' << t << ' ';
    int cnt = 0;
    size_t p = 0;
    do {
        p = t.find(s, p);
        if (p != string::npos) {
            p++;
            cnt++;
        }
    } while(p != string::npos);
    return cnt;
}

int main1(void) {
    int n = 100000, q = 100000;
    mt19937_64 mt(1145140019*time(0));
    uniform_int_distribution<int> ui(1, n);
    poisson_distribution ps(0.5);
    uniform_int_distribution<char> uc('a', 'd');
    string s(n, 0);
    for (int i = 0; i != n; ++i) s[i] = uc(mt);
    ofstream cout("1.in");
    ofstream aout("1.out");
    cout << s << endl;
    cout << q << endl;
    while(q--) {
        int l1, r1, l2, r2;
        l1 = ui(mt); r1 = min(n, l1 + ps(mt) * 10);
        l2 = ui(mt); r2 = min(n, l2 + ps(mt) * (n / 20));
        cout << l1 << ' ' << r1 << ' ' << l2 << ' ' << r2 << endl;
        aout << bf(s, l1, r1, l2, r2) << endl;
    }
    cout.close();
    aout.close();
    return 0;
}

int main(void) {
    ifstream cin("1.in");
    #ifndef ONLINE_JUDGE
    #endif // ONLINE_JUDGE
    string s; cin >> s; int l = s.size();
    sam.clear();
    sam.build(s);

    dfs(1);

    for (int i = 1; i <= l; ++i)
        modify(dlb[pos[i]], rt[i] = cp(rt[i - 1]), 1, n + 1);

    mp_init();
    ifstream fin("1.out");
    int q; cin >> q;
    while(q--) {
        int l1, r1, l2, r2;
        cin >> l1 >> r1 >> l2 >> r2;
        int p = mp_find(l1, r1);
        int lv = l2 + (r1 - l1 + 1) - 1, rv = r2;
        int res, pres; fin >> pres;
        if (lv > rv)
            res = 0;
        else
            res = query(dlb[p], drb[p], rt[lv - 1], rt[rv], 1, n + 1);
        //cout << res << ' ';
        if (res != pres)
            cout << pres << ' ';
        //cout << endl;
    }

    return 0;
}
