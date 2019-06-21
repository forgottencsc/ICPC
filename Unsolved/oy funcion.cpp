#include <bits/stdc++.h>
#define N 10000000
using namespace std;

bool ip[N];
vector<int> ps;
int f[N];
typedef long long ll;
ll s[N];
void euler_sieve() {
    ps.reserve(N / log(N) * 1.2);
    memset(ip, 1, sizeof(ip)); ip[1] = 0;
    f[1] = s[1] = 1;
    for (int i = 2; i != N; ++i) {
        if (ip[i]) {
            ps.push_back(i);
            f[i] = i - 2;
        }
        for (int p : ps) {
            if (i * p >= N) break;
            ip[i * p] = 0;
            if (i % p) {
                f[i * p] = f[i] * (p - 2);
            }
            else {
                if((i / p) % p)
                    f[i * p] = f[i / p] * (p - 1) * (p - 1);
                else
                    f[i * p] = f[i] * p;
                break;
            }
        }
        s[i] = s[i - 1] + f[i];
    }
}


int main(void) {
    ios::sync_with_stdio(0); cin.tie(0);
    #ifndef ONLINE_JUDGE
    ifstream cin("1.in");
    #endif // ONLINE_JUDGE
    euler_sieve();

    int T; cin >> T;
    while(T--) {
        int n; cin >> n; ll res = 0;
        for (int l = 1, r; l <= n; l = r + 1) {
            r = n / (n / l);
            res += (s[r] - s[l - 1]) * (n / l) * (n / l);
        }
        cout << res << endl;
    }

    return 0;
}