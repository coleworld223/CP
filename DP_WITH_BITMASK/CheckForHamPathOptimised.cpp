#include <bits/stdc++.h>
using namespace std;

/*
   Given an graph check for existence of hamiltonian walk (optimised)
*/

using ll = long long;
const ll inf = 1e18;

void solve() {
    ll n, m;
    cin >> n >> m;

    vector <vector <ll>> a (n, vector <ll> (n, -1));
    vector <ll> e (n);

    for (ll i = 0; i < m; i += 1) {
        ll u, v, w;
        cin >> u >> v >> w;
        u--; v--;
        a[u][v] = a[v][u] = w;
        e[u] |= (1 << v);
        e[v] |= (1 << u);
    }

    vector <ll> dp (1 << n);

    for (ll m = 0; m < (1 << n); m += 1) {
        if (__builtin_popcount(m) == 1) {
            dp[m] = m;
        } 
        else {
            for (ll p = 0; p < n; p += 1) if ((m >> p & 1)) {
                if ((dp[(m ^ (1 << p))] & e[p])) dp[m] |= (1 << p);
            }
        }
    }

    if (dp[(1 << n) - 1]) cout << "YES" << '\n';
    else cout << "NO" << '\n';
}

int main () {
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int tests = 1;
    // cin >> tests;

    for (int i = 0; i < tests; i ++) {
        solve ();
    }
}