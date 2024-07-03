#include <bits/stdc++.h>
using namespace std;

using ll = long long;

struct DS {
    set <array <ll, 2>> st;
    void add(ll x, ll i) {
        if (st.count({x, i})) st.erase({x, i});
        else st.insert({x, i});
    }
    void operator +(DS& oth) {
        if (oth.st.size() > st.size())
            swap(oth.st, st);
        for (auto [x, i] : oth.st) {
            add(x, i);
        }
    }
    ll res() {
        if (st.empty()) return -1;
        auto [x, y] = *st.begin();
        return x;
    }
};

void solve() {
    ll n, m;
    cin >> n >> m;

    vector <vector <array <ll, 2>>> a (n);

    for (ll i = 0; i < n - 1; i++) {
        ll u, v;
        cin >> u >> v;
        --u; --v;
        a[u].push_back({v, i});
        a[v].push_back({u, i});
    }

    vector <vector <array <ll, 2>>> val (n);

    for (ll i = 0; i < m; i++) {
        ll u, v, x;
        cin >> u >> v >> x;
        u--; v--;
        val[u].push_back({x, i});
        val[v].push_back({x, i});
    }

    vector <DS> Info (n);
    vector <ll> res (n);

    function <void (ll, ll, ll)> dfs = [&] (ll u, ll p, ll id) {
        for (auto [x, i] : val[u]) {
            Info[u].add(x, i);
        }
        for (auto [v, id] : a[u]) if (v != p) {
            dfs(v, u, id);
            Info[u] + Info[v];
        }
        if (id != -1) res[id] = Info[u].res();
    };

    dfs(0, -1, -1);

    for (ll i = 0; i < n - 1; i++) {
        cout << res[i] << '\n';
    }
}

int main() {
    freopen("disrupt.in", "r", stdin);
    freopen("disrupt.out", "w", stdout);
    ios_base::sync_with_stdio();cin.tie(0);
    int t = 1;
    // cin >> t;
    for (int i = 0; i < t; i++) {
        solve();
    }
}