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

    vector <ll> deg (n), tp;

    for (ll i = 0; i < m; i += 1) {
        ll u, v;
        cin >> u >> v;
        u--; v--;
        a[u].push_back(v);
        deg[v] += 1;
    }

    queue <ll> q;

    for (ll u = 0; u < n; u += 1) {
        if (deg[u] == 0) { 
            q.push (u);
        }
    }

    while (!q.empty()) {
        ll u = q.front();
        q.pop();
        tp.push_back(u);
        for (ll v : a[u]) {
            deg[v]--;
            if (deg[v] == 0) {
                q.push (v);
            }
        }
    }

    if ((ll) tp.size() != n) cout << "IMPOSSIBLE" << "\n";
    else {
        for (ll x : tp) {
            cout << x + 1 << ' ';
        }
        cout << '\n';
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