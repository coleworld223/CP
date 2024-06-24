#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const ll inf = 1e18;

using ll = long long;


struct RMQ {
    vector <vector <ll>> tab;
    vector <ll> a;
    ll n;
    ll LOG = 0;
    ll min_index (ll x, ll y) { // modify this for any operations
        return (a[x] < a[y] ? x : y);
    }
    RMQ (vector <ll> &_a) {
        a = _a;
        while ((1 << LOG) < (ll) a.size()) LOG += 1;
        LOG += 1;
        n = a.size();
        tab.resize(n, vector <ll> (LOG, -1));
        for (ll bit = 0; bit < LOG; bit += 1) {
            if (bit == 0) {
                for (ll i = 0; i < n; i += 1) {
                    tab[i][bit] = i;
                }
            }
            else {
                for (ll i = 0; i + (1 << bit) <= n; i += 1) {
                    tab[i][bit] = min_index (tab[i][bit - 1], tab[i + (1 << (bit - 1))][bit - 1]);
                }
            }
        }
    }

    ll qry (ll l, ll r) {
        ll lg = 31 - __builtin_clz (r - l + 1);
        return min_index (tab[l][lg], tab[r - (1 << lg) + 1][lg]);
    }
};

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
        if ((r - l + 1) % 2 != 0) val ^= lzy;
        extend ();
        if (l + 1 <= r) {
            lft -> lzy ^= lzy;
            rht -> lzy ^= lzy;
        }
        lzy = def_lzy;
    }

    void upd (ll x, ll y, ll v) {
        push ();
        if (l >= x && r <= y) {
            lzy ^= v;
            push ();
            return;
        }
        extend ();
        ll mid = (l + r) >> 1;
        if (mid >= x) lft -> upd (x, y, v);
        if (mid + 1 <= y) rht -> upd (x, y, v);
        val = (lft -> val ^ rht -> val);
    }

    ll qry (ll ql, ll qr) {
        push ();
        if (l >= ql && r <= qr) return val;
        extend();
        ll mid = (l + r) >> 1;
        ll res = def_val;
        if (mid >= ql) res = (res ^ lft -> qry (ql, qr));
        if (mid + 1 <= qr) res = (res ^ rht -> qry (ql, qr));
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

    vector <ll> e, in (n), sz (n), dep (n), e1;
    ll LOG = 20;
    vector <vector <ll>> up (n, vector <ll> (LOG, -1));

    function <void (ll, ll)> dfs = [&] (ll u, ll p) {
        for (ll bit = 0; bit < LOG; bit += 1) {
            if (bit == 0) up[u][bit] = p;
            else if (up[u][bit - 1] != -1) up[u][bit] = up[up[u][bit - 1]][bit - 1];
        } 
        e.push_back(u);
        in[u] = e.size() - 1;
        sz[u] += 1;
        for (ll v : a[u]) if (v != p) {
            dep[v] = dep[u] + 1;
            dfs (v, u);
            sz[u] += sz[v];
        }
    };

    dfs (0, -1);

    auto go_up = [&] (ll& u, ll d) {
        for (ll bit = 0; bit < LOG; bit += 1) if (d >> bit & 1) {
            u = up[u][bit];
        }
    };

    auto lca = [&] (ll u, ll v) ->  ll {
        if (dep[u] < dep[v]) swap (u, v);
        go_up (u, dep[u] - dep[v]);
        if (u == v) return u;
        for (ll bit = LOG - 1; bit >= 0; bit -= 1) if (up[u][bit] != up[v][bit]) {
            u = up[u][bit];
            v = up[v][bit];
        }
        return up[u][0];
    };

    Node* root = new Node (0, n);
    vector <ll> dep_array (n);

    for (ll i = 0; i < n; i += 1) {
        dep_array[i] = dep[e[i]];
        root -> upd (i, i + sz[e[i]] - 1, v[e[i]]);
    }

    RMQ rmq (dep_array);

    while (q--) {
        ll tt;
        cin >> tt;
        if (tt == 1) {
            ll u, x;
            cin >> u >> x;
            u--;
            root -> upd (in[u], in[u] + sz[u] - 1, v[u]);
            v[u] = x;
            root -> upd (in[u], in[u] + sz[u] - 1, v[u]);
        }
        else {
            ll x, y;
            cin >> x >> y;
            x--; y--;
            ll lc = lca (x, y);
            ll xx = root -> qry (in[x], in[x]);
            ll yx = root -> qry (in[y], in[y]);
            ll res = (xx ^ yx ^ v[lc]);
            cout << res << '\n';
        }
    }
}

int main () {
    freopen("cowland.in", "r", stdin);
    freopen("cowland.out", "w", stdout);
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int tests = 1;
    // cin >> tests;

    for (int i = 0; i < tests; i ++) {
        solve ();
    }
}