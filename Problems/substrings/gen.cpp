#include <bits/stdc++.h>
#include "../generator.h"
using namespace std;

void gen(int& id, int k, string n) {
    ofstream cout(to_string(id++) + ".in");
    cout << k << ' ' << n << endl;
    cout.close();
}

void solve(istream& cin, ostream& cout);

int check(istream& cin, istream& cout);

int main1(void) {
    int id = 1;
    gen(id, 12, "245684");
    gen(id, 5, "252525252505050505055020502050205020502");
    gen(id, 25, "252525252505050505055020502050205020502");
    gen(id, 3, "12000006500198430087356807329040501034682004750084597836");
    gen(id, 12, "12651000098438000070356870032904851023468200405084597836");
    gen(id, 72, "12605198004387350687329000048501234682475084597836");
    gen(id, igr(1, 100000), sgr(800, '0', '9'));
    gen(id, igr(1, 100000), sgr(800, '0', '9'));
    gen(id, igr(1, 100000), sgr(800, '0', '9'));
    gen(id, igr(1, 100000), sgr(800, '0', '9'));
    gen(id, igr(1, 100000), sgr(800, '0', '9'));
    gen(id, 1, sgr(100000, '0', '9'));
    gen(id, 12, sgt(100000, "2455680000"));
    gen(id, 24, sgt(100000, "2455680000"));
    gen(id, 20, sgt(100000, "2455680000"));
    gen(id, 11, sgt(100000, "01"));
    gen(id, 4, sgt(100000, "200000"));
    gen(id, 11, sgr(100000, '0', '9'));
    gen(id, 3125, sgt(100000, "500000"));
    gen(id, 250000, sgt(100000, "500000"));
    gen(id, 735134400, sgr(100000, '0', '9'));
    gen(id, 735134400, sgt(100000, "23468"));
    gen(id, 735134400 / 2, sgr(100000, '0', '9'));
    gen(id, 735134400 / 3, sgt(100000, "24680"));
    gen(id, 735134400 / 2, sgr(100000, '0', '9'));
    gen(id, 735134400 / 3, sgt(100000, "24680000000"));
    gen(id, igr(1, 1000000000), sgr(100000, '0', '9'));
    gen(id, igr(1, 1000000000), sgr(100000, '0', '9'));
    gen(id, igr(1, 1000000000), sgr(100000, '0', '9'));
    gen(id, igr(1, 1000000000), sgr(100000, '0', '9'));

    for (int i = 1; i < id; ++i) {
        ifstream cin(to_string(i) + ".in");
        ofstream out(to_string(i) + ".out");
        solve(cin, out);
        cout << i << endl;
    }

//    for (int i = 1; i <= id; ++i) {
//        ifstream cin(to_string(i) + ".in");
//        ifstream out(to_string(i) + ".out");
//        cout << (int)(check(cin, out)) << endl;
//    }

    return 0;
}