using ll = long long;
const int mod = 1e9 + 7;
const ll inf = 1e18;

struct cell {
    ll l, r, mx, wh;
    cell () {
        l = r = mx = wh = -inf;
    }
    bool operator == (const cell& oth) {
        return (oth.l == l && oth.r == r && oth.mx == mx && oth.wh == wh);
    }
};
cell def_cell;

cell merge (cell a, cell b) {
    if (a == def_cell) return b;
    cell res;
    res.l = max (a.l, a.wh + b.l);
    res.r = max (b.r, b.wh + a.r);
    res.mx = max ({a.mx, b.mx, a.r + b.l});
    res.wh = a.wh + b.wh;
    return res;
}

ll def_val = 0, def_lzy = 0;
struct Node {
    Node* lft = NULL;
    Node* rht = NULL;
    ll l, r;
    cell val;

    Node (ll _l, ll _r) {
        l = _l;
        r = _r;
    }

    void extend () {
        if (!lft && l + 1 <= r) {
            ll mid = (l + r) >> 1;
            lft = new Node (l, mid);
            rht = new Node (mid + 1, r);
        }
    }

    void upd (ll p, ll v) {
        if (l == r) {
            val.l = val.r = val.mx = v;
            val.wh = v;
            return;
        }
        extend();
        ll mid = (l + r) >> 1;
        if (p <= mid) lft -> upd (p, v);
        else rht -> upd (p, v);
        val = merge (lft -> val, rht -> val);
    }

    cell qry (ll ql, ll qr) {
        if (l >= ql && r <= qr) return val;
        extend();
        ll mid = (l + r) >> 1;
        cell res;
        if (mid >= ql) res = merge (res, lft -> qry (ql, qr));
        if (mid + 1 <= qr) res = merge (res, rht -> qry (ql, qr));
        return res; 
    }
};