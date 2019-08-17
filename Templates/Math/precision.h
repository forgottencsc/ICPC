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

#define pb push_back
#define mp make_pair
typedef pair<int,int> pii;

typedef double ld;
typedef vector<int> vi;
#define fi first
#define se second

// base and base_digits must be consistent
constexpr int base = 1000000000;
constexpr int base_digits = 9;

struct bigint {
  // value == 0 is represented by empty z
  vector<int> z;  // digits

  // sign == 1 <==> value >= 0
  // sign == -1 <==> value < 0
  int sign;

  bigint() : sign(1) {}

  bigint(long long v) { *this = v; }

  bigint& operator=(long long v) {
    sign = v < 0 ? -1 : 1;
    v *= sign;
    z.clear();
    for (; v > 0; v = v / base) z.push_back((int)(v % base));
    return *this;
  }

  bigint(const string& s) { read(s); }

  bigint& operator+=(const bigint& other) {
    if (sign == other.sign) {
      for (int i = 0, carry = 0; i < other.z.size() || carry; ++i) {
        if (i == z.size()) z.push_back(0);
        z[i] += carry + (i < other.z.size() ? other.z[i] : 0);
        carry = z[i] >= base;
        if (carry) z[i] -= base;
      }
    } else if (other != 0 /* prevent infinite loop */) {
      *this -= -other;
    }
    return *this;
  }

  friend bigint operator+(bigint a, const bigint& b) { return a += b; }

  bigint& operator-=(const bigint& other) {
    if (sign == other.sign) {
      if (sign == 1 && *this >= other || sign == -1 && *this <= other) {
        for (int i = 0, carry = 0; i < other.z.size() || carry; ++i) {
          z[i] -= carry + (i < other.z.size() ? other.z[i] : 0);
          carry = z[i] < 0;
          if (carry) z[i] += base;
        }
        trim();
      } else {
        *this = other - *this;
        this->sign = -this->sign;
      }
    } else {
      *this += -other;
    }
    return *this;
  }

  friend bigint operator-(bigint a, const bigint& b) { return a -= b; }

  bigint& operator*=(int v) {
    if (v < 0) sign = -sign, v = -v;
    for (int i = 0, carry = 0; i < z.size() || carry; ++i) {
      if (i == z.size()) z.push_back(0);
      long long cur = (long long)z[i] * v + carry;
      carry = (int)(cur / base);
      z[i] = (int)(cur % base);
    }
    trim();
    return *this;
  }

  bigint operator*(int v) const { return bigint(*this) *= v; }

  friend pair<bigint, bigint> divmod(const bigint& a1, const bigint& b1) {
    int norm = base / (b1.z.back() + 1);
    bigint a = a1.abs() * norm;
    bigint b = b1.abs() * norm;
    bigint q, r;
    q.z.resize(a.z.size());

    for (int i = (int)a.z.size() - 1; i >= 0; i--) {
      r *= base;
      r += a.z[i];
      int s1 = b.z.size() < r.z.size() ? r.z[b.z.size()] : 0;
      int s2 = b.z.size() - 1 < r.z.size() ? r.z[b.z.size() - 1] : 0;
      int d = (int)(((long long)s1 * base + s2) / b.z.back());
      r -= b * d;
      while (r < 0) r += b, --d;
      q.z[i] = d;
    }

    q.sign = a1.sign * b1.sign;
    r.sign = a1.sign;
    q.trim();
    r.trim();
    return {q, r / norm};
  }

  friend bigint sqrt(const bigint& a1) {
    bigint a = a1;
    while (a.z.empty() || a.z.size() % 2 == 1) a.z.push_back(0);

    int n = a.z.size();

    int firstDigit = (int)::sqrt((double)a.z[n - 1] * base + a.z[n - 2]);
    int norm = base / (firstDigit + 1);
    a *= norm;
    a *= norm;
    while (a.z.empty() || a.z.size() % 2 == 1) a.z.push_back(0);

    bigint r = (long long)a.z[n - 1] * base + a.z[n - 2];
    firstDigit = (int)::sqrt((double)a.z[n - 1] * base + a.z[n - 2]);
    int q = firstDigit;
    bigint res;

    for (int j = n / 2 - 1; j >= 0; j--) {
      for (;; --q) {
        bigint r1 =
            (r - (res * 2 * base + q) * q) * base * base +
            (j > 0 ? (long long)a.z[2 * j - 1] * base + a.z[2 * j - 2] : 0);
        if (r1 >= 0) {
          r = r1;
          break;
        }
      }
      res *= base;
      res += q;

      if (j > 0) {
        int d1 = res.z.size() + 2 < r.z.size() ? r.z[res.z.size() + 2] : 0;
        int d2 = res.z.size() + 1 < r.z.size() ? r.z[res.z.size() + 1] : 0;
        int d3 = res.z.size() < r.z.size() ? r.z[res.z.size()] : 0;
        q = (int)(((long long)d1 * base * base + (long long)d2 * base + d3) /
                  (firstDigit * 2));
      }
    }

    res.trim();
    return res / norm;
  }

  bigint operator/(const bigint& v) const { return divmod(*this, v).first; }

  bigint operator%(const bigint& v) const { return divmod(*this, v).second; }

  bigint& operator/=(int v) {
    if (v < 0) sign = -sign, v = -v;
    for (int i = (int)z.size() - 1, rem = 0; i >= 0; --i) {
      long long cur = z[i] + rem * (long long)base;
      z[i] = (int)(cur / v);
      rem = (int)(cur % v);
    }
    trim();
    return *this;
  }

  bigint operator/(int v) const { return bigint(*this) /= v; }

