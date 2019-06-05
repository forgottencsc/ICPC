#include <bits/stdc++.h>
#include <functional>
using namespace std;

int main(void) {

    string s, t;
    cin >> s >> t;
    size_t pos = 0;
    while(pos != string::npos) {
        pos = s.find(t, pos);
        if (pos != string::npos)
            cout << ++pos << ' ';
    }
    return 0;
}