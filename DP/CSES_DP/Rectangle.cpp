#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const ll inf = 1e18;

void solve () {
    ll n, m;
    cin >> n >> m;

    vector <vector <ll>> dp (n + 1, vector <ll> (m + 1, inf));

    //dp[x][y] = to cut a rect (x, y) in square, what's the min move req
    //dp[x][y] = min (dp[x - p][y] + dp[p][y], dp[x][y - q] + dp[x][q]) s.t. x > p >= 1 && y > q >= 1
    // dp[x][x] = 0;

    for (ll i = 1; i <= min (n, m); i += 1) {
        dp[i][i] = 0;
    }

    for (ll x = 1; x <= n; x += 1) {
        for (ll y = 1; y <= m; y += 1) {
            for (ll p = 1; p < x; p += 1) {
                dp[x][y] = min (dp[x][y], dp[x - p][y] + dp[p][y] + 1) ;
            }
            for (ll q = 1; q < y; q += 1) {
                dp[x][y] = min (dp[x][y], dp[x][y - q] + dp[x][q] + 1);
            }
        }
    }

    cout << dp[n][m] << '\n';
}

int main () {
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int tests = 1;
    // cin >> tests;

    for (int i = 0; i < tests; i += 1) {
        solve ();
    }
}