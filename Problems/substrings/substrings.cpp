#include <bits/stdc++.h>
#define N 100001
using namespace std;
typedef long long ll;

ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }

ll mod(ll x, ll p) { x %= p; return x + (x < 0 ? p : 0); }

ll exgcd(ll a, ll b, ll& u, ll& v) { ll d;
	if (b) d = exgcd(b, a % b, v, u), v -= (a / b) * u;
	else d = a, u = 1, v = 0; return d;
}

bool lce(ll& a, ll& b, ll& p) {
	ll x, k, d = exgcd(a, p, x, k);
	if (b % d == 0) a = 1, b = mod(x * b / d, p /= d);
	return a == 1;
}

int n, k, w;
char str[N]; int s[N];
ll p10[N];
vector<int> d;

ll dc(int l, int r) {
    if (l == r) return s[l] % k == 0;
    int m = (l + r) >> 1;
    ll res = dc(l, m) + dc(m + 1, r);
    vector<unordered_map<ll, int>> cnt(w);

    vector<ll> x(w, 0);
    for (int i = m; i >= l; --i) {
        for (int j = 0; j != w; ++j) {
            x[j] = (x[j] + p10[m - i] * s[i]) % d[j];
            cnt[j][x[j]]++;
        }
    }

    ll y = 0;
    for (int i = m + 1; i <= r; ++i) {
        y = (10 * y + s[i]) % k;
        ll a = p10[i - m], b = k - y, p = k;
        if (!lce(a, b, p)) continue;
        else {
            ll j = lower_bound(d.begin(), d.end(), p) - d.begin();
            auto it = cnt[j].find(b);
            if (it == cnt[j].end()) continue;
            else res += it->second;
        }
    }

    return res;
}

void solve(istream& cin, ostream& cout) {
    cin >> k >> str; n = strlen(str);
    for (int i = 1; i <= n; ++i)
        s[i] = str[i - 1] - '0';

    p10[0] = 1;
    for (int i = 1; i != N; ++i)
        p10[i] = p10[i - 1] * 10 % k;

    d.clear();
    for (int i = 0; i <= 30; ++i)
        d.push_back(k / gcd(p10[i], k));

    sort(d.begin(), d.end());
    d.erase(unique(d.begin(), d.end()), d.end());
    w = d.size();

    cout << dc(1, n) << endl;
}

int main1(void) {
    ios::sync_with_stdio(0); cin.tie(0);
    #ifndef ONLINE_JUDGE
    ifstream cin("1.in");
    #endif // ONLINE_JUDGE

    solve(cin, cout);

    return 0;
}