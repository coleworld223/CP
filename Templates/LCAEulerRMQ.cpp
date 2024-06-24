#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const ll inf = 1e18;

struct RMQ {
    vector <vector <ll>> tab;
    vector <ll> a;
    ll n;
    ll LOG = 0;
    ll min_index (ll x, ll y) { // modify this for any operations
        return (a[x] < a[y] ? x : y);
    }
    RMQ (vector <ll> &_a) {
        a = _a;
        while ((1 << LOG) < (ll) a.size()) LOG += 1;
        LOG += 1;
        n = a.size();
        tab.resize(n, vector <ll> (LOG, -1));
        for (ll bit = 0; bit < LOG; bit += 1) {
            if (bit == 0) {
                for (ll i = 0; i < n; i += 1) {
                    tab[i][bit] = i;
                }
            }
            else {
                for (ll i = 0; i + (1 << bit) <= n; i += 1) {
                    tab[i][bit] = min_index (tab[i][bit - 1], tab[i + (1 << (bit - 1))][bit - 1]);
                }
            }
        }
    }

    ll qry (ll l, ll r) {
        ll lg = 31 - __builtin_clz (r - l + 1);
        return min_index (tab[l][lg], tab[r - (1 << lg) + 1][lg]);
    }
};

void solve () {
    ll n, q;
    cin >> n >> q;

    vector <vector <ll>> a (n);

    for (ll i = 1; i < n; i += 1) {
        ll x;
        cin >> x;
        x--;
        a[i].push_back(x);
        a[x].push_back(i);
    }

    vector <ll> euler;
    vector <ll> dep (n);
    vector <ll> in (n);

    function <void (ll, ll)> dfs = [&] (ll u, ll p) {
        euler.push_back(u);
        in[u] = euler.size() - 1;
        for (ll v : a[u]) if (v != p) {
            dep[v] = dep[u] + 1;
            dfs (v, u);
            euler.push_back(u);
        }
    };

    dfs (0, -1);

    vector <ll> dep_array (2 * n);

    for (ll i = 0; i < 2 * n; i += 1) {
        dep_array[i] = dep[euler[i]];
    }

    RMQ rmq (dep_array);

    while (q--) {
        ll u, v;
        cin >> u >> v;
        u--; v--;
        if (in[u] > in[v]) swap (u, v);
        ll id = rmq.qry (in[u], in[v]);
        cout << euler[id] + 1 << '\n';
    }
}

int main () {
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int tests = 1;
    // cin >> tests;

    for (int i = 0; i < tests; i ++) {
        solve ();
    }
}