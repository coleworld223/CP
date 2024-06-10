#include <bits/stdc++.h>
using namespace std;

using ll = long long;

void solve () {
    ll n, m, r, c, x, y;
    cin >> n >> m >> r >> c >> x >> y;

    vector <string> G (n);

    for (ll i = 0; i < n; i += 1) {
        cin >> G[i];
    }

    r--; c--;

    deque <pair <ll, ll>> dq;

    vector <vector <array <ll, 2>>> dis (n, vector <array <ll, 2>> (m, {-1, -1}));

    dq.push_back({r, c});
    dis[r][c] = {0, 0};

    auto valid = [&] (ll x, ll y) -> bool {
        return x >= 0 && x < n && y >= 0 && y < m && G[x][y] == '.';
    };

    while (!dq.empty()) {
        auto [cr, cc] = dq.front();
        dq.pop_front();
        auto [dl, dr] = dis[cr][cc];
        ll nr, nc;
        // up
        nr = cr - 1, nc = cc;
        if (valid (nr, nc) && dis[nr][nc][0] == -1) {
            dis[nr][nc] = {dl, dr};
            dq.push_front({nr, nc});
        }
        //down
        nr = cr + 1, nc = cc;
        if (valid (nr, nc) && dis[nr][nc][0] == -1) {
            dis[nr][nc] = {dl, dr};
            dq.push_front ({nr, nc});
        }
        //left
        nr = cr, nc = cc - 1;
        if (valid (nr, nc) && dis[nr][nc][0] == -1) {
            dis[nr][nc] = {dl + 1, dr};
            dq.push_back ({nr, nc});
        }
        //right
        nr = cr, nc = cc + 1;
        if (valid (nr, nc) && dis[nr][nc][0] == -1) {
            dis[nr][nc] = {dl, dr + 1};
            dq.push_back({nr, nc});
        }
    }

    ll ans = 0;

    for (ll i = 0; i < n; i += 1) {
        for (ll j = 0; j < m; j += 1) if (G[i][j] == '.') {
            auto [l, r] = dis[i][j];
            if (l == -1) continue; 
            if (l <= x && r <= y) {
                ans += 1;
            }
        }
    }

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