#include <bits/stdc++.h>
using namespace std;

using ll = long long;

void solve () {
    ll n;
    cin >> n;

    ll inf = 1e18;

    vector <ll> h (n), dp (n, inf);

    for (ll i = 0; i < n; i += 1) {
        cin >> h[i];
    }

    dp[0] = 0;

    for (ll i = 1; i < n; i += 1) {
        dp[i] = min ({dp[i], (i - 1 >= 0 ? dp[i - 1] + abs (h[i] - h[i - 1]) : inf),
         (i - 2 >= 0? dp[i - 2] + abs (h[i] - h[i - 2]) : inf)});
    }

    cout << dp[n - 1] << '\n';
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