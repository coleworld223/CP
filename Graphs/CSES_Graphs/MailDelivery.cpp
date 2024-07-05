#include<bits/stdc++.h>
using namespace std;

using ll = long long;

void solve() {
    ll n, m;
    cin >> n >> m;

    vector <vector <array <ll, 2>>> a (n);
    vector <ll> deg (n);

    for (ll i = 0; i < m; i++) {
        ll u, v;
        cin >> u >> v;
        u--; v--;
        a[u].push_back({v, i});
        a[v].push_back({u, i});
        deg[u]++;
        deg[v]++;
    }

    for (ll i = 0; i < n; i++) {
        if (deg[i] % 2) {
            cout << "IMPOSSIBLE" << '\n';
            return;
        }
    }

    vector <ll> res = {0};
    vector <ll> done (m);

    function <void (ll)> dfs = [&] (ll u) {
        while (a[u].size()) {
            auto [v, i] = a[u].back();
            a[u].pop_back();
            if (!done[i]) {
                done[i] = 1;
                dfs(v);
                res.push_back(u);
            }
        }
    };

    dfs(0);

    for (ll i = 0; i < m; i++) if (!done[i]) {
        cout << "IMPOSSIBLE" << '\n';
        return;
    }

    for (ll x : res) {
        cout << x + 1 << ' ';
    }
    cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t = 1;
    // cin >> t;
    for (int i = 0; i < t; i++) {
        solve();
    }
}