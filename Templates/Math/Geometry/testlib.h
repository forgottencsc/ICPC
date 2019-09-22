
const dbl mm = 1e6;

mt19937_64 mt(time(0));

int ui(int l, int r) { return uniform_int_distribution<int>(l, r)(mt);}

dbl ud(dbl l = -mm, dbl r = mm) {
    uniform_real_distribution<dbl> urd(l, r);
    return urd(mt);
}

vec up(dbl m = mm) { return { round(ud(-m, m)), round(ud(-m, m)) }; }

bool is_convex(vec* pv, int n) {
    pv[n + 1] = pv[1];
    pv[n + 2] = pv[2];
    for (int i = 1; i <= n; ++i) {
        if (sgn(crx(pv[i], pv[i + 1], pv[i + 2])) < 0)
            cout << crx(pv[i], pv[i + 1], pv[i + 2]) << endl;
    }
    return true;
}

int uc(vec* cv, int n) {
    static vec pv[N];
    vector<dbl> fv(n);
    for (int i = 0; i != n; ++i)
        fv[i] = ud(0, 2 * pi);
    sort(fv.begin(), fv.end());
    rotate(fv.begin(), fv.begin() + ui(0, n - 1), fv.end());
    dbl r = ud(1, mm);
    bool rec = (ui(0, 2) == 0);
    for (int i = 0; i != n; ++i) {
        pv[i + 1] = univ(fv[i]) * r;
        pv[i + 1].x = round(pv[i + 1].x);
        pv[i + 1].y = round(pv[i + 1].y);
    }
    return convex_hull(pv, n, cv);
}

pair<dbl, int> crxmax1(vec p) {
    pair<dbl, int> res = { -DBL_MAX, -1 };
    for (int i = 0; i != cvq::n; ++i)
        res = max(res, pair<dbl, int>(p ^ cvq::c[i], i));
    return res;
}

bool chk_cont(vec* cv, int n, vec p) {
    for (int i = 0; i != n; ++i)
        if (sgn(crx(cv[i], cv[i + 1], p)) < 0)
            return false;
    return true;
}

bool chk_ltan(vec* cv, int n, vec p, vec q) {
    for (int i = 0; i != n; ++i)
        if (crx(p, q, cv[i]) > 0)
            return false;
    return true;
}

bool chk_rtan(vec* cv, int n, vec p, vec q) {
    for (int i = 0; i != n; ++i)
        if (crx(p, q, cv[i]) < 0)
            return false;
    return true;
}

bool chk_sec(vec* cv, int lp, line l) {
    return lsitsc({ cv[lp], cv[lp + 1] }, l);
}

int tc = 0;

vec cv[N], pv[N]; dbl ans[N];

bool chk_crxmax(int n, int m) {
    bool fail = 0;
    n = uc(cv, n);
    assert(is_convex(cv, n));
    cvq::init(cv, n);
    for (int i = 1; i <= m; ++i) {
        pv[i] = up();
        auto r1 = crxmax1(pv[i]), r2 = cvq::crxmax(pv[i]);
        assert((pv[i] ^ cvq::c[r1.second]) == r1.first);
        assert((pv[i] ^ cvq::c[r2.second]) == r2.first);
        if (r1 != r2) {
            if (r1.first - r2.first)
                fail = 1;
            cout << r1.first - r2.first << ' ' << r1.second << ' ' << r2.second << endl;
        }
//        ans[i] = crxmax1(pv[i]).first;
//        dbl diff = ans[i] - cvq::crxmax(pv[i]).first;
//        if (diff != 0)
//            cout << diff <<endl;
    }
    if (fail) {
        ++tc;
        ofstream os1(to_string(tc) + ".fi");
        ofstream os2(to_string(tc) + ".fo");
        os1 << n << ' ' << m << endl;
        for (int i = 1; i <= n; ++i) {
            os1 << cv[i].x << ' ' << cv[i].y << endl;
        }
        for (int i = 1; i <= m; ++i) {
            os1 << pv[i].x << ' ' << pv[i].y << endl;
            os2 << ans[i] << endl;
        }
    }
    return !fail;
}

bool chk_tan(int n, int m) {bool fail = 0;
    n = uc(cv, n);
    cvq::init(cv, n);
    for (int i = 1; i <= m; ++i) {
        pv[i] = up();
        int lp, rp;
        if (!cvq::tangent(pv[i], lp, rp)) {
            if (!chk_cont(cvq::c, n, pv[i]))
                fail = 1;
        }
        else {
            if (!chk_ltan(cvq::c, n, pv[i], cvq::c[lp]))
                fail = 1;
            if (!chk_rtan(cvq::c, n, pv[i], cvq::c[rp]))
                fail = 1;
        }
    }
    if (fail) {
        ++tc;
        ofstream os1(to_string(tc) + ".fi");
        ofstream os2(to_string(tc) + ".fo");
        os1 << n << ' ' << m << endl;
        for (int i = 1; i <= n; ++i) {
            os1 << cv[i].x << ' ' << cv[i].y << endl;
        }
        for (int i = 1; i <= m; ++i) {
            os1 << pv[i].x << ' ' << pv[i].y << endl;
        }
    }
    return !fail;
}

line lv[N];
bool chk_sec(int n, int m) {
    n = uc(cv, n);
    cvq::init(cv, n);
    bool fail = 0;
    for (int i = 1; i <= m; ++i) {
        lv[i].p = up();
        lv[i].v = up();
        int p1, p2;
        if (cvq::secant(lv[i], p1, p2)) {
            if (!chk_sec(cvq::c, p1, lv[i]))
                fail = 1;
            if (!chk_sec(cvq::c, p2, lv[i]))
                fail = 1;
        }
    }
    if (fail) {
        ++tc;
        ofstream os1(to_string(tc) + ".fi");
        ofstream os2(to_string(tc) + ".fo");
        os1 << n << ' ' << m << endl;
        for (int i = 1; i <= n; ++i) {
            os1 << cv[i].x << ' ' << cv[i].y << endl;
        }
        for (int i = 1; i <= m; ++i) {
            os1 << lv[i].p.x << ' ' << lv[i].p.y << ' ';
            os1 << lv[i].v.x << ' ' << lv[i].v.y << endl;
        }
    }
    return !fail;
}

void check() {
    const int n = 1000, m = 1000;
    int succ = 0, w = 0;
    while(tc <= 2) {
        ++w;
        bool f = 1;
        if (w % 3 == 1) {
            f = chk_sec(n,m);
        }
        else if (w % 3 == 2){
            f = chk_tan(n, m);
        }
        else {
            f = chk_crxmax(n, m);
        }
        if (!f)
            cout << "Failed: " << tc <<endl;
        else succ++;
        if (succ % 100 == 0)
            cout << "Success: " << succ << endl;
    }
}
