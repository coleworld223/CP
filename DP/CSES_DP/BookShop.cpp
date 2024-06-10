#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const int mod = 1e9 + 7;
const ll inf = 1e18;

void solve () {
    ll n, k;
    cin >> n >> k;

    vector <ll> wt (n), val (n);

    for (ll i = 0; i < n; i += 1) {
        cin >> wt[i];
    }

    for (ll i = 0; i < n; i += 1) {
        cin >> val[i];
    }

    vector <ll> dp (k + 1);

    for (ll i = 0; i < n; i += 1) {
        for (ll j = k; j >= 0; j--) {
            if (j - wt[i] >= 0) {
                dp[j] = max (dp[j], dp[j - wt[i]] + val[i]);
                dp[j] %= mod;
            }
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