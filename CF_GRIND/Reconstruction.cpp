#include <bits/stdc++.h>
using namespace std;

//https://codeforces.com/contest/1984/submission/266278190

using ll = long long;
const int mod = 998244353;


void solve () {
    ll n, m;
    cin >> n >> m;

    string s;
    cin >> s;

    m = abs (m);

    s = "P" + s;
    s.push_back('S');

    vector <ll> b (n + 2);

    for (ll i = 1; i <= n; i += 1) {
        cin >> b[i];
    }

    set <ll> done;

    ll ans = 0;

    for (ll i = 0; i <= n; i += 1) {
        ll sum = b[i] + b[i + 1];
        if (done.count (sum)) continue;
        done.insert (sum);
        ll dp[n + 2][2] = {0};

        dp[0][0] = 1;

        for (ll j = 1; j <= n + 1; j += 1) {
            if (s[j] == 'P') {
                if (abs(b[j] - b[j - 1]) <= m) {
                    dp[j][0] += dp[j - 1][0];
                }
                ll p_sm = abs(b[j] + b[j - 1] - sum);
                if (max ((p_sm / 2), (p_sm - (p_sm / 2))) <= m) dp[j][0] += dp[j - 1][1];
            }
            else if (s[j] == 'S') {
                if (b[j] + b[j - 1] == sum) dp[j][1] += dp[j - 1][0];
                if (abs (b[j - 1] - b[j]) <= m) dp[j][1] += dp[j - 1][1];
            }
            else {
                if (abs(b[j] - b[j - 1]) <= m) dp[j][0] += dp[j - 1][0];
                ll p_sm = abs(b[j] + b[j - 1] - sum);
                if (max ((p_sm / 2), (p_sm - (p_sm / 2))) <= m) dp[j][0] += dp[j - 1][1];
                if (b[j] + b[j - 1] == sum) dp[j][1] += dp[j - 1][0];
                if (abs (b[j - 1] - b[j]) <= m) dp[j][1] += dp[j - 1][1];
            }
            dp[j][0] %= mod;
            dp[j][1] %= mod;
        }
        ans += dp[n + 1][1];
        ans %= mod;
    }

    ans += mod;
    ans %= mod;

    cout << ans << '\n';
}

int main () {
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int tests = 1;
    cin >> tests;

    for (int i = 0; i < tests; i += 1) {
        solve ();
    }
}