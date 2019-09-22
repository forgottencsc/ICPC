int convex_hull(vec* p, int n, vec* c) {
    sort(p + 1, p + n + 1); n = unique(p + 1, p + n + 1) - p - 1;
    int m = 0;
    c[1] = p[++m];
    for (int i = 1; i <= n; ++i) {
        while (m > 1 && sgn(crx(c[m - 1], c[m], p[i])) != 1) m--;
        c[++m] = p[i];
    }
    int t = m;
    for (int i = n - 1; i; --i) {
        while (m > t && sgn(crx(c[m - 1], c[m], p[i])) != 1) m--;
        c[++m] = p[i];
    }
    if (m > 1) m--; c[m + 1] = c[1]; return m;
}

dbl rotating_calipers(vec* c, int n) {
    #define nxt(x) ((x)==n?1:(x)+1)
    for (int p = 1, q1 = 1, q2 = 1, q3 = 1; p <= n; ++p) {
        line l = { c[p], c[nxt(p)] - c[p] };
        while (sgn(l.v*(c[nxt(q1)]-c[q1]))!=-1) q1 = nxt(q1);
        while (sgn(l.v^(c[nxt(q2)]-c[q2]))!=-1) q2 = nxt(q2);
        if (p == 1) q3 = q2;
        while (sgn(l.v*(c[nxt(q3)]-c[q3]))!=1) q3 = nxt(q3);
        //  ...
    }
    #undef nxt
    return ans;
}

