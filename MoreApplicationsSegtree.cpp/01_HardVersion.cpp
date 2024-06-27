#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const ll inf = 1e18;


struct cell {
    ll len;
    ll ct0_good;
    ll ct0_tot;
    cell() {
        len = ct0_tot = ct0_good = 0;
    }
    cell(ll x, ll y, ll z) {
        len = x, ct0_good = y, ct0_tot = z;
    }
    cell operator +(cell oth) {
        if (len == 0) return oth;
        cell res;
        res.len = len + oth.len;
        res.ct0_good = ct0_good + oth.ct0_good + min(ct0_tot - ct0_good, (oth.len - oth.ct0_tot) - oth.ct0_good);
        res.ct0_tot = ct0_tot + oth.ct0_tot;
        return res;
    }
    void pr() {
        cout << len << ' ' << ct0_good << ' ' << ct0_tot << '\n';
    }
};

cell one(1, 0, 0);
cell zer(1, 0, 1);

struct Node{
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

    void upd(ll x) {
        if (x == 1) v = one;
        else v = zer; 
    }

    void put(ll p, ll x) {
        if (l == r) {
            upd(x);
            return;
        }
        extend();
        ll mid = (l + r) >> 1;
        if (p <= mid) lft -> put(p, x);
        else rht -> put(p, x);
        v = lft -> v + rht -> v;
    }

    cell qry(ll ql, ll qr) {
        if (l >= ql && r <= qr) return v;
        extend();
        cell res;
        ll mid = (l + r) >> 1;
        if (ql <= mid) res = (res + lft -> qry(ql, qr));
        if (qr >= mid + 1) res = (res + rht -> qry(ql, qr));
        return res; 
    }
};

void solve() {
    string s;
    cin >> s;
    ll n = s.size();

    Node* root = new Node(0, n);
    for (ll i = 0; i < n; i += 1) {
        root -> put(i, (s[i] - '0'));
    }

    ll q;
    cin >> q;

    while (q--) {
        ll t;
        cin >> t;
        if (t == 1) {
            ll x;
            cin >> x;
            x--;
            if (s[x] == '0') s[x] = '1';
            else s[x] = '0';
            root -> put(x, (s[x] - '0'));
        }
        else {
            ll l, r;
            cin >> l >> r;
            l--; r--;
            cell res = root -> qry(l, r);
            ll len = r - l + 1;
            ll ans = len - 2 * (res.ct0_good);
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