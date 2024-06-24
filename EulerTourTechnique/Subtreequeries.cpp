#include <bits/stdc++.h>
using namespace std;

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

    vector <ll> value (n);

    for (ll i = 0; i < n; i += 1) {
        cin >> value[i];
    }

    vector <vector <ll>> adj (n);

    for (ll i = 0; i < n - 1; i += 1) {
        ll u, v;
        cin >> u >> v;
        u--; v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // euler tour

    vector <ll> tour, pos (n), sbtree (n);

    function <void (ll, ll)> dfs = [&] (ll node, ll par) {
        tour.push_back (node);
        pos[node] = tour.size() - 1;
        sbtree[node] += 1;
        for (ll child : adj[node]) if (child != par) {
            dfs (child, node);
            sbtree[node] += sbtree[child];
        }
    };

    dfs (0, -1);

    Node* root = new Node (0, n);

    for (ll i = 0; i < n; i += 1) {
        root -> upd (i, i, value[tour[i]]);
    }
 
    while (q--) {
        ll type;
        cin >> type;
        if (type == 1) {
            ll s, x;
            cin >> s >> x;
            s--;
            value[s] = x;
            ll ini = root -> qry (pos[s], pos[s]);
            root -> upd (pos[s], pos[s], x - ini);
        }
        else {
            ll s;
            cin >> s;
            s--;
            ll res = root -> qry (pos[s], pos[s] + sbtree[s] - 1);
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