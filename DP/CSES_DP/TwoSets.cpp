#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const ll inf = 1e18;

const int mod = 1e9 + 7;

ll binpow (ll a, ll b) {
    ll mul = a;
    ll res = 1;
    for (ll bit = 0; bit < 31; bit += 1) {
        if (b >> bit & 1) res *= mul;
        res %= mod;
        mul *= mul;
        mul %= mod;
    }
    return res;
}

ll inv (ll a) {
    return binpow (a, mod - 2);
}

void solve () {
    ll n;
    cin >> n;

    ll S = n * (n + 1) / 2;

    vector <ll> sum (S + 1);

    sum[0] = 1;

    for (ll x = 1; x <= n; x += 1) {
        for (ll s = S; s >= 0; s--) if (s - x >= 0) {
            sum[s] += sum[s - x];
            sum[s] %= mod;
        }
    } 

    if (S % 2 != 0) cout << 0 << '\n';
    else {
        sum[S / 2] *= inv (2);
        cout << sum[S / 2] % mod << '\n';
    }
}

int main () {
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int tests = 1;
    // cin >> tests;

    for (int i = 0; i < tests; i += 1) {
        solve ();
    }
}