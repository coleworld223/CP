#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const ll inf = 1e18;

ll def_val = inf;
ll def_lzy = inf;
class Node {
public:
    Node* lft = NULL;
    Node* rht = NULL;
    ll l, r, node_val, node_lzy;

    Node (ll _l, ll _r) {
        l = _l, r = _r, node_val = def_val, node_lzy = def_lzy;
    }

    void extend () {
        if (!lft && l + 1 <= r) {
            ll mid = (l + r) >> 1;
            lft = new Node (l, mid);
            rht = new Node (mid + 1, r);
        }
    }

    void upd_lzy (ll x) {
        node_lzy = x;
    }

    void push () {
        if (node_lzy == def_lzy) return;
        node_val = node_lzy;
        if (l + 1 <= r) {
            extend ();
            lft -> upd_lzy (node_lzy);
            rht -> upd_lzy (node_lzy);
        }
        node_lzy = def_lzy;
    }

    void put (ll ql, ll qr, ll v) {
        push();
        if (l >= ql && r <= qr) {
            upd_lzy (v);
            push();
            return;
        }
        extend();
        ll mid = (l + r) >> 1;
        if (ql <= mid) lft -> put (ql, qr, v);
        if (mid + 1 <= qr) rht -> put (ql, qr, v);
        node_val = min (lft -> node_val, rht -> node_val);
    }

    ll qry (ll ql, ll qr) {
        push();
        if (l >= ql && r <= qr) return node_val;
        extend();
        ll mid = (l + r) >> 1;
        ll res = def_val;
        if (ql <= mid) res = min (res, lft -> qry (ql, qr));
        if (mid + 1 <= qr) res = min (res, rht -> qry (ql, qr));
        return res;
    }
};

void solve () {
    ll n, q;
    cin >> n >> q;

    vector <ll> a (n);

    Node* root = new Node (0, n);

    for (ll i = 0; i < n; i += 1) {
        cin >> a[i];
        root -> put (i, i, a[i]);
    }

    while (q--) {
        ll l, r;
        cin >> l >> r;
        l--; r--;
        ll res = root -> qry (l, r);
        cout << res << '\n';
    }
}

int main () {
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int tests = 1;
    // cin >> tests;

    for (int i = 0; i < tests; i ++) {
        solve ();
    }
}