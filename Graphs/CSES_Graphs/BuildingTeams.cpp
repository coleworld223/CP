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

    vector <ll> col (n, -1);

    bool f = 1;

    function <void (ll)> dfs = [&] (ll u) -> void {
        for (ll v : a[u]) {
            if (col[v] == -1) {
                col[v] = 1 - col[u];
                dfs (v);
            }
            else {
                if (col[v] == col[u]) f = 0;
            }
        }
    };

    for (ll u = 0; u < n; u += 1) {
        if (col[u] == -1) {
            col[u] = 0;
            dfs (u);
        }
    }

    if (!f) {
        cout << "IMPOSSIBLE" << '\n';
        return;
    }

    for (ll i = 0; i < n; i += 1) {
        cout << col[i] + 1 << ' ';
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