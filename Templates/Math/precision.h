#define rep(i,l,r) for(int i=l;i<=r;++i)
#define per(i,r,l) for(int i=r;i>=l;--i)
template <typename T> void chmin(T&x,const T &y) { if(x>y)x=y; }
template <typename T> void chmax(T&x,const T &y) { if(x<y)x=y; }

const int W=1e8,B=20,T=60;
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
		int jk=i+B;s64 sum=0;
		rep(j,max(0,jk-(b.n-1)),min(jk,a.n-1))sum+=(s64)a[j]*b[jk-j];
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
		s64 sum=(s64)a[i]*k;
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
int cmp(const db &x,const db &eps) { return x < -eps ? -1 : x > eps; }