#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const ll inf = 1e18;

void solve () {
    ll n, m;
    cin >> n >> m;

    vector <array <ll, 3>> e (m);
    vector <vector <ll>> a (n);

    for (ll i = 0; i < m; i += 1) {
        auto&[u, v, w] = e[i];
        cin >> u >> v >> w;
        u--; v--;
        a[v].push_back(u);
    }

    vector <ll> dis (n, -inf);

    dis[0] = 0;

    for (ll tim = 0; tim < n - 1; tim += 1) {
        for (auto [u, v, w] : e) {
            if (dis[u] != -inf && dis[v] < dis[u] + w) {
                dis[v] = dis[u] + w;
            }
        }
    }

    vector <ll> bad (n), vis (n);

    bool f = 0;

    for (auto [u, v, w] : e) {
        if (dis[u] != inf && dis[u] + w > dis[v]) {
            bad[v] = 1;
        }
    }

    function <void (ll)> dfs = [&] (ll u) {
        vis[u] = 1;
        if (bad[u] && dis[u] != -inf) f = 1;
        for (auto v : a[u]) if (!vis[v]) {
            dfs (v);
        }
    };

    dfs (n - 1);

    if (f) cout << -1 << '\n';
    else cout << dis[n - 1] << '\n';
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