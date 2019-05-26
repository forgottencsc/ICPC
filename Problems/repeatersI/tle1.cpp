#include <bits/stdc++.h>
using namespace std;

int main(void) {
    int n; cin >> n;
    vector<string> vs;
    while(n--) {
        string s; cin >> s;
        int l = s.size(), a1 = 0, a2 = 0;
        for (const string& t : vs) {
            if (t.size() < l) continue;
            if (t.substr(0, l) == s)
                a1++;
            if (t.substr(t.size() - l, l) == s)
                a2++;
        }
        vs.push_back(s);
        cout << a1 << ' ' << a2 << endl;
    }
    return 0;
}