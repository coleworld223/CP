#include <bits/stdc++.h>
using namespace std;

//https://usaco.org/index.php?page=viewproblem2&cpid=696

#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

template <class T>
using Oset = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

using ll = long long;

struct DS {
    Oset <ll> st;
    void add (ll x) {
        st.insert(x);
    }
    void operator +(DS& oth) {
        if (oth.st.size() > st.size()) 
            st.swap(oth.st);
        for (ll x : oth.st) {
            add(x);
        }
    }
    ll res(ll x) {
        ll sz = st.size();
        ll id = st.order_of_key(x);
        return max(0ll, sz - id - 1);
    }
};

void solve() {
    ll n;
    cin >> n;

    vector <ll> p (n);

    for (ll i = 0; i < n; i++) {
        cin >> p[i];
    }

    vector <vector <ll>> a (n);

    for (ll i = 1; i < n; i++) {
        ll par;
        cin >> par;
        par--;
        a[par].push_back(i);
    }

    vector <DS> Info (n);
    vector <ll> res (n);

    function <void (ll)> dfs = [&] (ll u) {
        Info[u].add(p[u]);
        for (ll v : a[u]) {
            dfs(v);
            Info[u] + Info[v];
        }
        res[u] = Info[u].res(p[u]);
    };

    dfs(0);

    for (ll i = 0; i < n; i++) {
        cout << res[i] << '\n';
    }
}

int main() {
    freopen("promote.in", "r", stdin);
    freopen("promote.out", "w", stdout);
    ios_base::sync_with_stdio();cin.tie(0);
    int t = 1;
    // cin >> t;
    for (int i = 0; i < t; i++) {
        solve();
    }
}