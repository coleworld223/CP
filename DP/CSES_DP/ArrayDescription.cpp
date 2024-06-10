#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const int mod = 1e9 + 7;
const ll inf = 1e18;

void solve () {
    ll n, m;
    cin >> n >> m;

    vector <ll> a (n);

    for (ll i = 0; i < n; i += 1) {
        cin >> a[i];
    }

    vector <ll> dp (m + 1);

    dp[a[0]] = 1;

    if (a[0] == 0) {
        for (ll i = 1; i <= m; i += 1) {
            dp[i] = 1;
        }
    }

    for (ll i = 1; i < n; i += 1) {
        vector <ll> tmp (m + 1);
        if (a[i] == 0) {
            for (ll x = 1; x <= m; x += 1) {
                for (ll y = x - 1; y <= x + 1; y += 1) if (y >= 1 && y <= m) {
                    tmp[x] += dp[y];
                    tmp[x] %= mod;
                }
            }
        }
        else {
            for (ll y = a[i] - 1; y <= a[i] + 1; y += 1) if (y >= 1 && y <= m) {
                tmp[a[i]] += dp[y];
                tmp[a[i]] %= mod;
            }
        }
        dp = tmp;
    }

    ll ans = dp[a[n - 1]];

    if (a[n - 1] == 0) {
        ans = 0;
        for (ll i = 1; i <= m; i += 1) {
            ans += dp[i];
            ans %= mod;
        }
    }

    cout << ans << '\n';
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