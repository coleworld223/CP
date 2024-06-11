#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const ll inf  = 1e18;

void solve () {
    ll n, x1, y1, x2, y2;
    cin >> n >> x1 >> y1 >> x2 >> y2;

    map <ll, vector <ll>> rc, cr;

    map <ll, ll> dx, dy;

    for (ll i = 0; i < n; i += 1) {
        ll u, v;
        cin >> u >> v;
        rc[u].push_back(v);
        cr[v].push_back(u);
    }

    dx[x1] = 0;
    dy[y1] = 0;

    queue <pair <ll, ll>> q;

    q.push ({x1, 0});
    q.push ({y1, 1});

    while (!q.empty()) {
        auto [u, t] = q.front();
        q.pop();
        if (t == 0) {
            if (rc.count(u) == 0) continue;
            for (ll v : rc[u]) {
                if (dy.count (v) == 0) {
                    dy[v] = dx[u] + 1;
                    q.push ({v, 1});
                }
            }
        }
        else {
            if (cr.count (u) == 0) continue;
            for (ll v : cr[u]) {
                if (dx.count (v) == 0) {
                    dx[v] = dy[u] + 1;
                    q.push ({v, 0});
                }
            }
        }
    }

    ll ans = inf;
    if (dx.count (x2)) {
        ans = min (ans, dx[x2]);
    }
    if (dy.count (y2)) {
        ans = min (ans, dy[y2]);
    }

    if (ans == inf) {
        ans = -1;
    }

    cout << ans << '\n';
}

int main () {
    freopen("lasers.in", "r", stdin);
    freopen("lasers.out", "w", stdout);
    ios_base::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    int tests = 1;
    // cin >> tests;

    for (int i = 0; i < tests; i += 1) {
        solve ();
    }
}