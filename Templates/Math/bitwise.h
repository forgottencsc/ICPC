#include <bits/stdc++.h>
#define W 20
using namespace std;

typedef bitset<W> bv;
typedef array<bv, W> bs;

bool ins(bs& b, bv v, bool flg = 1) {
    for (int i = W - 1; i >= 0; --i) {
        if (!v[i]) continue;
        if (!b[i][i]) {
            if (flg) b[i] = v;
            return true;
        }
        else v ^= b[i];
    }
    return false;
}

bs bunion(const bs& b1, const bs& b2) {
    bs r = b1;
    for (int i = 0; i != W; ++i)
        if (b2[i].any()) ins(r,b2[i]);
    return r;
}

bs bitsc(const bs& b1, const bs& b2) {
    bs b = b1, t, r;
    for (int i = W - 1; i >= 0; --i) {
        if (!b2[i][i]) continue;
        bv v = b2[i], k; k[i] = 1; bool f = 1;
        for (int j = W - 1; j >= 0; --j) {
            if (!v[j]) continue;
            if (b[j].any()) v ^= b[j], k ^= t[j];
            else { b[j] = v; t[j] = k; f = 0; break; }
        }
        if (!f) continue;
        bv w;
        for (int j = 0; j != W; ++j)
            if (k[j]) w ^= b2[j];
        ins(r, w);
    }
    return r;
}

bv qmax(const bs& b) {
    bv v;
    for (int i = W - 1; i >= 0; --i)
        if (!v[i] && b[i][i]) v ^= b[i];
    return v;
}