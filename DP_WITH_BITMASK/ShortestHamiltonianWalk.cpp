#include <bits/stdc++.h>
using namespace std;

/*
   Given an graph search for shortest hamiltonian walk
*/

using ll = long long;
const ll inf = 1e18;

void solve() {
    ll n, m;
    cin >> n >> m;

    vector <vector <ll>> a (n, vector <ll> (n, -1));

    for (ll i = 0; i < m; i += 1) {
        ll u, v, w;
        cin >> u >> v >> w;
        u--; v--;
        a[u][v] = a[v][u] = w;
    }

    ll ans = inf;

    vector <vector <ll>> dp (1 << n, vector <ll> (n, inf));

    for (ll m = 0; m < (1 << n); m += 1) {
        for (ll u = 0; u < n; u += 1) if (m >> u & 1) {
            if (__builtin_popcount(m) == 1) {
                dp[m][u] = 0;
                continue;
            }
            for (ll p = 0; p < n; p += 1) if (p != u && (m >> p & 1) && a[p][u] != -1) {
                ll nm = (m ^ (1 << u));
                if (dp[nm][p] != inf && dp[nm][p] + a[p][u] < dp[m][u]) dp[m][u] = dp[nm][p] + a[p][u];
            }
            if (m == (1 << n) - 1) {
                ans = min (ans, dp[m][u]);
            }
        }
    }

    if (ans == inf) ans = -1;
    cout << ans << '\n';
}

int main () {
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int tests = 1;
    // cin >> tests;

    for (int i = 0; i < tests; i ++) {
        solve ();
    }
}