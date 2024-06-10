#include <bits/stdc++.h>
using namespace std;

using ll = long long;

void solve () {
    ll n, m;
    cin >> n >> m;

    vector <string> G (n);

    for (ll i = 0; i < n; i += 1) {
        cin >> G[i];
    }

    auto valid = [&] (ll x, ll y) -> bool {
        return x >= 0 && x < n && y >= 0 && y < m && G[x][y] != '#';
    };

    vector <vector <ll>> vis (n, vector <ll> (m));

    function <void (ll, ll)> dfs = [&] (ll x, ll y) -> void {
        vis[x][y] = 1;
        for (ll dx = -1; dx <= 1; dx += 1) {
            for (ll dy = -1; dy <= 1; dy += 1) if (abs (dx) + abs (dy) == 1) {
                ll nx = x + dx, ny = y + dy;
                if (valid (nx, ny) && !vis[nx][ny]) {
                    dfs (nx, ny);
                }
            }
        }
    };

    auto bfs = [&] (ll r, ll c) {
        queue <pair <ll, ll>> q;
        q.push ({r, c});
        vis[r][c] = 1;
        while (!q.empty()) {
            auto [x, y] = q.front();
            q.pop();
            for (ll dx = -1; dx <= 1; dx += 1) {
                for (ll dy = -1; dy <= 1; dy += 1) if (abs (dx) + abs (dy) == 1) {
                    ll nx = x + dx, ny = y + dy;
                    if (valid (nx, ny) && !vis[nx][ny]) {
                        vis[nx][ny] = 1;
                        q.push ({nx, ny});
                    }
                }
            }
        }
    };

    ll cnt = 0;

    for (ll i = 0; i < n; i += 1) {
        for (ll j = 0; j < m; j += 1) if (G[i][j] == '.' && !vis[i][j]) {
            dfs (i, j);
            // bfs (i, j);
            cnt += 1;
        }
    }

    cout << cnt << '\n';
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