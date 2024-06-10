#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const ll inf = 1e18;

using a2 = array <ll, 2>;

void solve () {
    ll n, m;
    cin >> n >> m;

    vector <array <ll, 3>> e (m);
    vector <vector <ll>> a (n);

    for (ll i = 0; i < m; i += 1) {
        auto&[u, v, w] = e[i];
        cin >> u >> v >> w;
        u--; v--;
        a[u].push_back(v);
    }

    vector <ll> dis (n, inf), prv (n, -1), vis (n);
    bool f = 0;
    ll lst = -1;

    function <void (ll)> dfs = [&] (ll u) {
        vis[u] = 1;
        for (ll v : a[u]) if (!vis[v]) {
            dfs (v);
        }
    };

    for (ll u = 0; u < n; u += 1) if (!vis[u]) {
        dis[u] = 0;
        dfs (u);
    }

    for (ll p = 0; p < n; p += 1) {
        bool rel = 0;
        for (auto [u, v, w] : e) {
            if (dis[u] != inf) {
                if (dis[u] + w < dis[v]) {
                    dis[v] = dis[u] + w;
                    rel = 1;
                    prv[v] = u;
                    lst = v;
                }
            }
        }
        if (p == n - 1 && rel) {
            f = 1;
        }
    }

    if (!f) {
        cout << "NO" << '\n';
        return;
    }

    for (ll tim = 0; tim < n; tim += 1) {
        lst = prv[lst];
    }

    vector <ll> cyc = {lst};

    ll _ = lst;

    while (1) {
        _ = prv[_];
        cyc.push_back(_);
        if (_ == lst) break;
    }

    cout << "YES" << '\n';

    reverse (cyc.begin(), cyc.end());

    for (ll x : cyc) {
        cout << x + 1 << ' ';
    }
    cout << "\n";


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