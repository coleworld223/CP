#include <bits/stdc++.h>
using namespace std;

using ll = int;

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

    using a2 = array <ll, 2>;
    vector <vector <ll>> d1 (n, vector <ll> (m, -1));
    vector <vector <ll>> d2 (n, vector <ll> (m, -1));
    vector <vector <a2>> prv (n, vector <a2> (m, {-1, -1}));

    queue <a2> q;

    for (ll x = 0; x < n; x += 1) {
        for (ll y = 0; y < m; y += 1) {
            if (G[x][y] == 'M') {
                q.push ({x, y});
                d1[x][y] = 0;
            }
        }
    }

    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();
        for (ll dx = -1; dx <= 1; dx += 1) {
            for (ll dy = -1; dy <= 1; dy += 1) if (abs (dx) + abs (dy) == 1) {
                ll nx = x + dx, ny = y + dy;
                if (valid (nx, ny) && d1[nx][ny] == -1) {
                    d1[nx][ny] = d1[x][y] + 1;
                    q.push ({nx, ny});
                }
            }
        }
    }

    for (ll x = 0; x < n; x += 1) {
        for (ll y = 0; y < m; y += 1) {
            if (G[x][y] == 'A') {
                q.push ({x, y});
                d2[x][y] = 0;
            }
        }
    }

    for (ll x = 0; x < n; x += 1) {
        for (ll y = 0; y < m; y += 1) {
            if (d1[x][y] == -1) {
                d1[x][y] = 1e9;
            }
        }
    }

    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();
        for (ll dx = -1; dx <= 1; dx += 1) {
            for (ll dy = -1; dy <= 1; dy += 1) if (abs (dx) + abs (dy) == 1) {
                ll nx = x + dx, ny = y + dy;
                if (valid (nx, ny) && d2[nx][ny] == -1 && d1[nx][ny] > d2[x][y] + 1) {
                    d2[nx][ny] = d2[x][y] + 1;
                    q.push ({nx, ny});
                    prv[nx][ny] = {x, y};
                }
            }
        }
    }

    string res = "";

    bool f = 0;

    for (ll x = 0; x < n; x += 1) {
        for (ll y = 0; y < m; y += 1) {
            if (x == 0 || x == n - 1 || y == 0 || y == m - 1) {
                if (d2[x][y] != -1) {
                    a2 state = {x, y};
                    f = 1;
                    auto &[r, c] = state;
                    while (G[r][c] != 'A') {
                        auto [pr, pc] = prv[r][c];
                        if (pr == r - 1) {
                            res.push_back('D');
                        }
                        if (pr == r + 1) {
                            res.push_back('U');
                        }
                        if (pc == c - 1) {
                            res.push_back('R');
                        }
                        if (pc == c + 1) {
                            res.push_back('L');
                        }
                        r = pr; c = pc;
                    }
                    reverse (res.begin(), res.end());
                }
            }
            if (res.size()) break;
        }
        if (res.size()) break;
    }

    if (f == 0) cout << "NO" << '\n';
    else {
        cout << "YES" << '\n';
        cout << res.size() << '\n';
        cout << res << '\n';
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