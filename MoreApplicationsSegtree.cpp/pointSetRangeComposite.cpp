#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const int mod = 998244353;

ll def = 0;
struct cell {
    ll a, b;
    cell() {
        a = b = def;
    }
    cell(ll _a, ll _b) {
        a = _a;
        b = _b;
    }
    ll compute(ll x) {
        return (a * x + b) % mod;
    }
    cell operator +(cell oth) {
        if (a == def) return oth;
        cell res;
        res.a = (a * oth.a) % mod;
        res.b = (oth.a * b + oth.b) % mod;
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

    void put(ll p, cell x) {
        if (l == r) {
            v = x;
            return;
        }
        extend();
        ll mid = (l + r) >> 1;
        if (p <= mid) lft -> put(p, x);
        else rht -> put(p, x);
        v = (lft -> v + rht -> v);
    }

    cell qry(ll ql, ll qr) {
        if (l >= ql && r <= qr) return v;
        extend();
        ll mid = (l + r) >> 1;
        cell res;
        if (mid >= ql) res = (res + lft -> qry(ql, qr));
        if (qr >= mid + 1) res = (res + rht -> qry(ql, qr));
        return res;
    }
};

void solve() {
    ll n, q;
    cin >> n >> q;

    Node* root = new Node(0, n);

    for (ll i = 0; i < n; i += 1) {
        ll x, y;
        cin >> x >> y;
        cell t(x, y);
        root -> put(i, t);
    }

    while (q--) {
        ll t;
        cin >> t;
        if (t == 0) {
            ll id, c, d;
            cin >> id >> c >> d;
            cell t(c, d);
            root -> put(id, t);
        }
        else {
            ll l, r, x;
            cin >> l >> r >> x;
            r--;
            cell res = root -> qry(l, r);
            ll ans = res.compute(x % mod);
            cout << ans << '\n';
        }
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