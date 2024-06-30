#include <bits/stdc++.h>
using namespace std;

// https://codeforces.com/contest/600/problem/E

using ll = long long;

struct DS {
    map <ll, ll> cnt, sum;
    void add(ll col, ll tim) {
        if (cnt.count(col)) {
            sum[cnt[col]] -= col;
        }
        cnt[col] += tim;
        sum[cnt[col]] += col;
    }
    void operator +(DS &oth) {
        if (oth.cnt.size() > cnt.size()) {
            swap(cnt, oth.cnt);
            swap(sum, oth.sum);
        }
        for (auto [col, f] : oth.cnt) {
            add(col, f);
        }
    }
    ll res() {
        auto [x, y] = (*(--sum.end()));
        return y;
    }
};

void solve() {
    ll n;
    cin >> n;

    vector <ll> col (n);

    for (ll i = 0; i < n; i++) {
        cin >> col[i];
    }

    vector <vector <ll>> a (n);

    for (ll i = 0; i < n - 1; i++) {
        ll u, v;
        cin >> u >> v;
        u--; v--;
        a[u].push_back(v);
        a[v].push_back(u);
    }

    vector <DS> Info (n);
    vector <ll> res (n);

    function <void (ll, ll)> dfs = [&] (ll u, ll p) {
        Info[u].add(col[u], 1);
        for (ll v : a[u]) if (v != p) {
            dfs(v, u);
            Info[u] + Info[v];
        }
        res[u] = Info[u].res();
    };

    dfs(0, -1);

    for (ll i = 0; i < n; i++) {
        cout << res[i] << ' ';
    }
    cout << '\n';
}

int main() {
    ios_base::sync_with_stdio();cin.tie(0);
    int t = 1;
    // cin >> t;
    for (int i = 0; i < t; i++) {
        solve();
    }
}