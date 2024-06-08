#include <bits/stdc++.h>
using namespace std;

using ll = long long;

void solve () {
    ll n;
    cin >> n;

    vector <array <ll, 3>> h (n + 1), dp (n + 1);

    ll ans = 0;

    for (ll i = 1; i <= n; i += 1) {
        auto&[a, b, c] = h[i];
        cin >> a >> b >> c;
        for (ll j = 0; j < 3; j += 1) {
            for (ll k = 0; k < 3; k += 1) if (k != j) {
                dp[i][j] = max (dp[i][j], dp[i - 1][k] + h[i][j]);
                ans = max (ans, dp[i][j]);
            }
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