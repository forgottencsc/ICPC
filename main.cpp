#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
vector<vector<int>> solve(ll n, ll k) {
    vector<vector<int>> v(k);
    if (k == 1) {
        v[0].resize(n);
        iota(v[0].begin(), v[0].end(), 1);
    }
    else if (n * (n + 1) / 2 % k || (n + 1) <= 2 * k)
        v.clear();
    else {
        if (n / k % 2 == 0) {
            for (int i = 0; i != k; ++i)
                for (int j = 0; j != n / k; ++j)
                    v[i].push_back((j * k  + ((j & 1) ? i : k - i - 1)) + 1);
        }
        else {
            if (n / k % k == 0) {
                for (int i = 0; i != k; ++i)
                    for (int j = 0; j != n / k; ++j)
                        v[i].push_back((j * k + ((j + i) % k)) + 1);
            }
            else {
                if (k % 2) {
                    for (int i = 0; i != k; ++i) {
                        v[i].push_back(i + 1);
                        int j;
                        if (i <= k / 2) j = k / 2 - i;
                        else j = 3 * k / 2 - i;
                        v[i].push_back(k + (k - j - 1) + 1);
                        int d = i - j;
                        v[i].push_back(2 * k + k / 2 - d + 1);
                    }
                    for (int i = 0; i != k; ++i)
                        for (int j = 3; j != n / k; ++j)
                            v[i].push_back((j * k  + ((j & 1) ? i : k - i - 1)) + 1);
                }
            }
        }
    }
//    if (v.size()) {
//        ll sum = n * (n + 1) / (2 * k);
//        for (int i = 0; i != k; ++i) {
//            ll ans = 0;
//            for (int j = 0; j != n / k; ++j)
//                ans += v[i][j];
//            if (ans != sum) {
//                cout << n << ' ' << k << endl;
//                for (int u = 0; u != k; ++u)
//                    for (int w = 0; w != n / k; ++w)
//                        cout << v[u][w] << " \n"[w == n / k - 1];
//                cout.flush();
//                exit(114514);
//            }
//        }
//    }
    return v;
}

int main(void) {
    #ifndef ONLINE_JUDGE
    freopen("1.in", "r", stdin);
    #endif // ONLINE_JUDGE

    int T; scanf("%d", &T);
    while(T--) {
        ll n, k; scanf("%lld%lld", &n, &k);
        vector<vector<int>> v = solve(n, k);
        if (!v.size()) printf("no\n");
        else {
            printf("yes\n");
            for (int i = 0; i != k; ++i)
                for (int j = 0; j != n / k; ++j)
                    printf("%d%c", v[i][j], " \n"[j == n / k - 1]);
        }

    }


    return 0;
}
