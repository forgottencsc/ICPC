int convex_hull(vec* p, int n, vec* c) {
    sort(p + 1, p + n + 1); int m = 0, t;
    c[1] = p[++m];
    for (int i = 1; i <= n; ++i) {
        while (m > 1 && dc(crx(c[m - 1], c[m], p[i])) != 1) m--;
        c[++m] = p[i];
    }
    t = m;
    for (int i = n - 1; i; --i) {
        while (m > t && dc(crx(c[m - 1], c[m], p[i])) != 1) m--;
        c[++m] = p[i];
    }
    return m - (n > 1);
}

dbl rotating_calipers(vec* c, int n) {
    #define nxt(x) ((x)==n?1:(x)+1)
    for (int p = 1, q1 = 1, q2 = 1, q3 = 1; p <= n; ++p) {
        line l = { c[p], c[nxt(p)] - c[p] };
        while (dc(l.v*(c[nxt(q1)]-c[q1]))!=-1) q1 = nxt(q1);
        while (dc(l.v^(c[nxt(q2)]-c[q2]))!=-1) q2 = nxt(q2);
        if (p == 1) q3 = q2;
        while (dc(l.v*(c[nxt(q3)]-c[q3]))!=1) q3 = nxt(q3);
        //  ...
    }
    #undef nxt
    return ans;
}

bool judge(line l0, line l1, line l2) { return dc((litsc(l1, l2)-l0.p)^l0.v)==1; }
int halfplane_intersection(line* lv, int n, vec* pv) {
    static pair<pair<dbl,dbl>, int> a[N];
    for (int i = 1; i <= n; ++i)
        a[i] = { { arg(lv[i].v), lv[i].p*univ(arg(lv[i].v)-pi/2) }, i };
    sort(a + 1, a + n + 1);
    static int b[N], q[N]; int w = 0, l = 1, r = 0;
    for (int i = 1; i <= n; ++i)
        if (i == 1 || dc(a[i].first.first-a[i-1].first.first))
            b[++w] = a[i].second;
    for (int i = 1; i <= w; ++i) {
        while (l<r&&judge(lv[b[i]],lv[q[r]],lv[q[r-1]]))--r;
        while (l<r&&judge(lv[b[i]],lv[q[l]],lv[q[l+1]]))++l;
        q[++r]=b[i];
    }
    while(l<r&&judge(lv[q[l]],lv[q[r]],lv[q[r-1]]))--r;
    while(l<r&&judge(lv[q[r]],lv[q[l]],lv[q[l+1]]))++l;
    if (r <= l + 1) return 0;
    int m = 0; q[r+1]=q[l];
    for (int i = l; i <= r; ++i)
        pv[++m]=litsc(lv[q[i]],lv[q[i+1]]);
    return m;
}


int convex_hull(vec* p, int n, vec* c) {
    sort(p + 1, p + n + 1);
    int m = 0;
    c[1] = p[++m];
    for (int i = 1; i <= n; ++i) {
        while (m > 1 && dc(crx(c[m - 1], c[m], p[i])) != 1) m--;
        c[++m] = p[i];
    }
    int t = m;
    for (int i = n - 1; i; --i) {
        while (m > t && dc(crx(c[m - 1], c[m], p[i])) != 1) m--;
        c[++m] = p[i];
    }
    return m - (m > 1);
}

int minkowski_sum(vec* cv1, int n1, vec* cv2, int n2, vec* cv) {
    static vec dv1[N], dv2[N], dv;
    cv1[n1 + 1] = cv1[1]; cv2[n2 + 1] = cv2[1];
    for (int i = 1; i <= n1; ++i) dv1[i] = cv1[i + 1] - cv1[i];
    for (int i = 1; i <= n2; ++i) dv2[i] = cv2[i + 1] - cv2[i];
    int m = 0; cv[++m] = cv1[1] + cv2[1];
    int p1 = 1, p2 = 1;
    while (p1 <= n1 && p2 <= n2)
        ++m, cv[m] = cv[m - 1] + (dc((dv1[p1])^(dv2[p2]))!=-1?dv1[p1++]:dv2[p2++]);
    while (p1 <= n1)
        ++m, cv[m] = cv[m - 1] + dv1[p1++];
    while (p2 <= n2)
        ++m, cv[m] = cv[m - 1] + dv2[p2++];
    assert(cv[m].x == cv[1].x && cv[m].y == cv[1].y);
    return m - 1;
}

