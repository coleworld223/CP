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

    vector <ll> dis (n, -1), prv (n, -1);

    auto bfs = [&] (ll u) -> void {
        queue <ll> q;
        q.push (u);
        dis[u] = 0;
        while (!q.empty()) {
            ll c = q.front();
            q.pop();
            for (ll v : a[c]) if (dis[v] == -1) {
                dis[v] = dis[u] + 1;
                prv[v] = c;
                q.push (v);
            } 
        }
    };

    bfs (0);

    if (dis[n - 1] == -1) {
        cout << "IMPOSSIBLE" << '\n';
        return;
    }

    vector <ll> path;
    ll state = n - 1;

    while (state != -1) {
        path.push_back(state + 1);
        state = prv[state];
    }

    reverse (path.begin(), path.end());

    cout << path.size() << '\n';

    for (ll x : path) {
        cout << x << ' ';
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