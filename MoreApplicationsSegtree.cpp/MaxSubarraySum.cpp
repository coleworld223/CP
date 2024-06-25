#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const int mod = 1e9 + 7;
const ll def = -1e18;

struct cell {
    ll left_max, right_max, mx, tot;
    cell() {
        left_max = right_max = tot = def;
    }
    cell operator+(const cell oth) {
        if (left_max == def) return oth;
        cell res;
        res.left_max = max (left_max, tot + oth.left_max);
        res.right_max = max (oth.right_max, oth.tot + right_max);
        res.mx = max ({mx, oth.mx, right_max + oth.left_max});
        res.tot = tot + oth.tot;
        return res;
    }
};

struct Node {
    Node* lft = NULL;
    Node* rht = NULL;
    ll l, r;
    cell v;

    Node(ll _l, ll _r) {
        l = _l;
        r = _r;
    }

    void extend() {
        if (!lft && l + 1 <= r) {
            ll mid = (l + r) >> 1;
            lft = new Node(l, mid);
            rht = new Node(mid + 1, r);
        }
    }

    void put(ll qp, ll val) {
        if (l == r) {
            v.left_max = v.right_max = v.tot = v.mx = val;
            return;
        }
        extend();
        ll mid = (l + r) >> 1;
        if (mid >= qp) lft -> put(qp, val);
        else rht -> put(qp, val);
        v = (lft -> v + rht -> v);
    }

    cell qry(ll ql, ll qr) {
        if (l >= ql && r <= qr) return v;
        extend();
        ll mid = (l + r) >> 1;
        cell res;
        if (ql <= mid) res = res + (lft -> qry(ql, qr));
        if (qr >= mid + 1) res = res + (rht -> qry(ql, qr));
        return res;
    }
};

void solve() {
    ll n, m;
    cin >> n >> m;

    Node* root = new Node(0, n);

    for (ll i = 0; i < n; i += 1) {
        ll x;
        cin >> x;
        root -> put(i, x);
    }

    while (m--) {
        ll p, v;
        cin >> p >> v;
        p--;
        root -> put(p, v);
        cell res = root -> qry(0, n);
        cout << res.mx << '\n';
    }

}

int main() {
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int tests = 1;
    // cin >> tests;

    for (int i = 0; i < tests; i ++) {
        solve ();
    }
}