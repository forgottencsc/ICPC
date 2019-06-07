#include <bits/stdc++.h>
#define N 1000002
using namespace std;
typedef long long ll;

char s[N], t[N]; ll p;
int n, m, r[N];
void getr() {
    n = strlen(s); m = 2 * n + 1; memset(t, '#', m);
    for (int i = 0; i != n; ++i) t[2 * i + 1] = s[i];
    for (int i = 1, p = 0, w = 0; i != m; ++i) {
        int j = (i>p+w ? 0 : min(r[p-(i-p)], p+w-i));
        while(0<=i-j-1 && i+j+1<m && t[i-j-1]==t[i+j+1]) ++j;
        r[i] = j; if (i + j > p + w)  p = i, w = j;
    }
}

bool ispal(int l, int u) {
    return r[l + u] >= u - l;
}

ll getval(int l, int u) {
    ll val = 0;
    for (int i = l; i != u; ++i)
        val = (val * 10 + (s[i] - '0')) % p;
    return val;
}


int main(void) {
    ios::sync_with_stdio(0); cin.tie(0);
    #ifndef ONLINE_JUDGE
    ifstream cin("9.in");
    #endif // ONLINE_JUDGE
    cin >> s >> p; getr();
    unordered_set<string> st;

    ll ans = 0;
    for (int i = 0; i != n - 1; ++i) {
        for (int j = i + 1; j <= n; ++j) {
            if (ispal(i, j)) {
                ll w = getval(i, j);
                //cout << w << endl;
                if (st.insert(string(s + i, s + j)).second)
                    ans = (ans + w) % p;
            }
        }
    }

    cout << ans << endl;
    return 0;
}
