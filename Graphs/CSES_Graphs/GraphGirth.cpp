#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const ll mod = 998244353;

const int sz = 2e5 + 5;

const ll inf = 1e18;

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

    ll ans = inf;

    auto bfs = [&] (ll node) -> void {
        queue <ll> q;
        vector <ll> dis (n, -1), par (n, -1);
        q.push (node);
        dis[node] = 0;
        while (!q.empty()) {
            ll u = q.front();
            q.pop();
            for (ll v : a[u]) if (v != par[u]) {
                if (dis[v] == -1) {
                    dis[v] = dis[u] + 1;
                    par[v] = u;
                    q.push (v);
                }
                else {
                    ans = min (ans, dis[u] + dis[v] + 1);
                }
            }
        }
    };

    for (ll u = 0; u < n; u += 1) {
        bfs (u);
    }

    if (ans == inf) ans = -1;

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