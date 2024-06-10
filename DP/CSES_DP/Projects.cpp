#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const ll sz = 1e9;

//Dynamic segment tree
struct node {
    node* lft_ptr = NULL;
    node* rht_ptr = NULL;
    ll lft, rht, val;

    node (ll l, ll r, ll v) {
        lft = l;
        rht = r;
        val = v;
    }

    void extend () {
        if (!lft_ptr && lft + 1 <= rht) {
            ll mid = (lft + rht) >> 1;
            lft_ptr = new node (lft, mid, 0);
            rht_ptr = new node (mid + 1, rht, 0);
        }
    }

    void put (ll p, ll x) {
        if (lft == rht) {
            val = x; return;
        }
        extend ();
        ll mid = (lft + rht) >> 1;
        if (p <= mid) lft_ptr -> put (p, x);
        else rht_ptr -> put (p, x);
        val = max (lft_ptr -> val, rht_ptr -> val);
    }

    ll qry (ll l, ll r) {
        if (lft >= l && rht <= r) return val;
        extend();
        ll mid = (lft + rht) >> 1;
        ll res = 0;
        if (l <= mid) res = max (res, lft_ptr -> qry (l, r));
        if (r >= mid + 1) res = max (res, rht_ptr -> qry (l, r));
        return res; 
    }
};

void solve () {
    ll n;
    cin >> n;

    vector <array <ll, 3>> eve (n);

    for (ll i = 0; i < n; i += 1) {
        cin >> eve[i][1] >> eve[i][0] >> eve[i][2];
    }

    sort (eve.begin(), eve.end());

    node* root = new node (0, sz, 0);

    for (auto ele : eve) {
        ll e = ele[0], s = ele[1], pts = ele[2];
        ll q = 0;
        if (s - 1 >= 0) {
            q = max (q, root -> qry (0, s - 1));
        }
        q += pts;
        ll put = max (q, root -> qry (e, e));
        root -> put (e, put);
    }

    ll res = root -> qry (0, sz);

    cout << res << '\n';
}

int main () {
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int tests = 1;
    // cin >> tests;

    for (int i = 0; i < tests; i += 1) {
        solve ();
    }
}