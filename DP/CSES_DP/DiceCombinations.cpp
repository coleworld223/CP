#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const int mod = 1e9 + 7;
const ll inf = 1e18;

void solve () {
    ll n, k;
    cin >> n >> k;

    vector <ll> c (n);

    for (ll i = 0; i < n; i += 1) {
        cin >> c[i];
    }

    vector <ll> dp (k + 1);

    dp[0] = 1;

    for (ll x = 1; x <= k; x += 1) {
        for (ll j = 0; j < n; j += 1) if (x - c[j] >= 0) {
            dp[x] += dp[x - c[j]];
            dp[x] %= mod;
        }
    }

    cout << dp[k] << '\n';
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