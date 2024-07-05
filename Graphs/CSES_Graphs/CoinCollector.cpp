#include<bits/stdc++.h>
using namespace std;

using ll = long long;

void solve() {
    ll n, m;
    cin >> n >> m;

    vector <ll> coins (n);
    vector <vector <ll>> adj (n), adj_rev (n);

    for (ll i = 0; i < n; i++) {
        cin >> coins[i];
    }

    for (ll i = 0; i < m; i++) {
        ll u, v;
        cin >> u >> v;
        u--; v--;
        adj[u].push_back(v);
        adj_rev[v].push_back(u);
    }

    vector <ll> vis (n), cmp (n), tp;

    function <void (ll)> dfs = [&] (ll u) {
        vis[u] = 1;
        for (ll v : adj[u]) if (!vis[v]) {
            dfs(v);
        }
        tp.push_back(u);
    };

    ll c = 0, sum = 0;

    function <void (ll)> dfs2 = [&] (ll u) {
        vis[u] = 1;
        sum += coins[u];
        cmp[u] = c;
        for (ll v : adj_rev[u]) if (!vis[v]) {
            dfs2(v);
        }
    };

    for (ll i = 0; i < n; i++) {
        if (!vis[i]) dfs(i);
    }

    reverse(tp.begin(), tp.end());
    vis.clear();
    vis.resize(n);
    vector <ll> cnt (n);

    for (ll x : tp) {
        if (!vis[x]) {
            sum = 0;
            dfs2(x);
            c++;
            cnt[c - 1] = sum;
        }
    }

    vector <vector <ll>> adj_scc (c);

    for (ll i = 0; i < n; i++) {
        for (ll v : adj[i]) {
            if (cmp[i] != cmp[v]) {
                adj_scc[cmp[i]].push_back(cmp[v]);
            }
        }
    }

    function <ll (vector <vector <ll>>)> give = [&] (vector <vector <ll>> adj) -> ll {
        ll n = adj.size();
        vector <ll> deg (n), tp;
        for (ll i = 0; i < n; i++) {
            for (ll x : adj[i]) deg[x]++;
        }
        queue <ll> q;
        for (ll i = 0; i < n; i++) if (deg[i] == 0) {
            q.push(i);
        }
        while (!q.empty()) {
            ll u = q.front();
            q.pop();
            tp.push_back(u);
            for (ll v : adj[u]) {
                deg[v]--;
                if (deg[v] == 0) 
                    q.push(v);
            }
        }

        reverse(tp.begin(), tp.end());
        vector <ll> dp (n);
        ll ans = 0;

        for (ll x : tp) {
            dp[x] = cnt[x];
            for (ll v : adj[x]) {
                dp[x] = max(dp[x], cnt[x] + dp[v]);
            }
            ans = max(ans, dp[x]);
        }
        return ans;
    };

    ll res = give(adj_scc);

    cout << res << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t = 1;
    // cin >> t;
    for (int i = 0; i < t; i++) {
        solve();
    }
}