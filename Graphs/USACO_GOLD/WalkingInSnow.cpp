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

    deque <pair <ll, ll>> dq;

    vector <vector <ll>> dis (n, vector <ll> (m, -1));

    dis[0][0] = 0;

    dq.push_back({0, 0});

    auto valid = [&] (ll x, ll y) -> bool {
        return x >= 0 && x < n && y >= 0 && y < m && G[x][y] != '.';
    };

    ll ans = 0;

    while (!dq.empty()) {
        auto ele = dq.front();
        ll x = ele.first, y = ele.second;
        dq.pop_front();
        ans = max (ans, dis[x][y] + 1);
        for (ll dx = -1; dx <= 1; dx += 1) {
            for (ll dy = -1; dy <= 1; dy += 1) if (abs (dx) + abs (dy) == 1) {
                ll nx = x + dx, ny = y + dy;
                if (valid (nx, ny) && dis[nx][ny] == -1) {
                    if (G[nx][ny] == G[x][y]) {
                        dis[nx][ny] = dis[x][y];
                        dq.push_front(make_pair(nx, ny));
                    }
                    else {
                        dis[nx][ny] = dis[x][y] + 1;
                        dq.push_back(make_pair(nx, ny));
                    }
                }
            }
        }
    }

    cout << ans << '\n';
}

int main () {
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int tests = 1;
    // cin >> tests;

    for (int i = 0; i < tests; i += 1) {
        solve ();
    }
}