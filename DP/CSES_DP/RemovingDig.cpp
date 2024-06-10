#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const int mod = 1e9 + 7;
const ll inf = 1e18;

void solve () {
    ll n;
    cin >> n;

    vector <ll> dp (n + 1, inf);

    dp[0] = 0;

    for (ll i = 1; i <= n; i += 1) {
        ll d = i;
        while (d) {
            ll x = (d % 10);
            d /= 10;
            if (i - x >= 0) dp[i] = min (dp[i], dp[i - x] + 1);
        }
    }

    cout << dp[n] << '\n';
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