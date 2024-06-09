#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const int mod = 1e9 + 7;

void solve () {
    ll n;
    cin >> n;

    vector <vector <ll>> a (n);

    for (ll i = 0; i < n - 1; i += 1) {
        ll u, v;
        cin >> u >> v;
        u--; v--;
        a[u].push_back(v);
        a[v].push_back(u);
    } 

    vector <vector <ll>> dp (n, vector <ll> (2));

    function <void (ll, ll)> dfs = [&] (ll u, ll p) {
        ll p0 = 1, p1 = 1;
        for (ll v : a[u]) if (v != p) {
            dfs (v, u);
            p0 *= (dp[v][0] + dp[v][1]);
            p1 *= (dp[v][0]);
            p0 %= mod;
            p1 %= mod;
        }
        dp[u][0] = p0;
        dp[u][1] = p1;
    };

    dfs (0, -1);

    ll res = dp[0][0] + dp[0][1];
    res %= mod;

    cout << res << '\n';
}

int main () {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int no_of_tests = 1;
    // cin >> no_of_tests;
    for (int test_no = 0; test_no < no_of_tests; test_no += 1) {
        solve ();
    }
}