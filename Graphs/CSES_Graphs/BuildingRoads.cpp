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

    vector <ll> vis (n);

    vector <ll> cmp;

    function <void (ll)> dfs = [&] (ll u) {
        vis[u] = 1;
        for (ll v : a[u]) if (!vis[v]) {
            dfs (v);
        }
    };

    for (ll u = 0; u < n; u += 1) if (!vis[u]) {
        dfs (u);
        cmp.push_back(u);
    }

    ll ans = cmp.size() - 1;

    cout << ans << '\n';

    for (ll i = 0; i < cmp.size() - 1; i += 1) {
        cout << cmp[i] + 1 << ' ' << cmp[i + 1] + 1 << '\n';
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