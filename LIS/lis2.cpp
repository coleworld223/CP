#include<bits/stdc++.h>
using namespace std;

using ll = long long;

struct Node {
    Node* lft = NULL;
    Node* rht = NULL;
    ll l, r, v;
    Node(ll _l, ll _r) {
        l = _l;
        r = _r;
        v = 0;
    }
    void extend() {
        if (!lft && l + 1 <= r) {
            ll mid = (l + r) >> 1;
            lft = new Node(l, mid);
            rht = new Node(mid + 1, r);
        }
    }
    void put(ll i, ll x) {
        if (l == r) {
            v = x;
            return;
        }
        extend();
        ll mid = (l + r) >> 1;
        if (i <= mid) lft -> put(i, x);
        else rht -> put(i, x);
        v = max(lft -> v, rht -> v);
    }
    ll qry(ll ql, ll qr) {
        if (l >= ql && r <= qr) return v;
        extend();
        ll mid = (l + r) >> 1;
        ll res = 0;
        if (ql <= mid) res = max(res, lft -> qry(ql, qr));
        if (qr >= mid + 1) res = max(res, rht -> qry(ql, qr));
        return res;
    }
};

void solve() {
    ll n;
    cin >> n;

    vector <ll> a (n);

    for (ll i = 0; i < n; i++) {
        cin >> a[i];
    }

    Node* root = new Node(0, 1e18);

    for (ll i = 0; i < n; i++) {
        ll x = max(1ll, root -> qry(a[i], a[i]));
        if (a[i]) x = max(x, root -> qry(0, a[i] - 1) + 1);
        root -> put(a[i], x);
    }

    ll res = root -> qry(0, 1e18);
    cout << res << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);cin.tie(0);
    int t = 1;
    // cin >> t;
    for (int i = 0; i < t; i++) {
        solve();
    }
}