#include <bits/stdc++.h>
using namespace std;

using ll = long long;

void solve () {
    int n;
    cin >> n;

    vector <int> a (n);

    for (int i = 0; i < n; i += 1) {
        cin >> a[i];
    }

    map <int, int> cnt;
    
    int ans = 1;

    for (int i = 0, j = 0; i < n; i += 1) {
        cnt[a[i]] += 1;
        while (cnt[a[i]] > 1) {
            cnt[a[j++]]--;
        }
        ans = max (ans, i - j + 1);
    }

    cout << ans << '\n';
}

int main () {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int tests = 1;
    // cin >> tests;

    for (int i = 0; i < tests; i += 1) {
        solve ();
    }
}