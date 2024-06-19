// https://codeforces.com/contest/1842/submission/266402624

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const ll inf = 1e18;

void solve () {
    ll n;
    cin >> n;

    vector <vector <ll>> a (n);

    for (ll i = 0; i < n - 1; i += 1) {
        ll u, v;
        cin >> u >> v;
        u--; v--;
        a[u].push_back(v);
        a[v].push_back(u);
    }

    vector <ll> ans (n + 1, inf);
    ans[0] = 0;

    for (ll root = 0; root < n; root += 1) {
        queue <ll> q;
        q.push (root);
        vector <ll> dis (n, -1);
        ll cnt = 0;
        dis[root] = 0;
        ll sm = 0;
        while (!q.empty()) {
            ll u = q.front();
            q.pop();
            cnt += 1;
            sm += dis[u];
            ans[cnt] = min (ans[cnt], sm);
            for (ll v : a[u]) if (dis[v] == -1) {
                dis[v] = dis[u] + 1;
                q.push (v);
            }
        }
    }

    for (ll i = 0; i <= n; i += 1) {
        cout << (n - 1) * i - 2 * ans[i] << ' ';
    }
    cout << '\n';
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