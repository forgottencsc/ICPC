#include <bits/stdc++.h>
#include "../generator.h"
#define N 1000001
using namespace std;

extern int ans[N];

void kcore();
bool check(istream& cin, istream& cout);
void solve(istream& cin, ostream& cout);

typedef pair<int, int> pii;

struct graph {
    int n;
    vector<pii> g;
};

void write_data(int id, const graph& g) {
    ofstream cout(to_string(id) + ".in");
    cout << g.n << ' ' << g.g.size() << endl;
    for (pii p : g.g)
        cout << p.first << ' ' << p.second << endl;
    cout.close();
}

int per[N];
void shuffle(graph& g) {
    iota(per, per + g.n + 1, 0);
    shuffle(g.g.begin(), g.g.end(), mt);
    for (pii& e : g.g) {
        e.first = per[e.first];
        e.second = per[e.second];
    }
}

pii egr(int nn1, int nn2) {
    int u = igr(1, nn1), v;
    do v = igr(1, nn2); while (v == u);
    return { u, v };
}

graph gen1(int nn, int mm) {
    graph g; g.n = nn;
    while (mm--) g.g.push_back(egr(nn, nn));
    return g;
}

graph gen2(int nn, int mm, int p) {
    graph g; g.n = nn;
    int w = sqrt(nn);
    while (mm--) {
        if (igr(1, 10) < p)
            g.g.push_back(egr(w, nn));
        else
            g.g.push_back(egr(nn, nn));
    }
    return g;
}

graph gen3(int nn, int mm, int p) {
    graph g; g.n = nn;
    int w = cbrt(nn);
    while (mm--) {
        if (igr(1, 100) < p)
            g.g.push_back(egr(w, nn));
        else
            g.g.push_back(egr(nn, nn));
    }
    return g;
}

graph gen4(int nn, int mm, int p) {
    graph g; g.n = nn;
    int w = nn / p;
    for (int i = 1; i <= nn; ++i) {
        for (int j = i + 1; j <= nn; ++j) {
            if (igr(1, 100) >= p) continue;
            g.g.push_back({i,j});
            mm--;
            if (!mm) break;
        }
        if (!mm) break;
    }
    return g;
}

graph gen5(int nn, int mm, int p) {
    graph g; g.n = nn;
    for (int i = 1; i <= nn; ++i) {
        for (int j = 1; j <= nn / 2; ++j) {
            if (igr(1, 100) >= p) continue;
            if (i == j) continue;
            g.g.push_back({ i, j });
        }
    }
    return g;
}

graph gen6(int nn, int mm, int p) {
    graph g; g.n = nn;
    for (int i = 1; i <= sqrt(nn); ++i) {
        for (int j = 1; j <= sqrt(nn); ++j) {
            if (igr(1, 100) >= p) continue;
            if (i == j) continue;
            g.g.push_back({ i, j });
            mm--;
        }
    }
    while(mm > 0) {
        g.g.push_back(egr(sqrt(nn), nn));
        mm--;
    }
    return g;
}

void gen(int id, int nn, int mm, function<graph(int, int)> fn) {
    graph g = fn(nn, mm);
    for (pii& e : g.g) if (e.first > e.second) swap(e.first, e.second);
    sort(g.g.begin(), g.g.end());
    g.g.erase(unique(g.g.begin(), g.g.end()), g.g.end());
    shuffle(g);
    while(g.g.size() > mm) g.g.pop_back();
    write_data(id, g);
    cout << id << " gen0" << endl;
}

void gen_batch(int& id, int nn, int mm, bool f = 1) {
//    gen(++id, nn, mm, bind(gen1, _1, _2));
//    gen(++id, nn, mm, bind(gen1, _1, _2));
//    gen(++id, nn, mm, bind(gen2, _1, _2, 95));
//    gen(++id, nn, mm, bind(gen3, _1, _2, 95));
    if (f) {
//        gen(++id, nn, mm, bind(gen4, _1, _2, 99));
//        gen(++id, nn, mm, bind(gen4, _1, _2, 99));
//        gen(++id, nn, mm, bind(gen4, _1, _2, 99));
//        gen(++id, nn, mm, bind(gen4, _1, _2, 99));
//        gen(++id, nn, mm, bind(gen5, _1, _2, 99));
//        gen(++id, nn, mm, bind(gen5, _1, _2, 99));
        gen(++id, nn, mm, bind(gen5, _1, _2, 99));
        gen(++id, nn, mm, bind(gen5, _1, _2, 99));
        gen(++id, nn, mm, bind(gen5, _1, _2, 99));
//        gen(++id, nn, mm, bind(gen6, _1, _2, 99));
//        gen(++id, nn, mm, bind(gen6, _1, _2, 99));
//        gen(++id, nn, mm, bind(gen6, _1, _2, 99));
//        gen(++id, nn, mm, bind(gen6, _1, _2, 99));
    }
}

int main(void) {

    int id = 3;
    //gen_batch(id, 10, 100);
//    gen_batch(id, 2000, 2000000);
//    gen_batch(id, 5000, 2000000);
    gen_batch(id, 2500, 2000000);
//    gen_batch(id, 100000, 2000000);
    //gen_batch(id, 500000, 2000000, 0);
    //gen_batch(id, 1000000, 5000000);

    clock_t t_s = clock();
    for (int i = 1; i <= id; ++i) {
        gfs(din, dout)
        solve(din, dout);
        cout << i << " gen" << endl;
    }
    cout << clock() - t_s << endl;
    t_s = clock();
    for (int i = 1; i <= id; ++i) {
        cfs(din, dout);
        if (!check(din, dout)) {
            cout << i << " failed" << endl;
        }
        else cout << i << " ok" << endl;
    }
    cout << clock() - t_s << endl;
    return 0;
}


/*
12 28
1 2
1 3
1 4
1 5
1 6
2 3
2 4
2 5
2 6
3 4
3 5
3 6
4 5
4 6
5 6
7 8
8 9
9 10
10 11
11 12
12 7
8 10
10 12
12 8
7 9
9 11
11 7
1 7

11 23
1 2
1 3
1 4
1 5
2 3
2 4
2 5
3 4
3 5
4 5
6 7
7 8
8 9
9 10
10 11
11 6
6 8
8 10
10 6
7 9
9 11
11 7
1 7

16 32
1 2
2 3
3 4
4 5
5 6
6 1
1 3
3 5
5 1
2 4
4 6
6 2
7 8
7 9
7 10
7 11
8 9
8 10
8 11
9 10
9 11
10 11
12 13
12 14
13 14
1 12
7 12
15 16
2 15
3 16
8 15
9 16
*/