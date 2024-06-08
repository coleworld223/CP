#include <bits/stdc++.h>
using namespace std;

using ll = long long;

void solve () {
    ll n, W;
    cin >> n >> W;

    vector <ll> w (n + 1), v (n + 1);

    for (ll i = 1; i <= n; i += 1) {
        cin >> w[i] >> v[i];
    }

    vector <vector <ll>> dp (n + 1, vector <ll> (W + 1));

    ll ans = 0;

    for (ll i = 1; i <= n; i += 1) {
        for (ll j = 0; j <= W; j += 1) {
            dp[i][j] = max (dp[i][j], dp[i - 1][j]);
            if (j - w[i] >= 0) {
                dp[i][j] = max (dp[i][j], dp[i - 1][j - w[i]] + v[i]);
            }
            ans = max (ans, dp[i][j]);
        }
    }

    cout << ans << '\n';
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