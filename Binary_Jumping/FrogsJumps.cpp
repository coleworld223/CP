#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const ll LOG = 20;  // LOG (M)

// this is a NlogM solution, utilising the fact that cycles as root graphs are there we can also write a NLOGN solution 

void solve() {
    ll n, k, m;
    cin >> n >> k >> m;

    vector <ll> p (n);

    for (ll i = 0; i < n; i++) {
        cin >> p[i];
    }

    vector <vector <ll>> nxt (n, vector <ll> (LOG, -1));

    for (ll i = 0, l = 0, r = k; i < n; i++) {
        while (r + 1 < n && p[r + 1] - p[i] < p[i] - p[l]) {
            l++;
            r++;
        }
        nxt[i][0] = (p[i] - p[l] >= p[r] - p[i] ? l : r); 
    }

    for (ll bit = 1; bit < LOG; bit++) {
        for (ll i = 0; i < n; i++) {
            nxt[i][bit] = nxt[nxt[i][bit - 1]][bit - 1];
        }
    }

    for (ll i = 0; i < n; i++) {
        ll u = i;
        for (ll bit = 0; bit < LOG; bit++) if (m >> bit & 1) {
            u = nxt[u][bit];
        }
        cout << u + 1 << ' ';
    }
    cout << "\n";
}

int main() {
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int tests = 1;
    // cin >> tests;
    for (int i = 0; i < tests; i += 1) {
        solve();
    }
}