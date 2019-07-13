#include <bits/stdc++.h>
typedef double dbl;
const dbl pi = acos(-1), eps = 1e-8;

struct vec { dbl x, y; };
vec operator+(vec v1, vec v2) { return { v1.x + v2.x, v1.y + v2.y }; }
vec operator-(vec v1, vec v2) { return { v1.x - v2.x, v1.y - v2.y }; }
dbl operator*(vec v1, vec v2) { return v1.x * v2.x + v1.y * v2.y; }
dbl operator^(vec v1, vec v2) { return v1.x * v2.y - v1.y * v2.x; }
vec operator*(dbl k, vec v) { return { k * v.x, k * v.y }; }


vector<vec> convex_hull(vector<vec>& ps) {
    swap(ps[0], *min_element(ps.begin(), ps.end(), [](vec v1, vec v2)
        {return v1.x==v2.x?v1.y<v2.y:v1.x<v2.x; }));
    sort(ps.begin()+1, ps.end(), [&](vec v1, vec v2){v1=v1-ps[0];v2=v2-ps[0];
        return (v1^v2)==0?v1*v1<v2*v2:(v1^v2)>0;});
    vector<vec> res = { ps[0], ps[1] };
    for (int i = 2; i != ps.size(); ++i) {
        while(((res.back()-res.end()[-2])^(ps[i]-res.back()))<0)
            res.pop_back();
        res.push_back(ps[i]);
    }
    return res;
}