  int operator%(int v) const {
    if (v < 0) v = -v;
    int m = 0;
    for (int i = (int)z.size() - 1; i >= 0; --i)
      m = (int)((z[i] + m * (long long)base) % v);
    return m * sign;
  }

  bigint& operator*=(const bigint& v) {
    *this = *this * v;
    return *this;
  }

  bigint& operator/=(const bigint& v) {
    *this = *this / v;
    return *this;
  }

  bool operator<(const bigint& v) const {
    if (sign != v.sign) return sign < v.sign;
    if (z.size() != v.z.size()) return z.size() * sign < v.z.size() * v.sign;
    for (int i = (int)z.size() - 1; i >= 0; i--)
      if (z[i] != v.z[i]) return z[i] * sign < v.z[i] * sign;
    return false;
  }

  bool operator>(const bigint& v) const { return v < *this; }

  bool operator<=(const bigint& v) const { return !(v < *this); }

  bool operator>=(const bigint& v) const { return !(*this < v); }

  bool operator==(const bigint& v) const {
    return !(*this < v) && !(v < *this);
  }

  bool operator!=(const bigint& v) const { return *this < v || v < *this; }

  void trim() {
    while (!z.empty() && z.back() == 0) z.pop_back();
    if (z.empty()) sign = 1;
  }

  bool isZero() const { return z.empty(); }

  friend bigint operator-(bigint v) {
    if (!v.z.empty()) v.sign = -v.sign;
    return v;
  }

  bigint abs() const { return sign == 1 ? *this : -*this; }

  long long longValue() const {
    long long res = 0;
    for (int i = (int)z.size() - 1; i >= 0; i--) res = res * base + z[i];
    return res * sign;
  }

  friend bigint gcd(const bigint& a, const bigint& b) {
    return b.isZero() ? a : gcd(b, a % b);
  }

  friend bigint lcm(const bigint& a, const bigint& b) {
    return a / gcd(a, b) * b;
  }

  void read(const string& s) {
    sign = 1;
    z.clear();
    int pos = 0;
    while (pos < s.size() && (s[pos] == '-' || s[pos] == '+')) {
      if (s[pos] == '-') sign = -sign;
      ++pos;
    }
    for (int i = (int)s.size() - 1; i >= pos; i -= base_digits) {
      int x = 0;
      for (int j = max(pos, i - base_digits + 1); j <= i; j++)
        x = x * 10 + s[j] - '0';
      z.push_back(x);
    }
    trim();
  }

  friend istream& operator>>(istream& stream, bigint& v) {
    string s;
    stream >> s;
    v.read(s);
    return stream;
  }

  friend ostream& operator<<(ostream& stream, const bigint& v) {
    if (v.sign == -1) stream << '-';
    stream << (v.z.empty() ? 0 : v.z.back());
    for (int i = (int)v.z.size() - 2; i >= 0; --i)
      stream << setw(base_digits) << setfill('0') << v.z[i];
    return stream;
  }

  static vector<int> convert_base(const vector<int>& a, int old_digits,
                                  int new_digits) {
    vector<long long> p(max(old_digits, new_digits) + 1);
    p[0] = 1;
    for (int i = 1; i < p.size(); i++) p[i] = p[i - 1] * 10;
    vector<int> res;
    long long cur = 0;
    int cur_digits = 0;
    for (int v : a) {
      cur += v * p[cur_digits];
      cur_digits += old_digits;
      while (cur_digits >= new_digits) {
        res.push_back(int(cur % p[new_digits]));
        cur /= p[new_digits];
        cur_digits -= new_digits;
      }
    }
    res.push_back((int)cur);
    while (!res.empty() && res.back() == 0) res.pop_back();
    return res;
  }

  typedef vector<long long> vll;

  static vll karatsubaMultiply(const vll& a, const vll& b) {
    int n = a.size();
    vll res(n + n);
    if (n <= 32) {
      for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) res[i + j] += a[i] * b[j];
      return res;
    }

    int k = n >> 1;
    vll a1(a.begin(), a.begin() + k);
    vll a2(a.begin() + k, a.end());
    vll b1(b.begin(), b.begin() + k);
    vll b2(b.begin() + k, b.end());

    vll a1b1 = karatsubaMultiply(a1, b1);
    vll a2b2 = karatsubaMultiply(a2, b2);

    for (int i = 0; i < k; i++) a2[i] += a1[i];
    for (int i = 0; i < k; i++) b2[i] += b1[i];

    vll r = karatsubaMultiply(a2, b2);
    for (int i = 0; i < a1b1.size(); i++) r[i] -= a1b1[i];
    for (int i = 0; i < a2b2.size(); i++) r[i] -= a2b2[i];

    for (int i = 0; i < r.size(); i++) res[i + k] += r[i];
    for (int i = 0; i < a1b1.size(); i++) res[i] += a1b1[i];
    for (int i = 0; i < a2b2.size(); i++) res[i + n] += a2b2[i];
    return res;
  }

  bigint operator*(const bigint& v) const {
    vector<int> a6 = convert_base(this->z, base_digits, 6);
    vector<int> b6 = convert_base(v.z, base_digits, 6);
    vll a(a6.begin(), a6.end());
    vll b(b6.begin(), b6.end());
    while (a.size() < b.size()) a.push_back(0);
    while (b.size() < a.size()) b.push_back(0);
    while (a.size() & (a.size() - 1)) a.push_back(0), b.push_back(0);
    vll c = karatsubaMultiply(a, b);
    bigint res;
    res.sign = sign * v.sign;
    for (int i = 0, carry = 0; i < c.size(); i++) {
      long long cur = c[i] + carry;
      res.z.push_back((int)(cur % 1000000));
      carry = (int)(cur / 1000000);
    }
    res.z = convert_base(res.z, 6, base_digits);
    res.trim();
    return res;
  }
};