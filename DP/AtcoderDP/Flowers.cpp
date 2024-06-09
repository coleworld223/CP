#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const int sz = 1e9;

//Dyanamic segment tree template to avoid coordinate compression
struct node {
    node* l = NULL;
    node* r = NULL;
    ll lft, rht;
    ll val;

    node (ll lft1, ll rht1, ll val1) {
        lft = lft1; rht = rht1; val = val1; 
    }

    void extend () {
        if (!l && lft + 1 <= rht) {
            ll mid = (lft + rht) >> 1;
            l = new node (lft, mid, 0);
            r = new node (mid + 1, rht, 0);
        }
    }

    void put (ll p, ll x) {
        if (lft == rht) {
            val = x; return;
        }
        extend();
        ll mid = (lft + rht) >> 1;
        if (p <= mid) l -> put (p, x);
        else r -> put (p, x);
        val = max (l -> val, r -> val);
    }

    ll qry (ll ql, ll qr) {
        if (lft >= ql && rht <= qr) {
            return val;
        }
        extend();
        ll mid = (lft + rht) >> 1;
        ll res = 0;
        if (ql <= mid) res = max (res, l -> qry (ql, qr));
        if (qr >= mid + 1) res = max (res, r -> qry (ql, qr));
        return res;
    }
};

void solve () {
    ll n;
    cin >> n;

    vector <ll> h (n), a (n);

    for (ll i = 0; i < n; i += 1) {
        cin >> h[i];
    }

    for (ll i = 0; i < n; i += 1) {
        cin >> a[i];
    }

    node* root = new node (0, sz + 1, 0);

    for (int i = 0; i < n; i += 1) {
        ll res = 0;
        if (h[i] > 0) res = max (res, root -> qry (0, h[i] - 1));
        res += a[i];
        root -> put (h[i], res);
    }

    ll res = root -> qry (0, sz);

    cout << res << '\n';
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