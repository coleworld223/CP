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

    vector <vector <ll>> dp (n, vector <ll> (n, -inf));

    for (ll len = 1; len <= n; len += 1) {
        if (len == 1) {
            for (ll i = 0; i + len - 1 < n; i += 1) {
                ll j = i + len - 1;
                dp[i][j] = a[i];
            }
        }
        else {
            for (ll i = 0; i + len - 1 < n; i += 1) {
                ll j = i + len - 1;
                ll ad0 = 0, ad1 = 0, ad2 = 0;
                if (j - i + 1 > 2) {
                    ad0 = dp[i + 1][j - 1];
                    ad1 = dp[i + 2][j];
                    ad2 = dp[i][j - 2];
                }
                dp[i][j] = max (dp[i][j], a[i] + min (ad0, ad1));
                dp[i][j] = max (dp[i][j], a[j] + min (ad0, ad2));
            }
        }
    }

    cout << dp[0][n - 1] << '\n';
}

int main () {
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int tests = 1;
    // cin >> tests;

    for (int i = 0; i < tests; i += 1) {
        solve ();
    }
}