namespace cvq {
    vec c[M], lw[M], up[M];
    int n, n1, n2;

    void build(vec* cv, int n_) {
        copy(cv + 1, cv + n_ + 1, c); n = n_;
        int p = 0;
        for (int i = 1; i != n; ++i)
            if (c[p]<c[i]) p = i;
        copy(c, c + p + 1, lw);
        copy(c + p, c + n, up); up[n] = c[0];
        n1 = p + 1; n2 = n - p + 1;
    }

    pair<dbl, int> get_tangent(vec* cv, int n, vec p) {
        int l = 0, r = n - 2;
        while(l+1<r) {
            int m = (l+r)/2;
            if (dc((cv[m+1]-cv[m])^p)==1)r=m;
            else l = m;
        }
        pair<dbl,int> p1(p^cv[r],r),p2(p^cv[0],0);
        return max(p1, p2);
    }

    void upd_tangent(vec p, int id, int& i0, int& i1) {
        if (dc(crx(p,c[i0],c[id]))==1) i0=id;
        if (dc(crx(p,c[i1],c[id]))==-1) i1=id;
    }

    void bin_search(int l, int r, vec p, int& i0, int &i1) {
        if (l == r) return;
        upd_tangent(p, l % n, i0, i1);
        int sl = dc(crx(p,c[l%n],c[(l+1)%n]));
        while(l+1<r){
            int m = (l + r) / 2;
            int sm = dc(crx(p, c[m%n], c[(m+1)%n]));
            if (sm == sl) l = m;
            else r = m;
        }
        upd_tangent(p, r % n, i0 , i1);
    }

    bool contain(vec p) {
        if (p.x<lw[0].x||p.x>up[0].x) return false;
        int id = lower_bound(lw, lw + n1, vec{p.x,-inf})-lw;
        if (!dc(lw[id].x-p.x)) {
            if (dc(lw[id].y-p.y)==1)
                return false;
        }
        else if (dc(crx(p,lw[id-1],lw[id]))==-1)
            return false;
        id = lower_bound(up, up + n2, vec{ p.x, inf }, greater<vec>())-up;
        if (!dc(up[id].x-p.x)) {
            if (dc(up[id].y-p.y)==-1)
                return false;
        }
        else if (dc(crx(p,up[id-1],up[id]))==-1)
            return false;
        return true;
    }

    bool get_tangent(vec p, int& i0, int& i1) {
        if (contain(p)) return false;
        i0 = i1 = 0;
        int id = lower_bound(lw, lw + n1, p) - lw;
        bin_search(0, id, p, i0, i1);
        bin_search(id, n1, p, i0, i1);
        id = lower_bound(up, up + n2, p, greater<vec>()) - up;
        bin_search(n1 - 1, n1 - 1 + id, p, i0, i1);
        bin_search(n1 - 1 + id, n1 - 1 + n2, p, i0, i1);
        return true;
    }

    pair<dbl, int> get_crxmax(vec p) {
        pair<dbl, int> r = get_tangent(up, n2, p);
        r.second += n1 - 1;
        r = max(r, get_tangent(lw, n1, p));
        return r;
    }

//    bool get_itsc(line l, int& i0, int& i1) {
//        int p0 = get_crxmax(u - v), p1 = get_crxmax(v - u);
//        if (dc(crx(u,v,c[p0]))*dc(crx(u,v,c[p1]))>=0)
//            return false;
//        if (p0 > p1) swap(p0, p1);
//        i0 = binary_search(u, v, p0, p1);
//        i1 = binary_search(u, v, p1, p0 + n);
//        return true;
//    }

}
