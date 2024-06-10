#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const int mod = 1e9 + 7;
const ll inf = 1e18;
ll n = 1e6;
vector <vector <ll>> dp (n + 1, vector <ll> (2));

void make () {
    dp[1][0] = 1;
    dp[1][1] = 1;

    for (ll i = 2; i <= n; i += 1) {
        dp[i][0] += (4 * dp[i - 1][0] + dp[i - 1][1]);
        dp[i][1] += (dp[i - 1][1] + dp[i - 1][0] + dp[i - 1][1]);
        dp[i][0] %= mod;
        dp[i][1] %= mod;
    }
}

int main () {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    make ();
    int no_of_tests = 1;
    cin >> no_of_tests;
    for (int test_no = 0; test_no < no_of_tests; test_no += 1) {
        ll p;
        cin >> p;
        ll res = (dp[p][0] + dp[p][1]) % mod;
        cout << res << '\n';
    }
}