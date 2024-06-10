#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const int mod = 1e9 + 7;
const ll inf = 1e18;

void solve () {
    ll n, k;
    cin >> n >> k;

    vector <ll> a (n);

    for (ll i = 0; i < n; i += 1) {
        cin >> a[i];
    }

    vector <ll> dp (k + 1, inf);

    dp[0] = 0;

    for (ll i = 1; i <= k; i += 1) {
        for (ll j = 0; j < n; j += 1) if (i - a[j] >= 0) {
            dp[i] = min (dp[i], dp[i - a[j]] + 1);
        } 
    }
    
    if (dp[k] == inf) dp[k] = -1;

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
