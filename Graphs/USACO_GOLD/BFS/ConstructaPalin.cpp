#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const ll inf  = 1e18;

void solve () {
    ll n, m;
    cin >> n >> m;

    vector <vector <vector <ll>>> a (n, vector <vector <ll>> (26));

    vector <vector <ll>> dis (n, vector <ll> (n, -1));
    vector <vector <bool>> dne (n, vector <bool> (n));

    queue <array <ll, 2>> q;

    for (ll i = 0; i < n; i += 1) {
        dis[i][i] = 0;
        q.push ({i, i});
    }

    for (ll i = 0; i < m; i += 1) {
        ll u, v;
        char c;
        cin >> u >> v >> c;
        u--; v--;
        if (dis[u][v] == -1) {
            dis[u][v] = dis[v][u] = 1;
        }
        else {
            dis[u][v] = dis[v][u] = min (dis[u][v], 1ll);
        }
        q.push ({v, u});
        q.push ({u, v});
        a[u][c - 'a'].push_back(v);
        a[v][c - 'a'].push_back(u);
    }

    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();
        if (dne[x][y]) continue;
        dne[x][y] = 1;
        for (ll c = 0; c < 26; c += 1) {
            for (ll v1 : a[x][c]) {
                for (ll v2 : a[y][c]) {
                    if (dis[v1][v2] == -1) {
                        dis[v1][v2] = dis[v2][v1] = dis[x][y] + 2;
                        q.push ({v1, v2});
                        q.push ({v2, v1});
                    }
                }
            }
        }
    }

    ll ans = dis[0][n - 1];

    cout << ans << '\n';
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