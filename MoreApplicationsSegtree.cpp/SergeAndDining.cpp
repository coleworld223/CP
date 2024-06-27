#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const ll inf = 1e18;

ll def = 0;
struct cell {
    ll v;
    cell() {
        v = 0;
    }
    cell operator +(cell oth) {
        cell res;
        res.v = max (v, oth.v);
        return res;
    }
};

struct lzy {
    ll u;
    lzy() {
        u = def;
    }
};

struct Node {
    Node* lft = NULL;
    Node* rht = NULL;
    ll l, r;
    cell v;
    lzy u;

    Node(ll _l, ll _r) {
        l = _l;
        r = _r;
    }

    void extend() {
        if (!lft && l + 1 <= r) {
            ll mid = (l + r) >> 1;
            lft = new Node(l, mid);
            rht = new Node(mid + 1, r);
        }
    }

    void upd_lzy (ll x) {
        u.u += x;
    }

    void push() {
        if (u.u == def) return;
        v.v += u.u;
        if (l + 1 <= r) {
            extend();
            lft -> upd_lzy(u.u);
            rht -> upd_lzy(u.u);
        }
        u.u = def;
    }

    void put(ll ql, ll qr, ll upd) {
        push();
        if (l >= ql && r <= qr) {
            upd_lzy(upd);
            push();
            return;
        } 
        extend();
        ll mid = (l + r) >> 1;
        lft -> push();
        rht -> push();
        if (ql <= mid) lft -> put(ql, qr, upd);
        if (qr >= mid + 1) rht -> put(ql, qr, upd);
        v = ((lft -> v) + (rht -> v));
    }

    cell qry(ll ql, ll qr) {
        push();
        if (l >= ql && r <= qr) {
            return v;
        }
        extend();
        ll mid = (l + r) >> 1;
        cell res;
        if (ql <= mid) res = (res + lft -> qry(ql, qr));
        if (qr >= mid + 1) res = (res + rht -> qry(ql, qr));
        return res;
    }

    ll last() {
        push();
        if (l == r) return l;
        extend();
        lft -> push();
        rht -> push();
        if ((rht -> v).v > 0) return rht -> last();
        return lft -> last();
    }
};

void solve() {
    ll n, m;
    cin >> n >> m;

    ll sz = 1000000;

    vector <ll> a (n), b (m);

    Node* root = new Node(0, sz);

    for (ll i = 0; i < n; i ++) {
        ll x;
        cin >> x;
        a[i] = x;
        root -> put(1, x, 1);
    }

    for (ll i = 0; i < m; i ++) {
        ll x;
        cin >> x;
        b[i] = x;
        root -> put(1, x, -1);
    }

    ll q;
    cin >> q;

    while (q--) {
        ll t;
        cin >> t;

        if (t == 1) {
            ll i, x;
            cin >> i >> x;
            root -> put(1, a[i - 1], -1);
            a[i - 1] = x;
            root -> put(1, a[i - 1], 1);
        }
        else {
            ll i, x;
            cin >> i >> x;
            root -> put(1, b[i - 1], 1);
            b[i - 1] = x;
            root -> put(1, b[i - 1], -1);
        }
        ll res = root -> last();
        if (res == 0) res = -1;
        cout << res << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int tests = 1;
    // cin >> tests;
    for (int i = 0; i < tests; i += 1) {
        solve();
    }
}