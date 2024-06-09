#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const ll inf = 1e18;

void solve () {
    ll n;
    cin >> n;

    vector <ll> a (n);

    for (ll i = 0; i < n; i += 1) {
        cin >> a[i];
    }

    vector <vector <ll>> dp (n, vector <ll> (n, inf));

    for (ll len = 1; len <= n; len += 1) {
        if (len == 1) {
            for (ll i = 0; i + len - 1 < n; i += 1) {
                dp[i][i + len - 1] = 0;
            }
        }
        else {
            for (ll i = 0; i + len - 1 < n; i += 1) {
                ll j = i + len - 1;
                ll smb = 0;
                for (ll k = i; k <= j; k += 1) {
                    smb += a[k];
                }
                for (ll k = i, smf = 0; k <= j - 1; k += 1) {
                    smf += a[k];
                    smb -= a[k];
                    dp[i][j] = min (dp[i][j], smf + smb + dp[i][k] + dp[k + 1][j]);
                }
            }
        }
    }

    cout << dp[0][n - 1] << '\n';
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