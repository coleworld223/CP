#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const int sz = 1e5 + 5;

bool dp[sz][2];

void solve () {
    ll n, k;
    cin >> n >> k;

    vector <int> a (n);

    for (int i = 0; i < n; i += 1) {
        cin >> a[i];
    }

    for (int sum = 0; sum <= k; sum += 1) {
        dp[sum][0] = 0;
        for (int i = 0; i < n; i += 1) {
            if (sum - a[i] >= 0 && dp[sum - a[i]][1] == 1) {
                dp[sum][0] = 1;
            }
        }
        dp[sum][1] = 1;
        for (int i = 0; i < n; i += 1) {
            if (sum - a[i] >= 0 && dp[sum - a[i]][0] == 0) {
                dp[sum][1] = 0;
            }
        }
    }

    if (dp[k][0]) cout << "First" << '\n';
    else cout << "Second" << '\n';
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