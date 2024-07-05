#include<bits/stdc++.h>
using namespace std;

using ll = long long;
const ll mod = 1e9 + 7;

struct Binomial {
    ll n;
    vector <ll> fact;
    Binomial(ll sz) {
        n = sz;
        fact.resize(n + 1);
        work();
    }

    void work() {
        fact[0] = 1;
        for (ll i = 1; i <= n; i++) {
            fact[i] = (fact[i - 1] * i) % mod;
        }
    }

    ll binpow(ll a, ll b) {
        if (b == 0) return 1ll;
        ll res = binpow(a, b / 2);
        ll ret = res;
        if (b % 2) ret = (res * a) % mod;
        ret = (ret * res) % mod;
        return ret;
    }

    ll inv(ll x) {
        return binpow(x, mod - 2);
    }

    ll C(ll n, ll r) {
        if (r > n) return 0ll;
        ll res = (fact[n] * inv(fact[r])) % mod;
        res = (res * inv(fact[n - r])) % mod;
        return res;
    }
};

void solve() {
    ll h, w, n;
    cin >> h >> w >> n;

    using a2 = array <ll, 2>;

    vector <a2> a (n);

    for (ll i = 0; i < n; i++) {
        auto&[x, y] = a[i];
        cin >> x >> y;
    }

    n += 1;

    a.push_back({h, w});

    sort (a.begin(), a.end(), [&] (a2 x, a2 y) {
        if (x[0] == y[0]) return x[1] < y[1];
        return x[0] < y[0];
    });

    Binomial bin(300000);

    vector <ll> dp (n);

    auto pathCount = [&] (ll x1, ll y1, ll x2, ll y2) -> ll {
        return bin.C(y2 - y1 + x2 - x1, x2 - x1);
    };

    for (ll i = 0; i < n; i++) {
        auto [x, y] = a[i];
        dp[i] = pathCount(1, 1, x, y);
        for (ll j = 0; j < i; j++) {
            auto [x1, y1] = a[j];
            if (y >= y1) {
                dp[i] -= (dp[j] * pathCount(x1, y1, x, y));
                dp[i] %= mod;
            }
        }
    }

    dp[n - 1] += mod;
    dp[n - 1] %= mod;
    cout << dp[n - 1] << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);cin.tie(0);
    int tests = 1;
    // cin >> tests;
    for (int i = 0; i < tests; i++) {
        solve();
    }
}