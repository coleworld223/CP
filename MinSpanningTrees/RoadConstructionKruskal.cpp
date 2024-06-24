#include <bits/stdc++.h>
using namespace std;

using ll = long long;

struct e {
    ll u, v, wt;
    bool operator < (const e& oth) {
        return wt < oth.wt;
    }
    bool operator > (const e& oth) {
        return wt > oth.wt;
    }
    bool operator == (const e& oth) {
        return wt == oth.wt;
    }
    void inp () {
        cin >> u >> v >> wt;
    }
    void print () {
        cout << u << ' ' << v << ' ' << wt << '\n';
    }
};

struct DSU {
    ll n;
    vector <ll> par;
    vector <ll> siz;
    DSU (ll sz) {
        n = sz;
        par.resize(n + 1);
        siz.resize(n + 1, 1);
        for (ll i = 1; i <= n; i += 1) {
            par[i] = i;
        }
    }
    ll find (ll x) {
        if (par[x] == x) return x;
        return par[x] = find (par[x]);
    }
    bool merge (ll x, ll y) {
        x = find (x);
        y = find (y);
        if (x == y) return false;
        if (siz[x] < siz[y]) swap (x, y);
        par[y] = x;
        siz[x] += siz[y];
        return true;
    }
};

void solve () {
    ll n, m;
    cin >> n >> m;

    vector <e> edges (m);

    for (ll i = 0; i < m; i += 1) {
        edges[i].inp();
    }

    sort (edges.begin(), edges.end());

    DSU d (n);

    ll cst = 0, cnt = 0;

    for (auto ed : edges) {
        if (d.merge (ed.u, ed.v)) {
            cst += ed.wt;
            cnt += 1;
        }
    }

    if (cnt != n - 1) {
        cout << "IMPOSSIBLE" << '\n';
        return;
    }

    cout << cst << '\n';
}

int main () {
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int tests = 1;
    // cin >> tests;

    for (int i = 0; i < tests; i ++) {
        solve ();
    }
}