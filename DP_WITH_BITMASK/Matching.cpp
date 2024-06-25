#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const int mod = 1e9 + 7;

void solve () {
    ll n;
    cin >> n;

    vector <vector <ll>> cmp (n, vector <ll> (n));

    for (ll i = 0; i < n; i += 1) {
        for (ll j = 0; j < n; j += 1) {
            cin >> cmp[i][j];
        }
    }

    vector <ll> dp (1 << n);

    dp[0] = 1;

    for (ll i = 0; i < n; i += 1) {
        for (ll msk = 0; msk < (1 << n); msk += 1) if (__builtin_popcount (msk) == (i + 1)) {
            for (ll j = 0; j < n; j += 1) if (msk >> j & 1 && cmp[i][j]) {
                dp[msk] += dp[(msk ^ (1 << j))];
                dp[msk] %= mod;
            }
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