#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const ll LOG = 20;

void solve() {
    ll n, k;
    cin >> n >> k;

    vector <ll> a (n);
    vector <vector <ll>> p (n, vector <ll> (LOG, -1));
    vector <vector <ll>> len (n, vector <ll> (LOG, -1));
    ll s = 0;

    for (ll i = 0; i < n; i++) {
        cin >> a[i];
        s += a[i];
    }

    if (s <= k) {
        cout << 1 << '\n';
        return;
    }

    for (ll i = 0, j = 0, sum = 0; i < n; i++) {
        while (sum + a[j % n] <= k) {
            sum += a[j % n];
            j++;
        }
        len[i][0] = (j - i);
        p[i][0] = (j % n);
        sum -= a[i];
    }

    for (ll bit = 1; bit < LOG; bit++) {
        for (ll i = 0; i < n; i++) {
            p[i][bit] = p[p[i][bit - 1]][bit - 1];
            len[i][bit] = len[i][bit - 1] + len[p[i][bit - 1]][bit - 1];
        }
    }

    ll lo = 0, hi = n + 1;

    auto chk = [&] (ll mid) -> bool {
        for (ll i = 0; i < n; i++) {
            ll cur_len = 0, cur_idx = i;
            for (ll bit = 0; bit < LOG; bit++) if ((mid >> bit & 1)) {
                cur_len += len[cur_idx][bit];
                cur_idx = p[cur_idx][bit];
            }
            if (cur_len >= n) return 1;
        }
        return 0;
    };

    while (hi - lo > 1) {
        ll mid = (lo + hi) >> 1;
        if (chk (mid)) hi = mid;
        else lo = mid;
    }

    cout << hi << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int tests = 1;
    // cin >> tests;
    for (int i = 0; i < tests; i += 1) {
        solve();
    }
}