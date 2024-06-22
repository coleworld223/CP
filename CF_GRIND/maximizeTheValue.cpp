// https://codeforces.com/problemset/problem/1906/F

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const int mod = 998244353;
const ll inf = 1e18;

struct cell {
    ll l, r, mx, wh;
    cell () {
        l = r = mx = wh = -inf;
    }
    bool operator == (const cell& oth) {
        return (oth.l == l && oth.r == r && oth.mx == mx && oth.wh == wh);
    }
};
cell def_cell;

cell merge (cell a, cell b) {
    if (a == def_cell) return b;
    cell res;
    res.l = max (a.l, a.wh + b.l);
    res.r = max (b.r, b.wh + a.r);
    res.mx = max ({a.mx, b.mx, a.r + b.l});
    res.wh = a.wh + b.wh;
    return res;
}

// max non empty subarray sum template
ll def_val = 0, def_lzy = 0;
struct Node {
    Node* lft = NULL;
    Node* rht = NULL;
    ll l, r;
    cell val;

    Node (ll _l, ll _r) {
        l = _l;
        r = _r;
    }

    void extend () {
        if (!lft && l + 1 <= r) {
            ll mid = (l + r) >> 1;
            lft = new Node (l, mid);
            rht = new Node (mid + 1, r);
        }
    }

    void upd (ll p, ll v) {
        if (l == r) {
            val.l = val.r = val.mx = v;
            val.wh = v;
            return;
        }
        extend();
        ll mid = (l + r) >> 1;
        if (p <= mid) lft -> upd (p, v);
        else rht -> upd (p, v);
        val = merge (lft -> val, rht -> val);
    }

    cell qry (ll opl, ll opr) {
        if (l >= opl && r <= opr) return val;
        extend();
        ll mid = (l + r) >> 1;
        cell res;
        if (mid >= opl) res = merge (res, lft -> qry (opl, opr));
        if (mid + 1 <= opr) res = merge (res, rht -> qry (opl, opr));
        return res; 
    }
};

void solve () {
    ll n, m;
    cin >> n >> m;

    vector <vector <ll>> r (n + 1), l (n + 1);

    vector <array <ll, 3>> op (m + 1);

    Node* root = new Node (0, m + 1);

    for (ll i = 1; i <= m; i += 1) {
        auto&[x, y, ad] = op[i];
        cin >> x >> y >> ad;
        l[x].push_back(i);
        r[y].push_back(i);
        root -> upd (i, 0);
    } 

    ll q;
    cin >> q;

    vector <vector <array <ll, 3>>> qry (n + 1);

    for (ll i = 1; i <= q; i += 1) {
        ll l, r, k;
        cin >> k >> l >> r;
        qry[k].push_back({l, r, i});
    }

    auto add = [&] (ll x) {
        for (ll i : l[x]) {
            auto[x, y, ad] = op[i];
            root -> upd (i, ad);
        }
    };

    auto rem = [&] (ll x) {
        for (ll i : r[x]) {
            auto [x, y, ad] = op[i];
            root -> upd (i, 0);
        }
    };

    vector <ll> ans (q + 1);

    for (ll x = 1; x <= n; x += 1) {
        add (x);
        for (auto [l, r, i] : qry[x]) {
            cell res = root -> qry (l, r);
            ans[i] = res.mx;
        }
        rem (x);
    }

    for (ll i = 1; i <= q; i += 1) {
        cout << ans[i] << '\n';
    }
    cout << '\n';
}

int main () {
    ios_base::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    int tests = 1;
    // cin >> tests;

    for (int i = 0; i < tests; i += 1) {
        solve ();
    }
}