#include <bits/stdc++.h>
using namespace std;

using ll = long long;

void solve () {
    ll n;
    cin >> n;

    vector <vector <ll>> a (n, vector <ll> (n));

    for (ll i = 0; i < n; i += 1) {
        for (ll j = 0; j < n; j += 1) {
            cin >> a[i][j];
        }
    }

    vector <ll> dp1 (1 << n);

    for (ll msk = 1; msk < (1 << n); msk += 1) {
        ll lssb = __builtin_ctz(msk);
        ll nmsk = (msk ^ (1 << lssb));
        dp1[msk] += dp1[nmsk];
        for (ll bit = 0; bit < n; bit += 1) if (nmsk >> bit & 1) {
            dp1[msk] += a[bit][lssb];
        } 
    }

    vector <ll> dp (1 << n);

    for (ll msk = 0; msk < (1 << n); msk += 1) {
        for (ll s = msk; s > 0; s = (msk & (s - 1))) {
            dp[msk] = max (dp[msk], dp1[s] + dp[(msk ^ s)]);
        }
    }

    cout << dp[(1 << n) - 1] << '\n';
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