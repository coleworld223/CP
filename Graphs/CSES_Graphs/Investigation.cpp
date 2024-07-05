#include<bits/stdc++.h>
using namespace std;

using ll = long long;
const ll mod = 1e9 + 7;
const ll inf = 1e18;
using a2 = array <ll, 2>;

void solve() {
    ll n, m;
    cin >> n >> m;

    vector <vector <a2>> a (n);

    for (ll i = 0; i < m; i++) {
        ll u, v, w;
        cin >> u >> v >> w;
        u--; v--;
        a[u].push_back({v, w});
    }

    set <a2> st;
    vector <ll> dis (n, inf), cnt (n, 0), minPath (n), maxPath (n), vis (n);

    cnt[0] = 1;
    dis[0] = 0;
    st.insert({0, 0});

    while (!st.empty()) {
        auto [d, u] = *st.begin();
        st.erase(st.begin());
        if (vis[u]) continue;
        vis[u] = 1;
        for (auto [v, w] : a[u]) {
            if (dis[v] == dis[u] + w) {
                minPath[v] = min(minPath[v], minPath[u] + 1);
                maxPath[v] = max(maxPath[v], maxPath[u] + 1);
                cnt[v] += cnt[u];
                cnt[v] %= mod;
            }
            else if (dis[v] > dis[u] + w) {
                minPath[v] = minPath[u] + 1;
                maxPath[v] = maxPath[u] + 1;
                cnt[v] = cnt[u];
                dis[v] = dis[u] + w;
                st.insert({dis[v], v});
            }
        }
    }

    cout << dis[n - 1] << ' ' << cnt[n - 1] << ' ' << minPath[n - 1] << ' ' << maxPath[n - 1] << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);cin.tie(0);
    int tests = 1;
    // cin >> tests;
    for (int i = 0; i < tests; i++) {
        solve();
    }
}