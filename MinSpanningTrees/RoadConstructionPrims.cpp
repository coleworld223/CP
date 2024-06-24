#include <bits/stdc++.h>
using namespace std;

using ll = long long;

void solve () {
    ll n, m;
    cin >> n >> m;

    vector <vector <array <ll, 3>>> a (n);
    vector <ll> wt (m);

    for (ll i = 0; i < m; i += 1) {
        ll u, v, w;
        cin >> u >> v >> w;
        u--; v--;
        wt[i] = w; 
        a[u].push_back({v, w, i});
        a[v].push_back({u, w, i});
    } 

    ll inf = 1e18;
    vector <bool> vis (n);
    vector <ll> dis (n, inf);
    priority_queue <array <ll, 3>> pq;
    pq.push ({-0, 0, -1});
    dis[0] = 0;
    vector <ll> mst;
    ll cst = 0;

    while (!pq.empty()) {
        auto [d, u, e] = pq.top();
        pq.pop();
        if (vis[u] || dis[u] < -d) continue;
        vis[u] = 1;
        if (e != -1) {
            mst.push_back(e);
            cst += wt[e];
        }
        for (auto [v, w, e1] : a[u]) {
            if (!vis[v] && dis[v] > w) {
                dis[v] = w;
                pq.push({-w, v, e1});
            }
        }
    }

    if (mst.size() != n - 1) {
        cout << "IMPOSSIBLE" << '\n';
        return;
    }

    cout << cst << '\n';
}

int main () {
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int tests = 1;
    // cin >> tests;

    for (int i = 0; i < tests; i ++) {
        solve ();
    }
}