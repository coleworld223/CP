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

    vector <vector <bool>> vis (n, vector <bool> (m));
    vector <vector <array <ll, 2>>> prv (n, vector <array <ll, 2>> (m, {-1, -1}));

    auto valid = [&] (ll x, ll y) -> bool {
        return x >= 0 && x < n && y >= 0 && y < m && G[x][y] != '#';
    };

    auto bfs = [&] (ll x, ll y) -> void {
        queue <array <ll, 2>> q;
        q.push ({x, y});
        vis[x][y] = 1;
        while (!q.empty()) {
            auto [r, c] = q.front();
            q.pop();
            for (ll dx = -1; dx <= 1; dx += 1) {
                for (ll dy = -1; dy <= 1; dy += 1) if (abs (dx) + abs (dy) == 1) {
                    ll nr = r + dx, nc = c + dy;
                    if (valid (nr, nc) && !vis[nr][nc]) {
                        vis[nr][nc] = 1;
                        prv[nr][nc] = {r, c};
                        q.push ({nr, nc});
                    }
                }
            }
        }
    };

    using a2 = array <ll, 2>;
    a2 st, en, state;

    for (ll i = 0; i < n; i += 1) {
        for (ll j = 0; j < m; j += 1) {
            if (G[i][j] == 'A') {
                st = {i, j};
            }
            if (G[i][j] == 'B') {
                en = {i, j};
            }
        }
    }

    auto [enx, eny] = en;
    auto [stx, sty] = st;

    bfs (enx, eny);

    if (vis[stx][sty] == 0) {
        cout << "NO" << '\n';
        return;
    }

    state = st;

    auto &[r, c] = state;

    string res = "";

    while (G[r][c] != 'B') {
        auto [nr, nc] = prv[r][c];
        if (nr == r + 1) {
            res.push_back('D');
        }
        if (nr == r - 1) {
            res.push_back('U');
        }
        if (nc == c + 1) {
            res.push_back('R');
        }
        if (nc == c - 1) {
            res.push_back('L');
        }
        r = nr, c = nc;
    }

    cout << "YES" << '\n';

    cout << res.size() << '\n';

    cout << res << '\n';
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