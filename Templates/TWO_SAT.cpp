struct two_sat {
    ll n;
    bool valid;
    vector <vector <ll>> a, ar;
    vector <ll> t, vis, cmp;
    vector <ll> res;

    two_sat(ll _n) {
        n = _n;
        valid = 1;
        vis.resize(2 * n);
        res.resize(n);
        cmp.resize(2 * n);
        a.resize(2 * n);
        ar.resize(2 * n);
    }

    void add_edge(ll x, ll y) {
        a[x].push_back(y);
        ar[y].push_back(x);
    }

    void add_clause(ll x, ll f, ll y, ll g) {
        add_edge(x + (f ? n : 0), y + (g ? 0 : n));
        add_edge(y + (g ? n : 0), x + (f ? 0 : n));
    }

    void exactly_one(ll x, ll y) {
        add_clause(x, 1, y, 1);
        add_clause(x, 0, y, 0);
    }

    void force_true(ll x) {
        add_clause(x, 1, x, 1);
    }

    void both_same(ll x, ll y) {
        add_clause(x, 0, y, 1);
        add_clause(x, 1, y, 0);
    }

    void dfs1(ll u) {
        vis[u] = 1;
        for (ll v : a[u]) if (!vis[v]) {
            dfs1(v);
        }
        t.push_back(u);
    }

    void dfs2(ll u, ll c) {
        vis[u] = 1;
        cmp[u] = c;
        for (ll v : ar[u]) if (!vis[v]) {
            dfs2(v, c);
        }
    }

    void work() {
        for (ll i = 0; i < 2 * n; i++) if (!vis[i]) {
            dfs1(i);
        }
        vis.clear();
        vis.resize(2 * n, 0);
        for (ll i = 2 * n - 1, c = 0; i >= 0; i--) {
            if (!vis[t[i]]) {
                dfs2(t[i], c);
                c++;
            }
        }
        
        for (ll i = 0; i < n; i++) {
            if (cmp[i] == cmp[i + n]) valid = 0;
            if (cmp[i] > cmp[i + n]) res[i] = 1;
        }
    }

    vector <ll> giv() {
        return res;
    }
};