#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const ll inf = 1e18;

void solve () {
    ll n, m;
    cin >> n >> m;

    vector <vector <array <ll, 2>>> a (n);

    for (ll i = 0; i < m; i += 1) {
        ll u, v, w;
        cin >> u >> v >> w;
        u--; v--;
        a[u].push_back({v, w});
    }

    set <array <ll, 2>> st;

    vector <ll> dis (n, inf), vis (n);

    dis[0] = 0;
    st.insert ({dis[0], 0});

    while (!st.empty()) {
        auto [d, u] = *st.begin();
        st.erase (st.begin());
        if (vis[u]) continue;
        vis[u] = 1;
        for (auto [v, w] : a[u]) {
            if (dis[u] + w < dis[v]) {
                dis[v] = dis[u] + w;
                st.insert ({dis[v], v});
            }
        }
    }

    for (ll u = 0; u < n; u += 1) {
        cout << dis[u] << ' ';
    }
    cout << "\n";
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