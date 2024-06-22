using ll = long long;

// lazy dyanamic segment tree template
ll def_val = 0, def_lzy = 0;
struct Node {
    Node* lft = NULL;
    Node* rht = NULL;
    ll l, r, val, lzy;

    Node (ll _l, ll _r) {
        l = _l;
        r = _r;
        val = def_val;
        lzy = def_lzy; 
    }

    void extend () {
        if (!lft && l + 1 <= r) {
            ll mid = (l + r) >> 1;
            lft = new Node (l, mid);
            rht = new Node (mid + 1, r);
        }
    }

    void push () {
        if (lzy == def_lzy) return;
        val += (r - l + 1) * lzy;
        extend ();
        if (l + 1 <= r) {
            lft -> lzy += lzy;
            rht -> lzy += lzy;
        }
        lzy = 0;
    }

    void upd (ll x, ll y, ll v) {
        push ();
        if (l >= x && r <= y) {
            lzy += v;
            push ();
            return;
        }
        extend ();
        ll mid = (l + r) >> 1;
        if (mid >= x) lft -> upd (x, y, v);
        if (mid + 1 <= y) rht -> upd (x, y, v);
        val = lft -> val + rht -> val;
    }

    ll qry (ll ql, ll qr) {
        push ();
        if (l >= ql && r <= qr) return val;
        extend();
        ll mid = (l + r) >> 1;
        ll res = 0;
        if (mid >= ql) res += lft -> qry (ql, qr);
        if (mid + 1 <= qr) res += rht -> qry (ql, qr);
        return res;
    }
};