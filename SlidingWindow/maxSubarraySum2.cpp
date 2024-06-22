#include <bits/stdc++.h>
using namespace std;

//same implementation goes for min sum as well

using ll = long long;

void solve () {
    ll n, a, b;
    cin >> n >> a >> b;

    vector <ll> sum (n + 1);

    ll ans = -1e18;

    for (ll i = 1; i <= n; i += 1) {
        cin >> sum[i];
        sum[i] += sum[i - 1];
    }

    multiset <ll> st;

    for (ll i = 1, i1 = 0, i2 = 0; i <= n; i += 1) {
        while (i - i1 + 1 > a) {
            st.insert (sum[i1++]);
        }
        while (i - i2 + 1 > b + 1) {
            st.erase (st.find(sum[i2++]));
        }
        if (i - i1 + 1 == a && !st.empty()) {
            ll mn = *begin(st);
            ans = max (ans, sum[i] - mn);
        }
    }

    cout << ans << '\n';
}

int main () {
    ios_base::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    int tests = 1;
    // cin >> tests;

    for (int i = 0; i < tests; i += 1) {
        solve ();
    }
}