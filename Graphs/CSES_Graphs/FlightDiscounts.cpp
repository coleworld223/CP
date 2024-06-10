#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const ll inf = 1e18;

using a2 = array <ll, 2>;

void solve () {
    ll n, m;
    cin >> n >> m;

    vector <vector <a2>> a (n), ar (n);
    vector <array <ll, 3>> e (m);

    for (ll i = 0; i < m; i += 1) {
        ll u, v, w;
        cin >> u >> v >> w;
        u--; v--;
        e[i] = {u, v, w};
        a[u].push_back({v, w});
        ar[v].push_back({u, w});
    }

    auto dij = [&] (ll node, vector <vector <a2>> &a) -> vector <ll> {
        vector <ll> dis (n, inf), vis (n);
        set <a2> st;
        dis[node] = 0;
        st.insert ({dis[node], node});
        while (!st.empty()) {
            auto [d, u] = *st.begin();
            st.erase (st.begin());
            if (vis[u]) continue;
            vis[u] = 1;
            for (auto [v, w] : a[u]) {
                if (d + w < dis[v]) {
                    dis[v] = d + w;
                    st.insert ({dis[v], v});
                }
            }
        }
        return dis;
    };

    vector <ll> d0 = dij (0, a);
    vector <ll> dn = dij (n - 1, ar);

    ll ans = d0[n - 1];

    for (auto [u, v, w] : e) {
        ans = min (ans, w / 2 + d0[u] + dn[v]);
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