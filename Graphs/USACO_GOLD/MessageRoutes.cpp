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

    queue <ll> q;
    vector <ll> dis (n, -1), par (n, -1);

    dis[0] = 0; q.push (0);

    while (!q.empty()) {
        ll u = q.front();
        q.pop();
        for (ll v : a[u]) {
            if (dis[v] == -1) {
                dis[v] = dis[u] + 1;
                q.push (v);
                par[v] = u;
            }
        }
    }

    if (dis[n - 1] == -1) {
        cout << "IMPOSSIBLE" << '\n';
        return;
    }

    vector <ll> path;

    ll _ = n - 1;

    while (_ != -1) {
        path.push_back(_);
        _ = par[_];
    }

    reverse (path.begin(), path.end());

    cout << path.size() << '\n';

    for (ll x : path) {
        cout << x + 1 << ' ';
    }
    cout << '\n';
}

int main () {
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int tests = 1;
    // cin >> tests;

    for (int i = 0; i < tests; i += 1) {
        solve ();
    }
}