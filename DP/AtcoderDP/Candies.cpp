#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const int mod = 1e9 + 7;

void solve () {
    ll n, k;
    cin >> n >> k;

    vector <ll> a (n);

    for (ll i = 0; i < n; i += 1) {
        cin >> a[i];
    }

    vector <ll> dp (k + 1), pf (k + 1);

    dp[0] = 1;

    auto reset = [&] () {
        for (ll i = 0; i <= k; i += 1) {
            pf[i] = dp[i];
            dp[i] = 0;
            if (i) pf[i] += pf[i - 1];
            pf[i] %= mod;
        }
    };

    for (ll i = 0; i < n; i += 1) {
        reset ();
        for (ll j = k; j >= 0; j--) {
            ll r = j, l = max(0ll, j - a[i]);
            dp[j] += pf[r] - (l ? pf[l - 1] : 0);
            dp[j] %= mod;
        }
    }

    dp[k] += mod;
    dp[k] %= mod;

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