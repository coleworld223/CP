#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const int mod = 1e9 + 7;

void add (int &x, int y) {
    x += y;
    x %= mod;
}

void solve () {
    int n, m;
    cin >> n >> m;

    vector <vector <char>> grid (n + 1, vector <char> (m + 1));
    vector <vector <int>> dp (n + 1, vector <int> (m + 1));
    dp[1][1] = 1;

    for (int i = 1; i <= n; i += 1) {
        for (int j = 1; j <= m; j += 1) {
            cin >> grid[i][j];
            if (grid[i][j] == '#') continue;
            add (dp[i][j], dp[i - 1][j]);
            add (dp[i][j], dp[i][j - 1]);
        }
    }

    cout << dp[n][m] << '\n';
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