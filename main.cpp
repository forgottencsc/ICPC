#include <bits/stdc++.h>
using namespace std;

#define rep(i,l,r) for(int i=l;i<=r;++i)
#define per(i,r,l) for(int i=r;i>=l;--i)
template <typename T> void chmin(T&x,const T &y) { if(x>y)x=y; }
template <typename T> void chmax(T&x,const T &y) { if(x<y)x=y; }

const int W=1e8,B=30,T=80;
struct db {
	int a[T],n;
	bool is_neg;
	int& operator [](int x) { return a[x]; }
	int operator [](int x) const { return a[x]; }
	void left_move(int l) {
	    per(i,n-1,0)a[i+l]=a[i];
	    rep(i,0,l-1)a[i]=0; n+=l;
    }
	db (int x=0) {
	    memset(a,0,sizeof(a));n=B; is_neg=0;
        if(x<0){is_neg=1;x=-x;}
		while(x){a[n++]=x%W;x/=W;}
	}
	void print(char c='\n')const {
		if(is_neg)putchar('-');
		if(n>B) {
			printf("%d",a[n-1]);
			per(i,n-2,B)printf("%.8d",a[i]);
		}
		else printf("0");
		printf(".");
		per(i,B-1,B-2)printf("%.8d",a[i]);
		printf("%c",c);
	}
	long double evalu(int l)const {
		long double x=0;
		per(i,n-1,l)x=x*W+a[i];
		return x;
	}
};
bool operator <(const db &a,const db &b)
{
	if(a.is_neg) {
		if(!b.is_neg)return 1;
		per(i,T-1,0) if(a[i]!=b[i])return a[i]>b[i];
		return 0;
	}
	else {
		if(b.is_neg)return 0;
		per(i,T-1,0) if(a[i]!=b[i])return a[i]<b[i];
		return 0;
	}
}
bool operator >=(const db &a,const db &b) { return !(a<b); }
bool operator <=(const db &a,const db &b) { return b>=a; }
bool operator >(const db &a,const db &b) { return b<a; }
bool operator !(const db &a) { int n=a.n; while(n&&!a[n-1])--n; return !n;}
db operator -(db a) { a.is_neg^=1; return a; }
db operator +(db a,const db &b);
db operator -(db a,db b) {
	b=-b;
	if(a.is_neg) {
		if(!b.is_neg) { a=-a; swap(a,b); }
		else return a+b;
	}
	else {
		if(b.is_neg) b=-b;
		else return a+b;
	}
	if(a<b)return -(b-a);
	rep(i,0,a.n-1) if((a[i]-=b[i])<0) { a[i]+=W; --a[i+1]; }
	while(a.n&&!a[a.n-1])--a.n;
	return a;
}
db operator +(db a,const db &b)
{
	if(a.is_neg) { if(!b.is_neg) return b-(-a); }
	else { if(b.is_neg)return a-(-b); }
	chmax(a.n,b.n);
	rep(i,0,a.n-1) if((a[i]+=b[i])>=W) { a[i]-=W; ++a[i+1]; }
	if(a[a.n])++a.n;
	return a;
}
void operator +=(db &a,const db &b) { a=a+b; }
void operator -=(db &a,const db &b) { a=a-b; }
db eps1,eps2,eps3;
db operator *(const db &a,const db &b) {
	db ans;
	ans.is_neg=a.is_neg^b.is_neg;
	ans.n=max(0,a.n+b.n-B);
	rep(i,0,ans.n) {
		int jk=i+B; long long sum=0;
		rep(j,max(0,jk-(b.n-1)),min(jk,a.n-1))sum+=1ll*a[j]*b[jk-j];
		int x=i;
		while(sum) { ans[x]+=sum%W; sum/=W; ++x; }
	}
	rep(i,0,ans.n) while(ans[i]>=W) { ans[i]-=W; ++ans[i+1]; }
	if(ans.n&&!ans[ans.n-1])--ans.n;
	return ans;
}
void operator *=(db &a,const db &b) { a=a*b; }
db operator *(db a,int k) {
	per(i,a.n-1,0) {
		long long sum=1ll * a[i]*k;
		a[i]=sum%W;
		a[i+1]+=sum/W;
	}
	rep(i,0,a.n-1)
	while(a[i]>=W) { a[i]-=W; ++a[i+1]; }
	if(a[a.n])++a.n;
	return a;
}
db operator *(int k,const db &a) { return a*k; }
db operator /(db a,db b) {
	a.is_neg^=b.is_neg;
	b.is_neg=0;
	a.left_move(B);
	int l=max(0,b.n-20);
	long double b_e=b.evalu(l);
	db x; x.n=0;
	per(i,a.n-1,0) {
		x.left_move(1);
		x[0]=a[i];
		if(x>=b)
		{
			int k=x.evalu(l)/b_e;
			if(k)--k;
			a[i]=k;
			x-=k*b;
			while(x>=b) { x-=b; ++a[i]; }
		}
		else a[i]=0;
	}
	while(a.n && !a[a.n - 1]) --a.n;
	return a;
}
void operator /=(db &a,const db &b) { a = a / b; }

typedef unsigned ui;
typedef db dbl;
int dcmp(const db &x) {
    return x < -eps1 ? -1 : x > eps1;
}

//  Simplex method begin

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


int main(void) {
	ios::sync_with_stdio(0);
    #ifndef ONLINE_JUDGE
    ifstream cin("1.in");
    #endif
	eps1.n=B-10;eps1[eps1.n-1]=1;
	eps2.n=B;eps2[eps2.n-1]=1;
	eps3.n=B-10;eps3[eps3.n-1]=1;
	int n, m, t; cin >> n >> m >> t;
	simplex_t s;
	vector<pair<int, dbl>> coef;
	for (int j = 1; j <= n; ++j) {
        double w; cin >> w;
        coef.push_back({ j, w });
	}
	s.add_cstr(coef, 0, -1);

	for (int i = 1; i <= m; ++i) {
        vector<pair<int, dbl>> a; dbl b;
		for (int j = 1; j <= n; ++j) {
            double w; cin >> w;
		    a.push_back({ j, w });
		}
		double w; cin >> w; b = w;
		s.add_cstr(a, b, 0);
	}

	int res = s.simplex();
	if (res == 0) cout << "Infeasible" << endl;
	else if (res == 2) cout << "Unbounded" << endl;
	else {
        s.x[0].print();
		if (t) for (ui j = 1; j <= n; ++j)
                s.x[j].print(' ');
	}

	return 0;
}
