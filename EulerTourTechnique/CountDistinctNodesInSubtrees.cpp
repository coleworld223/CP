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
    ll n;
    cin >> n;

    vector <ll> col (n);
    map <ll, vector <ll>> ind;
    for (ll i = 0; i < n; i += 1) {
        cin >> col[i];
    }

    vector <vector <ll>> a (n);

    for (ll i = 0; i < n - 1; i += 1) {
        ll u, v;
        cin >> u >> v;
        u--; v--;
        a[u].push_back(v);
        a[v].push_back(u);
    }

    vector <ll> e, t (n), sz (n);

    function <void (ll, ll)> dfs = [&] (ll u, ll p) {
        e.push_back(u);
        t[u] = e.size() - 1;
        sz[u] += 1;
        for (ll v : a[u]) if (v != p) {
            dfs (v, u);
            sz[u] += sz[v];
        }
    };

    dfs (0, -1);

    for (ll i = 0; i < n; i += 1) {
        ind[col[e[i]]].push_back(i);
    }

    vector <ll> res (n);

    Node* root = new Node (0, n);

    for (ll i = n - 1; i >= 0; i--) {
        ll x = ind[col[e[i]]].back();
        if (x > i) {
            root -> upd (x, x, -1);
            ind[col[e[i]]].pop_back();
        }
        root -> upd (i, i, 1);
        res[e[i]] = root -> qry (i, sz[e[i]] + i - 1);
    }

    for (ll i = 0; i < n; i += 1) {
        cout << res[i] << ' ';
    }
    cout << '\n';
}

int main () {
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int tests = 1;
    // cin >> tests;

    for (int i = 0; i < tests; i ++) {
        solve ();
    }
}