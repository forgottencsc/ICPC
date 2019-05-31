#include <bits/stdc++.h>
#define N 1000000

using namespace std;

typedef long long ll;

struct aca_t {
	struct tn { tn* c[26], *f, *s; int i; };
	tn ns[N], *nt;

	tn* r;
	aca_t() { nt = ns; }
	tn* gn() { return nt++; }

	void build(const vector<string>& sv) {
		r = gn();
		for (const string& s : sv) {
			tn* p = r;
			for (const char& ch : s) {
				int o = ch - 'a';
				if (!p->c[o]) p->c[o] = gn();
				p = p->c[o];
			}
			p->i = 1;
		}

		queue<tn*> q;
		for (tn*& v : r->c) {
			if (!v) v = r;
			else {
				q.push(v), v->f = r;
			}
		}
		while (!q.empty()) {
			tn* u = q.front(); q.pop();
			for (int o = 0; o != 26; ++o) {
				tn*& v = u->c[o],
					*f = u->f->c[o];
				if (v) {
					v->f = f;
					q.push(v);
					v->s = f->i ? f : f->s;
				}
				else v = f;
			}
		}
	}

	void match(char* s) {
		tn* p = r;
		for (int i = 0; s[i]; ++i) {
			int o = s[i] - 'a';
			p = p->c[o];
		}
	}

} aca;


struct sam_t {
	struct tn { tn* c[26], *f; int l, w; };
	tn ns[N], *nt;

	tn* r, *p;
	void clear() { nt = ns; }

	tn* gn(int l, tn* q = 0) {
		tn* np = nt++; np->l = l;
		if (q) {
			np->f = q->f;
			memcpy(np->c, q->c, sizeof(tn::c));
		}
		else np->w = 1;
		return np;
	}

	tn* extend(tn* p, int o) {
		tn* np = gn(p->l + 1);
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
		for (char ch : str)
			p = extend(p, ch - 'a');
	}

	vector<tn*> sort() {
		vector<int> c(p->l + 1, 0);
		vector<tn*> res(nt - ns);
		for (tn* q = ns; q != nt; ++q) c[q->l]++;
		for (int i = 1; i <= p->l; ++i) c[i] += c[i - 1];
		for (tn* q = ns; q != nt; ++q) res[--c[q->l]] = q;
		return res;

	}

} sam;


struct pa_t {
	struct tn { tn* c[26], *f; int l, w; };
	tn ns[N], *nt;
	tn* r0, *r1, *p;
	char s[N]; int n, m;

	void clear() { nt = ns; m = 0; }

	tn* gn(int l) {
		tn* np = nt++;
		memset(np->c, 0, sizeof(np));
		np->l = l; np->w = 0;
		return np;
	}

	tn* gf(tn* p, int i) {
		while (s[i] != s[i - p->l - 1])
			p = p->f;
		return p;
	}

	void build(string str) {
		clear();
		copy(str.begin(), str.end(), s + 1);
		n = str.size();
		r1 = gn(-1); r0 = gn(0); p = r0;
		p->f = r1;
		for (int i = 1; i <= str.size(); ++i) {
			int o = s[i] - 'a'; p = gf(p, i);
			if (!p->c[o]) {
				tn* np = p->c[o] = gn(p->l + 2);
				np->f = p == r1 ? r0 : gf(p->f, i)->c[o];
			}
			p = p->c[o]; p->w++;
			m = max(m, p->l);
		}
	}

	vector<tn*> sort() {
		vector<int> c(m + 1, 0);
		vector<tn*> res(nt - ns - 1);
		for (tn* q = ns + 1; q != nt; ++q) c[q->l]++;
		for (int i = 1; i <= m; ++i) c[i] += c[i - 1];
		for (tn* q = ns + 1; q != nt; ++q) res[--c[q->l]] = q;
		return res;
	}

} pa;
