
const dbl mm = 1e9;

mt19937_64 mt(time(0));

int ui(int l, int r) { return uniform_int_distribution<int>(l, r)(mt);}

dbl ud(dbl l = -mm, dbl r = mm) {
    uniform_real_distribution<dbl> urd(l, r);
    return urd(mt);
}

vec up(dbl m = mm) { return { ud(-m, m), ud(-m, m) }; }

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
    dbl r = ud(1, 1e9);
    for (int i = 0; i != n; ++i) {
        pv[i + 1] = univ(fv[i]) * r;
        //pv[i + 1].x = round(pv[i + 1].x);
        //pv[i + 1].y = round(pv[i + 1].y);
    }
    return convex_hull(pv, n, cv);
}

vec cv[N];

pair<dbl, int> crxmax(vec p, int n) {
    pair<dbl, int> res = { -DBL_MAX, -1 };
    for (int i = 0; i != n; ++i)
        res = max(res, pair<dbl, int>(p ^ cvq::c[i], i));
    return res;
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
