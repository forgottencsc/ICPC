#include <bits/stdc++.h>
#define N (1<<18)
typedef long long ll;

using namespace std;

//ostream& operator<<(ostream& os, ll l) {
//    string s; bool flg = 0;
//    if (l < 0) flg = 1, l = -l;
//    while (l) { s += (char)(l % 10 + '0'); l /= 10; }
//    if (s.empty()) s = '0';
//    reverse(s.begin(), s.end());
//    if (flg) s = '-' + s;
//    return os << s;
//}

bool pell_root(ll d, ll& x, ll& y) {
    static ll a[20000];
    double s = sqrt(d); ll m = s;
    if (m * m == d) return false;
    ll l = 0, b = m, c = 1; a[l++] = m;
    do {
        c = (d - b * b) / c;
        a[l++] = floor((s + b) / c);
        b = a[l - 1] * c - b;
    } while (a[l - 1] != 2 * a[0]);
    ll p = 1, q = 0;
    for (int i = l - 2; i >= 0; --i)
        swap(p, q), p += q * a[i];
    if (l % 2) x = p, y = q;
    else x = 2 * p * p + 1, y = 2 * p * q;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    #ifndef ONLINE_JUDGE
    ifstream cin("1.in");
    #endif // ONLINE_JUDGE
    cout << boolalpha;
    ll x, y;
    for (int d = 355; d != 600; ++d) {

        if (pell_root(d, x, y))
            cout << x << ' ' << y << ' ' << x * x - d * y * y << endl;
    }
    return 0;
}