// https://codeforces.com/contest/342/submission/266404647

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const ll inf = 1e18;

struct centroid {
    vector <vector <ll>> e;
    vector <ll> siz;
    vector <bool> vis;
    vector <ll> par;
    ll n;

    centroid (ll sz) {
        n = sz;
        e.resize(n);
        par.resize(n, -1);
        vis.resize(n);
        siz.resize(n);
    }

    void add (ll x, ll y) {
        e[x].push_back(y);
        e[y].push_back(x);
    }

    ll find_size (ll u, ll p = -1) {
        if (vis[u]) return 0ll;
        siz[u] = 1;
        for (ll v : e[u]) if (v != p) {
            siz[u] += find_size (v, u);
        }
        return siz[u];
    }

    ll find_centroid (ll u, ll p, ll sz) {
        for (ll v : e[u]) if (v != p) {
            if (!vis[v] && siz[v] > sz / 2) {
                return find_centroid (v, u, sz);
            }
        }
        return u;
    }

    void init_centroid (ll u = 0, ll p = -1) {
        find_size (u);
        ll c = find_centroid (u, -1, siz[u]);
        vis[c] = 1;
        par[c] = p;
        for (ll v : e[c]) if (!vis[v]) {
            init_centroid (v, c);
        }
    }
};

void solve () {
    ll n, q;
    cin >> n >> q;

    vector <vector <ll>> a (n);
    centroid ds (n);

    for (ll i = 0; i < n - 1; i += 1) {
        ll u, v;
        cin >> u >> v;
        u--; v--;
        a[u].push_back(v);
        a[v].push_back(u);
        ds.add (u, v);
    }

    ds.init_centroid ();
    ll LOG = 20;
    vector <ll> dep (n), ans (n, inf);
    vector <vector <ll>> up (n, vector <ll> (LOG, -1));

    function <void (ll, ll)> dfs = [&] (ll u, ll p) {
        for (ll bit = 0; bit < LOG; bit += 1) {
            if (bit == 0) up[u][bit] = p;
            else if (up[u][bit - 1] != -1) up[u][bit] = up[up[u][bit - 1]][bit - 1];
        }
        for (ll v : a[u]) if (v != p) {
            dep[v] = dep[u] + 1;
            dfs (v, u);
        }
    };

    auto go = [&] (ll &u, ll d) {
        for (ll bit = 0; bit < LOG; bit += 1) if (d >> bit & 1) {
            u = up[u][bit];
        }
    };

    auto lca = [&] (ll u, ll v) {
        if (dep[u] < dep[v]) swap (u, v);
        go (u, dep[u] - dep[v]);
        if (u == v) return u;
        for (ll bit = LOG - 1; bit >= 0; bit--) if (up[u][bit] != up[v][bit]) {
            u = up[u][bit];
            v = up[v][bit];
        }
        return up[u][0];
    };

    auto dis = [&] (ll u, ll v) {
        ll lc = lca (u, v);
        return (dep[u] + dep[v] - 2 * dep[lc]);
    };

    dfs (0, -1);

    auto upd = [&] (ll x) {
        ll _ = x;
        while (_ != -1) {
            ans[_] = min (ans[_], dis (_, x));
            _ = ds.par[_];
        }
    };

    upd (0);

    while (q--) {
        ll t, x;
        cin >> t >> x;
        x--;
        if (t == 1) {
            upd (x);
        }
        else {
            ll res = ans[x];
            ll _ = x;
            while (_ != -1) {
                res = min (res, ans[_] + dis (_, x));
                _ = ds.par[_];
            }
            cout << res << '\n';
        }
    }
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