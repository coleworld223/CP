#include <bits/stdc++.h>
using namespace std;

using ll = int;
const int mod = 1e9 + 7;

void solve() {
    ll n, c;
    cin >> n >> c;

    vector <vector <ll>> a (n);

    for (ll i = 0; i < c; i += 1) {
        ll u, v;
        cin >> u >> v;
        u--; v--;
        a[v].push_back(u);
    }

    vector <vector <ll>> dp (1 << n, vector <ll> (n, 0));

    for (ll m = 1; m < (1 << n); m += 1) if (m & 1) {
        if ((m >> (n - 1) & 1) && __builtin_popcount(m) != n) continue;
        for (ll u = 0; u < n; u += 1) {
            if (m == 1 && u == 0) {
                dp[m][u] = 1;
            }
            if (__builtin_popcount(m) > 1) {
                for (ll p : a[u]) if (p != u && (m >> p & 1)) {
                    dp[m][u] += (dp[(m ^ (1 << u))][p]);
                    dp[m][u] %= mod;
                }
            }
        }
    }

    cout << dp[(1 << n) - 1][n - 1] << '\n';
}

int main () {
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int tests = 1;
    // cin >> tests;

    for (int i = 0; i < tests; i ++) {
        solve ();
    }
}