bool judge(line l0, line l1, line l2) { return sgn((litsc(l1, l2)-l0.p)^l0.v)==1; }
int halfplane_intersection(line* lv, int n, vec* pv) {
    static pair<pair<dbl,dbl>, int> a[N];
    for (int i = 1; i <= n; ++i)
        a[i] = { { arg(lv[i].v), lv[i].p*univ(arg(lv[i].v)-pi/2) }, i };
    sort(a + 1, a + n + 1);
    static int b[N], q[N]; int w = 0, l = 1, r = 0;
    for (int i = 1; i <= n; ++i)
        if (i == 1 || sgn(a[i].first.first-a[i-1].first.first))
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

int minkowski_sum(vec* cv1, int n1, vec* cv2, int n2, vec* cv) {
    if (n1 == 1 || n2 == 1) {
        if (n1 == 1) swap(n1, n2), swap(cv1, cv2);
        for (int i = 1; i <= n1; ++i)
            cv[i] = cv1[i] + cv2[1];
        return n1;
    }
    static vec dv1[N], dv2[N], dv;
    cv1[n1 + 1] = cv1[1]; cv2[n2 + 1] = cv2[1];
    for (int i = 1; i <= n1; ++i) dv1[i] = cv1[i + 1] - cv1[i];
    for (int i = 1; i <= n2; ++i) dv2[i] = cv2[i + 1] - cv2[i];
    int m = 0; cv[++m] = cv1[1] + cv2[1];
    int p1 = 1, p2 = 1;
    while (p1 <= n1 || p2 <= n2) {
        if (p1 <= n1 && p2 <= n2)
            dv = (sgn((dv1[p1])^(dv2[p2]))!=-1?dv1[p1++]:dv2[p2++]);
        else if (p1 <= n1)
            dv = dv1[p1++];
        else
            dv = dv2[p2++];
        while (m > 1 && !sgn((cv[m] - cv[m - 1]) ^ dv)) {
            dv = dv + cv[m] - cv[m - 1];
            m--;
        }
        cv[m + 1] = cv[m] + dv;
        m++;
    }
    if (m > 1) m--; return m;
}


typedef long long ll;
typedef pair<dbl, int> pdi;
const dbl inf = 1e10;
namespace cvq {
    vec c[N];
    int w, n;

    void init(vec* cv, int m) {
        copy_n(cv + 1, m, c); n = m;
        rotate(c, min_element(c, c + n), c + n);
        c[n] = c[0]; c[n + 1] = c[1];
        w = 0; while (c[w] < c[w + 1]) ++w;
    }

    //  0：在凸包外，1：在凸包上或凸包内
    int contain(vec p) {
        if (p.x < c[0].x || c[w].x < p.x) return false;
        if (crx(c[0], c[w], p) > 0) {
            int e = lower_bound(c + w, c + n + 1, vec{ p.x, inf }, greater<vec>()) - c;
            if (!sgn(p.x - c[e].x)) return p.y <= c[e].y;
            else return crx(c[e - 1], c[e], p) >= 0;
        }
        else {
            int e = lower_bound(c, c + w + 1, vec{ p.x, -inf }) - c;
            if (!sgn(p.x - c[e].x)) return p.y >= c[e].y;
            else return crx(c[e - 1], c[e], p) >= 0;
        }
    }

    pdi crxmax0(int l, int r, vec p) {
        int r0 = r;
        while (l <= r) {
            int m = (l + r) >> 1;
            if ((p ^ (c[m + 1] - c[m])) >= 0) l = m + 1;
            else r = m - 1;
        }
        return pdi(p^c[l],l % n);
    }

    pdi crxmax(vec p) {
        pdi res = p.x <= 0 ? crxmax0(0, w - 1, p) : crxmax0(w, n - 1, p);
        return max({ res, pdi(p ^ c[0], 0), pdi(p ^ c[w], w) });
    }
    pdi crxmin(vec p) { return crxmax(p * -1); }

    bool ltan(vec p, int i) { return crx(p,c[i],i?c[i-1]:c[n-1])<=0&&crx(p,c[i],c[i+1])<=0; }
    bool rtan(vec p, int i) { return crx(p,c[i],i?c[i-1]:c[n-1])>=0&&crx(p,c[i],c[i+1])>=0; }

    int ltan(int l, int r, vec p) {
        if (ltan(p, r)) return r; r--;
        while (l <= r) {
            int m = (l + r) >> 1;
            if (crx(p,c[m],c[m+1])<0) r = m - 1;
            else l = m + 1;
        }
        return l;
    }

    int rtan(int l, int r, vec p) {
        if (rtan(p, r)) return r; l++;
        while (l <= r) {
            int m = (l + r) >> 1;
            if (crx(p,c[m],m?c[m - 1]:c[n - 1])>0) l = m + 1;
            else r = m - 1;
        }
        return r;
    }

    bool tangent(vec p, int& lp, int& rp) {
        if (contain(p)) return false;
        if (p.x < c[0].x) { lp = ltan(w, n, p); rp = rtan(0, w, p); }
        else if (p.x > c[w].x) { lp = ltan(0, w, p); rp = rtan(w, n, p); }
        else if (crx(c[0], c[w], p) > 0) {
            int e = lower_bound(c + w, c + n + 1, p, greater<vec>()) - c;
            lp = ltan(w, e, p); rp = rtan(e, n, p);
        }
        else {
            int e = lower_bound(c + 0, c + w + 1, p) - c;
            lp = ltan(0, e, p); rp = rtan(e, w, p);
        }
        lp %= n; rp %= n;
        return true;
    }

    int secant0(line s, int l, int r) {
        while (l <= r) {
            int m = (l + r) >> 1;
            if (crx(s.p, s.p+s.v, c[m%n]) <= 0) r=m-1;
            else l = m + 1;
        }
        return r % n;
    }

    bool secant(line s, int& p1, int& p2) {
        pdi lc = crxmax(s.v), rc = crxmin(s.v);
        int lp = lc.second, rp = rc.second;
        if (crx(s.p, s.p + s.v, c[lp]) * crx(s.p, s.p + s.v, c[rp]) > 0)
            return false;
        p1 = secant0(s, lp, rp < lp ? rp + n : rp);
        p2 = secant0({ s.p, s.v * -1 }, rp, lp < rp ? lp + n : lp);
        return true;
    }
};
