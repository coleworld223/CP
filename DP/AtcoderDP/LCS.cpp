#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const int sz = 1e5;

void solve () {
    string a, b;
    cin >> a >> b;

    ll n = a.size(), m = b.size();

    vector <vector <ll>> dp (n + 1, vector <ll> (m + 1));

    for (ll i = 1; i <= n; i += 1) {
        for (ll j = 1; j <= m; j += 1) {
            dp[i][j] = max ({dp[i][j], dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1] + (a[i - 1] == b[j - 1])});
        }
    }

    array <ll, 2> state = {n, m};

    string res = "";

    while (1) {
        auto &[x, y] = state;
        if (x == 0 || y == 0) break;
        if (dp[x][y] == dp[x - 1][y - 1] + 1 && (a[x - 1] == b[y - 1])) {
            res.push_back(a[x - 1]);
            x--; y--;
        }
        else {
            if (dp[x][y] == dp[x - 1][y]) x--;
            else if (dp[x][y] == dp[x][y - 1]) y--;
        }
    }

    reverse (res.begin(), res.end());
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