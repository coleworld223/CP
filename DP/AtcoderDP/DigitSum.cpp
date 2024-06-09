#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const ll mod = 1e9 + 7;

ll dp[100001][101][2];

void solve () {
    string s;
    cin >> s;

    ll d;
    cin >> d;

    ll n = s.size();

    vector <ll> pw (n + 1);

    pw[0] = 1;

    for (ll i = 1; i <= n; i += 1) {
        pw[i] = pw[i - 1] * 10;
        pw[i] %= d;
    }

    auto reset = [&] () {
        for (ll i = 0; i < n; i += 1) {
            for (ll j = 0; j < d; j += 1) {
                for (ll k = 0; k < 2; k += 1) {
                    dp[i][j][k] = -1;
                }
            }
        }
    };

    reset ();

    function <ll (ll, ll, ll)> F = [&] (ll idx, ll rem, ll f) {
        if (idx >= n) {
            if (rem == 0) return 1ll;
            return 0ll;
        }
        if (dp[idx][rem][f] != -1) return dp[idx][rem][f];
        ll res = 0;
        if (f) {
            for (ll dig = 0; dig <= 9; dig += 1) {
                res += F (idx + 1, (rem + dig) % d, 1);
                res %= mod;
            }
        }
        else {
            ll till = (s[idx] - '0');
            for (ll dig = 0; dig <= till; dig += 1) {
                res += F (idx + 1, (rem + dig) % d, (dig < till));
                res %= mod;
            }
        }
        return dp[idx][rem][f] = res;
    };

    ll res = F (0, 0, 0);

    res -= 1;

    res %= mod;

    res += mod;

    res %= mod;

    cout << res << '\n';
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