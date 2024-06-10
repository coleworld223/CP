#include <bits/stdc++.h>
using namespace std;

using ll = long long;

void solve () {
    ll n, m;
    cin >> n >> m;

    vector <vector <ll>> a (n);

    for (ll i = 0; i < m; i += 1) {
        ll u, v;
        cin >> u >> v;
        u--; v--;
        a[u].push_back(v);
        a[v].push_back(u);
    }

    vector <ll> path, vis (n);
    vector <ll> cyc;

    function <void (ll, ll)> dfs = [&] (ll u, ll p) {
        path.push_back(u);
        vis[u] = 1;
        for (ll v : a[u]) {
            if (!vis[v]) {
                dfs (v, u);
            }
            else if (v != p && cyc.size() == 0) {
                ll sz = path.size();
                while (1) {
                    cyc.push_back(path[--sz]);
                    if (path[sz] == v) break;
                }
                cyc.push_back(u);
            }
        }
        path.pop_back();
    };

    for (ll u = 0; u < n; u += 1) if (!vis[u]) {
        dfs (u, -1);
    }

    if (cyc.size() == 0) {
        cout << "IMPOSSIBLE" << '\n';
        return;
    }

    cout << cyc.size() << '\n';

    for (ll x : cyc) {
        cout << x + 1 << ' ';
    }
    cout << '\n';

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