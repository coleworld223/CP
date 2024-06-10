#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const ll inf = 1e18;

void solve () {
    ll n, m, q;
    cin >> n >> m >> q;

    vector <vector <ll>> dis (n, vector <ll> (n, -1));

    for (ll i = 0; i < m; i += 1) {
        ll u, v, w;
        cin >> u >> v >> w;
        u--; v--;
        if (dis[u][v] == -1) dis[u][v] = dis[v][u] = w;
        else {
            dis[u][v] = dis[v][u] = min (dis[u][v], w);
        }
    }

    for (ll x = 0; x < n; x += 1) {
        dis[x][x] = 0;
    }

    for (ll k = 0; k < n; k += 1) {
        for (ll x = 0; x < n; x += 1) {
            for (ll y = 0; y < n; y += 1) {
                if (dis[x][k] == -1 || dis[k][y] == -1) continue;
                if (dis[x][y] == -1) dis[x][y] = dis[x][k] + dis[k][y];
                else dis[x][y] = min (dis[x][y], dis[x][k] + dis[k][y]);
            }
        }
    }

    while (q--) {
        ll u, v;
        cin >> u >> v;
        u--; v--;
        cout << dis[u][v] << '\n';
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