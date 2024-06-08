#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const int sz = 1e5;

void solve () {
    ll n, W;
    cin >> n >> W;

    vector <ll> w (n + 1), v (n + 1);

    for (ll i = 1; i <= n; i += 1) {
        cin >> w[i] >> v[i];
    }

    ll inf = 1e18;

    vector <vector <ll>> dp (n + 1, vector <ll> (sz + 1, inf));

    //dp[i][j] = (min capacity req for making value equal to 'j' till index 'i')
    //dp[i][j] -> dp[i + 1][j + w[i + 1]], dp[i + 1][j] (push DP)

    dp[0][0] = 0;

    for (ll i = 0; i < n; i += 1) {
        for (ll j = 0; j <= sz; j += 1) {
            if (dp[i][j] != inf) {
                dp[i + 1][j] = min (dp[i + 1][j], dp[i][j]);
                if (j + v[i + 1] <= sz) dp[i + 1][j + v[i + 1]] 
                   = min (dp[i + 1][j + v[i + 1]], dp[i][j] + w[i + 1]);
            }
        }
    }

    ll ans = 0;

    for (ll val = 0; val <= sz; val += 1) {
        if (dp[n][val] <= W) {
            ans = val;
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