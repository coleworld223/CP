#include <bits/stdc++.h>
using namespace std;

using ll = int;
const int mod = 1e9 + 7;

ll def_val = -1, def_lzy = -1;
struct Node {
    Node* lft = NULL;
    Node* rht = NULL;
    ll l, r, v, lzy;
    Node(ll _l, ll _r) {
        l = _l;
        r = _r;
        v = def_val;
        lzy = def_lzy;
    }

    void extend() {
        if (!lft && l + 1 <= r) {
            ll mid = (l + r) >> 1;
            lft = new Node(l, mid);
            rht = new Node(mid + 1, r);
        }
    }

    void push() {
        if (lzy == def_lzy) return;
        v = lzy;
        if (l + 1 <= r) {
            lft -> lzy = lzy;
            rht -> lzy = lzy;
        }
        lzy = def_lzy;
    }

    void put(ll ql, ll qr, ll val) {
        push();
        if (l >= ql && r <= qr) {
            lzy = val;
            push();
            return;
        }
        extend();
        ll mid = (l + r) >> 1;
        if (mid >= ql) lft -> put(ql, qr, val);
        if (mid + 1 <= qr) rht ->  put(ql, qr, val);
        v = max(lft -> v, rht -> v);
    }

    ll qry(ll ql, ll qr) {
        push();
        if (l >= ql && r <= qr) return v;
        extend();
        ll mid = (l + r) >> 1;
        ll res = def_val;
        if (mid >= ql) res = max (res, lft -> qry(ql, qr));
        if (mid + 1 <= qr) res = max (res, rht -> qry(ql, qr));
        return res; 
    }

    ll walk(ll ql, ll qr, ll mx) {
        push();
        if (l == r) return l;
        extend();
        if (lft -> v >= mx) return lft -> walk(ql, qr, mx);
        else if (rht -> v >= mx) return rht -> walk(ql, qr, mx);
        return -1;
    }

};

void solve() {
    ll n, m;
    cin >> n >> m;

    Node* root = new Node(0, n);

    for (ll i = 0; i < n; i += 1) {
        ll x;
        cin >> x;
        root -> put (i, i, x);
    }

    for (ll i = 0; i < m; i += 1) {
        ll x;
        cin >> x;
        ll id = root -> walk(0, n, x);
        cout << id + 1 << ' ';
        if (id != -1) {
            ll ini = root -> qry(id, id);
            root -> put (id, id, ini - x);
        }
    }
    cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int tests = 1;
    // cin >> tests;

    for (int i = 0; i < tests; i ++) {
        solve ();
    }
}