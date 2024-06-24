#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const ll inf = 1e18;

using ll = long long;

// lazy dyanamic segment tree template
ll def_val = 0, def_lzy = 0;
struct Node {
    Node* lft = NULL;
    Node* rht = NULL;
    ll l, r, val, lzy;

    Node (ll _l, ll _r) {
        l = _l;
        r = _r;
        val = def_val;
        lzy = def_lzy; 
    }

    void extend () {
        if (!lft && l + 1 <= r) {
            ll mid = (l + r) >> 1;
            lft = new Node (l, mid);
            rht = new Node (mid + 1, r);
        }
    }

    void push () {
        if (lzy == def_lzy) return;
        val += (r - l + 1) * lzy;
        extend ();
        if (l + 1 <= r) {
            lft -> lzy += lzy;
            rht -> lzy += lzy;
        }
        lzy = 0;
    }

    void upd (ll x, ll y, ll v) {
        push ();
        if (l >= x && r <= y) {
            lzy += v;
            push ();
            return;
        }
        extend ();
        ll mid = (l + r) >> 1;
        if (mid >= x) lft -> upd (x, y, v);
        if (mid + 1 <= y) rht -> upd (x, y, v);
        val = lft -> val + rht -> val;
    }

    ll qry (ll ql, ll qr) {
        push ();
        if (l >= ql && r <= qr) return val;
        extend();
        ll mid = (l + r) >> 1;
        ll res = 0;
        if (mid >= ql) res += lft -> qry (ql, qr);
        if (mid + 1 <= qr) res += rht -> qry (ql, qr);
        return res;
    }
};

void solve () {
    ll n, q;
    cin >> n >> q;

    vector <ll> v (n);

    for (ll i = 0; i < n; i += 1) {
        cin >> v[i];
    }

    vector <vector <ll>> a (n);

    for (ll i = 0; i < n - 1; i += 1) {
        ll u, v;
        cin >> u >> v;
        u--; v--;
        a[u].push_back(v);
        a[v].push_back(u);
    }

    vector <ll> e, in (n), sum (n), sz (n);

    function <void (ll, ll)> dfs = [&] (ll u, ll p) {
        e.push_back(u);
        in[u] = e.size() - 1;
        sum[u] += v[u];
        sz[u] += 1;
        for (ll v : a[u]) if (v != p) {
            sum[v] += sum[u];
            dfs (v, u);
            sz[u] += sz[v];
        }
    };

    dfs (0, -1);
    Node* root = new Node (0, n);

    for (ll i = 0; i < n; i += 1) {
        root -> upd (i, i, sum[e[i]]);
    }

    while (q--) {
        ll tt;
        cin >> tt;
        if (tt == 1) {
            ll u, x;
            cin >> u >> x;
            u--;
            root -> upd (in[u], in[u] + sz[u] - 1, -v[u]);
            v[u] = x;
            root -> upd (in[u], in[u] + sz[u] - 1, v[u]);
        }
        else {
            ll u;
            cin >> u;
            u--;
            ll res = root -> qry (in[u], in[u]);
            cout << res << '\n';
        }
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