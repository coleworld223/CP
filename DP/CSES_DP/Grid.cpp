#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const int mod = 1e9 + 7;
const ll inf = 1e18;

void solve () {
    ll n;
    cin >> n;

    vector <string> G (n);

    for (ll i = 0; i < n; i += 1) {
        cin >> G[i];
    }

    vector <vector <ll>> dp (n, vector <ll> (n));

    if (G[0][0] == '.') dp[0][0] = 1;

    for (ll i = 0; i < n; i += 1) {
        for (ll j = 0; j < n; j += 1) if (G[i][j] == '.') {
            if (i) dp[i][j] += dp[i - 1][j];
            if (j) dp[i][j] += dp[i][j - 1];
            dp[i][j] %= mod;
        }
    }

    cout << dp[n - 1][n - 1];
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