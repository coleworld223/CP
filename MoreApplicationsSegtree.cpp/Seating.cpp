#include <bits/stdc++.h>
using namespace std;

using ll = long long;

ll def = -1;
struct cell {
    ll pref, suf, seg, len;
    cell() {
        pref = suf = seg = len = def;
    }
    cell(ll p, ll s, ll se, ll l) {
        pref = p;
        suf = s;
        seg = se;
        len = l;
    }
    cell operator +(cell oth) {
        if (len == -1) return oth;
        cell res;
        res.pref = max(pref, (pref == len ? pref + oth.pref : 0));
        res.suf = max(oth.suf, (oth.suf == oth.len ? oth.suf + suf : 0));
        res.len = len + oth.len;
        res.seg = max({seg, oth.seg, suf + oth.pref});
        return res;
    }
    void operator =(cell oth) {
        pref = oth.pref;
        suf = oth.suf;
        seg = oth.seg;
        len = oth.len;
    }
    void pr() {
        cout << pref << ' ' << suf << ' ' << seg << ' ' << len << '\n';
    }
};

struct Node {
    Node* lft = NULL;
    Node* rht = NULL;
    ll l, r;
    cell v;
    ll u;
    Node(ll _l, ll _r) {
        l = _l;
        r = _r;
        u = def;
    }

    void extend() {
        if (!lft && l + 1 <= r) {
            ll mid = (l + r) >> 1;
            lft = new Node(l, mid);
            rht = new Node(mid + 1, r);
        }
    }

    void push() {
        if (u == -1) return;
        if (u == 0) {
            ll len = r - l + 1;
            cell _(len, len, len, len);
            v = _;
        }
        else {
            ll len = r - l + 1;
            cell _(0, 0, 0, len);
            v = _;
        }
        if (l + 1 <= r) {
            extend();
            lft -> u = u;
            rht -> u = u;
        }
        u = -1;
    }

    void put(ll ql, ll qr, ll u1) {
        push();
        if (l >= ql && r <= qr) {
            u = u1;
            push();
            return;
        }
        extend();
        lft -> push();
        rht -> push();
        ll mid = (l + r) >> 1;
        if (ql <= mid) lft -> put(ql, qr, u1);
        if (mid + 1 <= qr) rht -> put(ql, qr, u1);
        v = ((lft -> v) + (rht -> v));
    }

    cell find (ll ql, ll qr) {
        push();
        if (l >= ql && r <= qr) return v;
        extend();
        ll mid = (l + r) >> 1;
        cell res;
        if (ql <= mid) res = (res + (lft -> find(ql, qr)));
        if (qr >= mid + 1) res = (res + (rht -> find(ql, qr)));
        return res;
    }

    ll qry(ll get) {
        push();
        if (v.seg < get) return -1;
        if (l == r) return l;
        ll mid = (l + r) >> 1;
        lft -> push();
        rht -> push();
        ll x = lft -> qry(get);
        if (x != -1) return x;
        if ((lft -> v).suf + (rht -> v).pref >= get) return (mid - (lft -> v).suf + 1);
        return rht -> qry(get);
    }
};

void solve() {
    ll n, q;
    cin >> n >> q;

    Node* root = new Node(1, n);
    ll res = 0;

    root -> put(1, n, 0);

    while(q--) {
        char x;
        cin >> x;
        if (x == 'A') {
            ll p;
            cin >> p;
            ll l = root -> qry(p);
            if (l == -1) res++;
            else root -> put(l, l + p - 1, 1);
        }
        else {
            ll l, r;
            cin >> l >> r;
            root -> put(l, r, 0);
        }
    }
    cout << res << '\n';
}

int main() {
    freopen("seating.in", "r", stdin);
    freopen("seating.out", "w", stdout);
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int tests = 1;
    // cin >> tests;
    for (int i = 0; i < tests; i += 1) {
        solve();
    }
}