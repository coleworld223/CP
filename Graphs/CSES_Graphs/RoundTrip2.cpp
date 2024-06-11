#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const ll inf = 1e18;

using a2 = array <ll, 2>;
using a3 = array <ll, 3>;

void solve () {
    ll n, m;
    cin >> n >> m;

    vector <vector <ll>> a (n);

    for (ll i = 0; i < m; i += 1) {
        ll u, v;
        cin >> u >> v;
        u--; v--;
        a[u].push_back(v);
    }

    vector <ll> vis (n), pvis (n, -1), path, cyc;

    function <void (ll)> dfs = [&] (ll u) {
        vis[u] = 1;
        path.push_back(u);
        pvis[u] = path.size() - 1;
        for (ll v : a[u]) {
            if (!vis[v]) dfs (v);
            else if (pvis[v] != -1 && cyc.size() == 0) {
                for (ll i = pvis[v]; i < path.size(); i += 1) {
                    cyc.push_back(path[i]);
                }
                cyc.push_back (v);
            }
        }
        pvis[u] = -1;
        path.pop_back();
    };

    for (ll u = 0; u < n; u += 1) {
        if (!vis[u]) dfs (u);
    }

    if (cyc.size() == 0) cout << "IMPOSSIBLE" << '\n';
    else {
        cout << cyc.size() << '\n';
        for (ll x : cyc) {
            cout << x + 1 << ' ';
        }
        cout << "\n";
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