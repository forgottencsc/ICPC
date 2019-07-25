#include <bits/stdc++.h>
#include "../generator.h"
using namespace std;

bool do_gen = true;

ofstream* optr;

void gen(int& id, int k, string n) {
    ofstream& cout = *optr;
    //if (!do_gen) { ++id; return; }
    //ofstream cout(to_string(id++) + ".in");
    int nn = n.size();
    cout << nn << ' ' << k << ' ' << n << endl;
    tree t = tg(nn);
    shuffle(t);
    //t.print();
    for (pair<int, int> e : t.g)
        cout << e.first << ' ' << e.second << endl;
    //cout.close();
}

void solve(istream& cin, ostream& cout);

int main(void) {
    int id = 1;
    ofstream out("1.in");
    optr = &out;
    out << 20 << endl;
    gen(id, 12, "245684");
    gen(id, 5, "252525252505050505055020502050205020502");
    gen(id, 25, "252525252505050505055020502050205020502");
    gen(id, 12, "12651000098438000070356870032904851023468200405084597836");
    gen(id, 72, "12605198004387350687329000048501234682475084597836");
    gen(id, igr(1, 100000), sgr(500, '0', '9'));
    gen(id, igr(1, 100000), sgr(500, '0', '9'));
    gen(id, igr(1, 100000), sgr(500, '0', '9'));
    gen(id, igr(1, 100000), sgr(500, '0', '9'));
    gen(id, 1, sgr(1000, '0', '9'));
    gen(id, 12, sgt(1000, "2455680000"));
    gen(id, 11, sgt(1000, "1"));
    gen(id, 4, sgt(5000, "2468000"));
    gen(id, 11, sgr(5000, '0', '9'));
    gen(id, 8316*2, sgt(10000, "224466883"));
    gen(id, 3125, sgt(10000, "500000"));
    gen(id, 65536, sgt(10000, "24680000"));
    gen(id, 83160, sgt(50000, "224466883000"));
    gen(id, 83160, sgt(50000, "22222244444466666688888333333000000000001579"));
    //gen(id, 65536, sgr(50000, '0', '9'));
    gen(id, igr(1, 100000), sgr(50000, '0', '9'));
    //gen(id, igr(1, 100000), sgr(50000, '0', '9'));

    out.close();
    for (int i = 1; i <= id; ++i) {
        ifstream cin(to_string(i) + ".in");
        ofstream dout(to_string(i) + ".out");
        solve(cin, dout);
        //cout << i << endl;
    }

    return 0;
}
