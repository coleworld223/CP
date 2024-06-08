#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const int sz = 1e5;

void solve () {
    ll n, m;
    cin >> n >> m;

    vector <vector <ll>> a (n);

    vector <ll> deg (n), tp, dp (n), frm (n, -1);

    for (ll i = 0; i < m; i += 1) {
        ll u, v;
        cin >> u >> v;
        u--; v--;
        deg[v] += 1;
        a[u].push_back(v);
    }

    queue <ll> q;

    for (ll i = 0; i < n; i += 1) if (deg[i] == 0) {
        q.push (i);
    }

    while (!q.empty()) {
        ll u = q.front();
        q.pop();
        tp.push_back(u);
        for (ll v : a[u]) {
            deg[v]--;
            if (deg[v] == 0) {
                q.push (v);
            }
        }
    }

    for (ll i = n - 1; i >= 0; i--) {
        ll _ = tp[i];
        for (ll v : a[_]) {
            if (dp[_] < dp[v] + 1) {
                dp[_] = dp[v] + 1;
                frm[_] = v;
            }
        }
    }

    ll ans = *max_element(dp.begin(), dp.end());

    cout << ans << '\n';

    //path 

    // vector <ll> pth;

    // for (ll i = 0; i < n; i += 1) {
    //     if (dp[i] == ans) {
    //         while (i != -1) {
    //             pth.push_back(i);
    //             i = frm[i];
    //         }
    //         break;
    //     }
    // }

    // for (ll x : pth) {
    //     cout << x << ' ';
    // }
    // cout << '\n'; 
}

int main () {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int no_of_tests = 1;
    // cin >> no_of_tests;
    for (int test_no = 0; test_no < no_of_tests; test_no += 1) {
        solve ();
    }
}