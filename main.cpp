#include <bits/stdc++.h>
#define N 100001
using namespace std;

typedef long long ll;
typedef vector<ll> vec;
typedef vector<vec> mat;

int main(void) {
    ios::sync_with_stdio(0); cin.tie(0);
    #ifndef ONLINE_JUDGE
    ifstream cin("1.in");
    #endif // ONLINE_JUDGE

    int n1, n2; cin >> n1 >> n2;
    mat a(n1, vec(n2));
    for (int i = 0; i != n1; ++i)
        for (int j = 0; j != n2; ++j)
            cin >> a[i][j];

    if (n1 > n2) {
        mat r(n2, vec(n1));
        for (int i = 0; i != n1; ++i)
            for (int j = 0; j != n2; ++j)
                r[j][i] = a[i][j];
        a = move(r);
        swap(n1, n2);
    }

    vec rs(n1, 0), cs(n2, 0);
    for (int i = 0; i != n1; ++i)
        for (int j = 0; j != n2; ++j)
            rs[i] += a[i][j], cs[j] += a[i][j];

    ll ans = 0, res = 0;

    priority_queue<ll, vector<ll>, greater<ll>> pq;
    for (int i = 0; i != n1; ++i) {
        pq.push(rs[i]);
        if (pq.size() > 4) pq.pop();
    }

    res = 0;
    while (!pq.empty()) res += pq.top(), pq.pop();
    ans = max(ans, res);

    for (int j = 0; j != n2; ++j) {
        for (int i = 0; i != n1; ++i)
            rs[i] -= a[i][j];
        for (int i = 0; i != n1; ++i) {
            pq.push(rs[i]);
            if (pq.size() > 3) pq.pop();
        }
        res = cs[j];
        while (!pq.empty()) res += pq.top(), pq.pop();
        ans = max(ans, res);
        for (int i = 0; i != n1; ++i)
            rs[i] += a[i][j];
    }

    for (int i1 = 0; i1 != n1 - 1; ++i1) {
        for (int i2 = i1 + 1; i2 != n1; ++i2) {
            for (int j = 0; j != n2; ++j)
                cs[j] -= (a[i1][j] + a[i2][j]);
            for (int j = 0; j != n2; ++j) {
                pq.push(cs[j]);
                if (pq.size() > 2) pq.pop();
            }
            res = rs[i1] + rs[i2];
            while (!pq.empty())
                res += pq.top(), pq.pop();
            ans = max(ans, res);
            for (int j = 0; j != n2; ++j)
                cs[j] += (a[i1][j] + a[i2][j]);
        }
    }

    for (int i = 0; i != n1; ++i) {
        for (int j = 0; j != n2; ++j)
            cs[j] -= a[i][j];
        for (int j = 0; j != n2; ++j) {
            pq.push(cs[j]);
            if (pq.size() > 3) pq.pop();
        }
        res = rs[i];
        while (!pq.empty()) res += pq.top(), pq.pop();
        ans = max(ans, res);
        for (int j = 0; j != n2; ++j)
            cs[j] += a[i][j];
    }

    for (int i = 0; i != n2; ++i) {
        pq.push(cs[i]);
        if (pq.size() > 4) pq.pop();
    }

    res = 0;
    while (!pq.empty()) res += pq.top(), pq.pop();
    ans = max(ans, res);

    cout << ans << endl;

    return 0;
}
