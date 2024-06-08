#include <bits/stdc++.h>
using namespace std;

using ll = long long;

void solve () {
    cout << fixed << setprecision(10);
    int n;
    cin >> n;

    vector <double> p (n);

    for (int i = 0; i < n; i += 1) {
        cin >> p[i];
    }

    vector <vector <double>> dp (n + 1, vector <double> (n + 1));

    dp[0][0] = 1;

    for (int i = 1; i <= n; i += 1) {
        for (int j = 0; j <= n; j += 1) {
            dp[i][j] += dp[i - 1][j] * (1 - p[i - 1]);
            if (j) dp[i][j] += dp[i - 1][j - 1] * (p[i - 1]);
        }
    }

    double ans = 0;

    for (int h = 0; h <= n; h += 1) {
        int t = (n - h);
        if (h > t) {
            ans += dp[n][h];
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