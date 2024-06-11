#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const ll inf = 1e18;

const ll mod = 1e9 + 7;

using a2 = array <ll, 2>;
using a3 = array <ll, 3>;

void solve () {
    ll n, m;
    cin >> n >> m;

    vector <vector <ll>> a (n);
    vector <ll> in (n), tp;

    for (ll i = 0; i < m; i += 1) {
        ll u, v;
        cin >> u >> v;
        u--; v--;
        a[u].push_back(v);
        in[v] += 1;
    }

    queue <ll> q;

    for (ll u = 0; u < n; u += 1) {
        if (in[u] == 0) q.push(u);
    }

    while (!q.empty()) {
        ll u = q.front();
        q.pop();
        tp.push_back(u);
        for (ll v : a[u]) {
            in[v]--;
            if (in[v] == 0) {
                q.push(v);
            }
        }
    }

    vector <ll> dp (n, 0);
    dp[n - 1] = 1;

    for (ll i = n - 1; i >= 0; i--) {
        ll u = tp[i];
        for (ll v : a[u]) {
            dp[u] += dp[v];
            dp[u] %= mod;
        }
    }

    cout << dp[0] << '\n';
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