
struct BinaryLiftingTree {
    ll LOG;
    ll n;
    vector <vector <ll>> up;
    // Requires a parent array
    BinaryLiftingTree(vector <ll>& _par) {
        n = _par.size();
        LOG = ceil(log2(n + 1)) + 1;
        up.resize(n, vector <ll> (LOG, -1));
        for (ll i = 0; i < n; i++) {
            up[i][0] = _par[i];
        }
        work();
    }

    void work() {
        for (ll bit = 1; bit < LOG; bit++) {
            for (ll u = 0; u < n; u++) {
                if (up[u][bit - 1] != -1) up[u][bit] = up[up[u][bit - 1]][bit - 1];
            }
        }
    }

    void go_up(ll &u, ll k) {
        for (ll bit = 0; bit < LOG; bit++) if ((k >> bit & 1) && u != -1) {
            u = up[u][bit];
        }
    }
};