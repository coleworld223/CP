#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const ll inf = 1e18;

void solve () {
    string s, t;
    cin >> s >> t;

    ll n = s.size();
    ll m = t.size();

    vector <vector <ll>> dp (n, vector <ll> (m, inf));

    for (ll i = 0; i < n; i += 1) {
        for (ll j = 0; j < m; j += 1) {
            dp[i][j] = min (dp[i][j], (i - 1 >= 0 ? dp[i - 1][j] + 1 : j + 1 + 1));
            dp[i][j] = min (dp[i][j], (j - 1 >= 0 ? dp[i][j - 1] + 1 : i + 1 + 1));
            dp[i][j] = min (dp[i][j], (i - 1 >= 0 && j - 1 >= 0 ? dp[i - 1][j - 1] + (s[i] != t[j]) : (s[i] != t[j]) + (j - 1 + 1) + (i - 1 + 1)));
        }
    }

    cout << dp[n - 1][m - 1] << '\n';
}

int main () {
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int tests = 1;
    // cin >> tests;

    for (int i = 0; i < tests; i += 1) {
        solve ();
    }
}