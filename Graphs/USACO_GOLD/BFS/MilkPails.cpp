#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const ll mod = 998244353;

const int sz = 2e5 + 5;

void solve () {
    ll x, y, k, m;
    cin >> x >> y >> k >> m;

    vector <vector <ll>> dis (x + 1, vector <ll> (y + 1, -1));

    dis[0][0] = 0;

    queue <array <ll, 2>> q;

    q.push ({0, 0});

    while (!q.empty()) {
        auto [r, c] = q.front();
        q.pop();
        if (dis[x][c] == -1) {
            dis[x][c] = dis[r][c] + 1;
            q.push ({x, c});
        }
        if (dis[r][y] == -1) {
            dis[r][y] = dis[r][c] + 1;
            q.push ({r, y});
        }
        if (dis[0][c] == -1) {
            dis[0][c] = dis[r][c] + 1;
            q.push ({0, c});
        }
        if (dis[r][0] == -1) {
            dis[r][0] = dis[r][c] + 1;
            q.push ({r, 0});
        }
        ll t = min (r, y - c);
        if (dis[r - t][c + t] == -1) {
            dis[r - t][c + t] = dis[r][c] + 1;
            q.push ({r - t, c + t});
        }
        t = min (c, x - r);
        if (dis[r + t][c - t] == -1) {
            dis[r + t][c - t] = dis[r][c] + 1;
            q.push ({r + t, c - t});
        }
    }

    ll ans = 1e9;

    for (ll i = 0; i <= x; i += 1) {
        for (ll j = 0; j <= y; j += 1) if (dis[i][j] != -1 && dis[i][j] <= k) {
            ans = min (ans, abs (m - (i + j)));
        }
    }

    cout << ans << '\n';
}

int main () {
    freopen("pails.in", "r", stdin);
    freopen("pails.out", "w", stdout);
    ios_base::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    int tests = 1;
    // cin >> tests;

    for (int i = 0; i < tests; i += 1) {
        solve ();
    }
}