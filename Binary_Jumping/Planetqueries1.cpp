#include <bits/stdc++.h>
using namespace std;
 
using ll = int;
 
ll nxt[200001][31];
ll LOG = 31;
 
void solve() {
    ll n, q;
    cin >> n >> q;
 
    for (ll i = 0; i < n; i++) {
        cin >> nxt[i][0];
        nxt[i][0]--;
    }
 
    for (ll bit = 1; bit < LOG; bit++) {
        for (ll u = 0; u < n; u++) {
            nxt[u][bit] = nxt[nxt[u][bit - 1]][bit - 1];
        }
    }
 
    while (q--) {
        ll u, d;
        cin >> u >> d;
        u--;
        for (ll bit = 0; bit < LOG; bit++) if (d >> bit & 1) {
            u = nxt[u][bit];
        }
        cout << u + 1 << '\n';
    }
}
 
int main() {
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int tests = 1;
    // cin >> tests;
    for (int i = 0; i < tests; i += 1) {
        solve();
    }
}