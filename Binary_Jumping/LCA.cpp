#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const ll inf = 1e18;
const int mod = 998244353;

void solve() {
    ll n, q;
    cin >> n >> q;

    vector <vector <ll>> a (n);

    for (ll i = 1; i < n; i++) {
        ll x;
        cin >> x;
        x--;
        a[i].push_back(x);
        a[x].push_back(i);
    }

    ll LOG = 20;

    vector <vector <ll>> up (n, vector <ll> (LOG, -1));
    vector <ll> dep (n);

    function <void (ll, ll)> dfs = [&] (ll u, ll p) {
        for (ll bit = 0; bit < LOG; bit++) {
            if (bit == 0) up[u][bit] = p;
            else if (up[u][bit - 1] != -1) up[u][bit] = up[up[u][bit - 1]][bit - 1];
        }
        for (ll v : a[u]) if (v != p) {
            dep[v] = dep[u] + 1;
            dfs(v, u);
        }
    };

    dfs(0, -1);

    auto go_up = [&] (ll& u, ll d) {
        for (ll bit = 0; bit < LOG; bit++) if ((d >> bit & 1) && u != -1) {
            u = up[u][bit];
        }
    };

    auto lca = [&] (ll u, ll v) {
        if (dep[u] < dep[v]) swap(u, v);
        go_up(u, dep[u] - dep[v]);
        if (u == v) return u;
        for (ll bit = LOG - 1; bit >= 0; bit--) if (up[u][bit] != up[v][bit]) {
            u = up[u][bit];
            v = up[v][bit];
        }
        return up[u][0];
    };

    while (q--) {
        ll u, d;
        cin >> u >> d;
        u--;
        go_up(u, d);
        if (u != -1) u += 1;
        cout << u << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int tests = 1;
    // cin >> tests;
    for (int i = 0; i < tests; i += 1) {
        solve();
    }
}