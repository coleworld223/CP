#include<bits/stdc++.h>
using namespace std;

using ll = long long;

void solve() {
    ll n;
    cin >> n;

    vector <ll> a (n);

    for (ll i = 0; i < n; i++) {
        cin >> a[i];
    }

    vector <ll> lis;

    for (ll i = 0; i < n; i++) {
        if (lis.empty()) lis.push_back(a[i]);
        else {
            ll id = lower_bound(lis.begin(), lis.end(), a[i]) - lis.begin();
            if (id >= lis.size()) lis.push_back(a[i]);
            else lis[id] = a[i]; 
        }
    }

    cout << (ll) lis.size() << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);cin.tie(0);
    int t = 1;
    // cin >> t;
    for (int i = 0; i < t; i++) {
        solve();
    }
}