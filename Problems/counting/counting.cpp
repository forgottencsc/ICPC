#include <bits/stdc++.h>
#define N 100001
using namespace std;

int n, k;
char s[N];

typedef long long ll;

int bl() {
    int ans = 0;
    for (int i = 0; i != n; ++i) {
        for (int j = i + 1; j <= n; ++j) {
            int sum = 0;
            for (int w = i; w != j; ++w)
                sum = (sum * 10 + s[w] - '0') % k;
            if (!sum) ans++;
        }
    }
    return ans;
}

int count1() {
    vector<int> c(k, 0); c[0] = 1;
    ll sum = 0, ans = 0;
    for (int i = 0; i != n; ++i) {
        sum = (sum * 10 + s[i] - '0') % k;
        ans += c[sum];
        c[sum]++;
        vector<int> t(k);
        for (int j = 0; j != k; ++j) t[j * 10 % k] += c[j];
        c = t;
    }
    return ans;
}

int count2() {
    reverse(s, s + n);
    vector<int> cnt(k, 0);
    int sum = 0, p = 1;
    for (int i = 0; i != n; ++i) {
        sum = (sum + p * (s[i] - '0')) % k;
        p = p * 10 % k;
        cnt[sum]++;
    }
    reverse(s, s + n);
    ll ans = cnt[0];
    for (int i = 0; i != k; ++i)
        ans += cnt[i] * (cnt[i] - 1) / 2;
    return ans;
}

int main(void) {
    ios::sync_with_stdio(0); cin.tie(0);
    #ifndef ONLINE_JUDGE
    ifstream cin("1.in");
    #endif
    cin >> k >> s; n = strlen(s);
    ll r1 = bl();
    ll r2 = count1();
    ll r3 = count2();
    cout << r1 << ' ' << r2 << ' ' << r3 << endl;
    return 0;
}