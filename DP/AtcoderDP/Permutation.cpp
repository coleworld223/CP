#include<bits/stdc++.h>
using namespace std;

using ll = long long;
const ll mod = 1e9 + 7;

void solve() {
    ll n;
    cin >> n;

    string s;
    cin >> s;

    vector <ll> dp (n + 1);
    vector <ll> pref (n + 1);

    dp[1] = 1;

    ll ans = 0;

    for (ll i = 1; i < n; i++) {
        for (ll j = 1; j <= i + 1; j++) {
            pref[j] = dp[j] + pref[j - 1];
            pref[j] %= mod;
            dp[j] = 0;
        }
        for (ll j = 1; j <= i + 1; j++) {
            if (s[i - 1] == '>') 
                dp[j] = pref[i + 1] - pref[j - 1];
            else
                dp[j] = pref[j - 1];
            dp[j] %= mod;
            if (i == n - 1) 
                ans += dp[j], ans %= mod;
        }
    }

    ans += mod;
    ans %= mod;
    cout << ans << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);cin.tie(0);
    int tests = 1;
    // cin >> tests;
    for (int i = 0; i < tests; i++) {
        solve();
    }
}