#include<bits/stdc++.h>
using namespace std;

using ll = long long;
const ll mod = 1e9 + 7;
const ll inf = 1e18;

void solve() {
    ll n;
    cin >> n;

    using a3 = array <ll, 3>;

    vector <a3> a (n);

    ll M = 0;

    for (ll i = 0; i < n; i++) {
        auto&[w, s, v] = a[i];
        cin >> w >> s >> v;
        M = max(M, s);
    }

    sort (a.begin(), a.end(), [&] (a3 x, a3 y) {
        return x[0] + x[1] < y[0] + y[1];
    });

    M *= 2;

    vector <ll> dp (M + 1);
    auto [w, s, v] = a[0];
    dp[w] = v;

    for (ll i = 0; i < n - 1; i++) {
        auto [w, s, v] = a[i + 1];
        for (ll j = M; j >= 0; j--) {
            if (j + w <= M && j <= s) dp[j + w] = max(dp[j + w], dp[j] + v);
        }
    }

    ll ans = *max_element(dp.begin(), dp.end());

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