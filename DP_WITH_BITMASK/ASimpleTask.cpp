#include <bits/stdc++.h>
using namespace std;

// https://codeforces.com/contest/11/problem/D

using ll = long long;
const ll inf = 1e18;

void solve() {
    ll n, m;
    cin >> n >> m;

    vector <vector <ll>> a (n, vector <ll> (n));

    for (ll i = 0; i < m; i += 1) {
        ll u, v;
        cin >> u >> v;
        u--; v--;
        a[u][v] = a[v][u] = 1;
    }

    vector <vector <ll>> dp (1 << n, vector <ll> (n, 0));

    ll ans = 0;

    for (ll m = 1; m < (1 << n); m += 1) {
        for (ll u = 0; u < n; u += 1) {
            if (__builtin_popcount(m) == 1) {
                dp[m][u] = 1;
            }
            else {
                for (ll p = 0; p < n; p += 1) if ((m >> p & 1) && (p != u) && a[p][u] && (u != __builtin_ctz(m))) {
                    dp[m][u] += (dp[(m ^ (1 << u))][p]);
                }
            }
            ll fir = __builtin_ctz(m);
            if (a[u][fir] && __builtin_popcount(m) >= 3) {
                ans += (dp[m][u]);
            }
        }
    }

    cout << ans / 2 << '\n';
}

int main () {
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int tests = 1;
    // cin >> tests;

    for (int i = 0; i < tests; i ++) {
        solve ();
    }
}