using ll = long long;

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