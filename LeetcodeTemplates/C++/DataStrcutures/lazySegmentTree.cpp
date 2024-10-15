template <class node, class U>
class segmentTree {
public:
  i32 N;
  vector <node> tree;
  vector <U> lazy;
public:
  segmentTree() {}
  void init(i32 N) {
    this -> N = N;
    tree.resize(4 * N);
    lazy.resize(4 * N);
  }
  void pull(i32 p) {
    tree[p] = merge(tree[2 * p + 1], tree[2 * p + 2]);
  }
  void push(i32 p, i32 l, i32 r) {
    apply(p, l, r);
    if (l + 1 <= r) {
      lazy[2 * p + 1].combine(lazy[p]);
      lazy[2 * p + 2].combine(lazy[p]);
    }
    lazy[p] = U();
  }
  void apply(i32 p, i32 l, i32 r) {
    if (lazy[p].lzAd) {
      tree[p].sum += (r - l + 1) * 1LL * lazy[p].lzAd;
    }
    else if (lazy[p].lzSet) {
      tree[p].sum = (r - l + 1) * 1LL * lazy[p].lzSet;
    }
  }
  void build(i32 p, i32 l, i32 r, vector <i32> &build_vec) {
    if (l == r) { tree[p] = build_vec[l]; return; }
    i32 mid = (l + r) >> 1;
    build(2 * p + 1, l, mid, build_vec);
    build(2 * p + 2, mid + 1, r, build_vec);
    pull(p);
  }
  void upd(i32 p, i32 l, i32 r, i32 ql, i32 qr, U &up) {
    push(p, l, r);
    if (l > qr || r < ql) return;
    if (l >= ql && r <= qr) { lazy[p].combine(up); push(p, l, r); return; }
    i32 mid = (l + r) >> 1;
    upd(2 * p + 1, l, mid, ql, qr, up);
    upd(2 * p + 2, mid + 1, r, ql, qr, up);
    pull(p);
  }
  node qry(i32 p, i32 l, i32 r, i32 ql, i32 qr) {
    push(p, l, r);
    if (l > qr || r < ql) return node();
    if (l >= ql && r <= qr) { return tree[p]; }
    i32 mid = (l + r) >> 1;
    node res = node();
    res = merge(res, qry(2 * p + 1, l, mid, ql, qr));
    res = merge(res, qry(2 * p + 2, mid + 1, r, ql, qr));
    return res;
  }
};