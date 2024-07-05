#include<bits/stdc++.h>
using namespace std;

using ll = long long;
const ll mod = 1e9 + 7;
const ll inf = 1e18;
using a2 = array <ll, 2>;

void solve() {
    ll n, m;
    cin >> n >> m;

    vector <vector <ll>> a (n), ar (n);

    for (ll i = 0; i < m; i++) {
        ll u, v;
        cin >> u >> v;
        u--; v--;
        a[u].push_back(v);
        ar[v].push_back(u);
    }

    vector <ll> ord, vis (n), cmp (n);

    function <void (ll)> dfs = [&] (ll u) {
        vis[u] = 1;
        for (ll v : a[u]) if (!vis[v]) {
            dfs(v);
        }
        ord.push_back(u);
    };

    function <void (ll, ll)> dfs1 = [&] (ll u, ll c) {
        cmp[u] = c;
        vis[u] = 1;
        for (ll v : ar[u]) if (!vis[v]) {
            dfs1(v, c);
        }
    };

    for (ll u = 0; u < n; u++) {
        if (!vis[u]) dfs(u); 
    }

    reverse(ord.begin(), ord.end());
    vis.clear();
    vis.resize(n);

    ll c = 0;

    for (ll x : ord) {
        if (!vis[x]) {
            dfs1(x, c);
            c++;
        }
    }

    cout << c << '\n';

    for (ll i = 0; i < n; i++) {
        cout << cmp[i] + 1 << ' ';
    }
    cout << "\n";
}

int main() {
    ios_base::sync_with_stdio(0);cin.tie(0);
    int tests = 1;
    // cin >> tests;
    for (int i = 0; i < tests; i++) {
        solve();
    }
}