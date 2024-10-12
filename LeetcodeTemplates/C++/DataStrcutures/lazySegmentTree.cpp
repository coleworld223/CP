#include <bits/stdc++.h>
using namespace std;

using i32 = int;
using i64 = long long;

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

struct node {
  i64 sum = 0;
};

node merge(node a, node b) {
  node res;
  res.sum = a.sum + b.sum;
  return res;
}

struct U {
  i64 lzAd = 0;
  i64 lzSet = 0;
  void combine(U &oth) {
    if (oth.lzAd != 0) {
      if (lzSet != 0) {
        lzSet += oth.lzAd;
      }
      else {
        lzAd += oth.lzAd;
      }
    }
    else if (oth.lzSet != 0) {
      lzSet = oth.lzSet;
      lzAd = 0;
    }
  }
};

void solve() {
  i32 N, Q;
  cin >> N >> Q;

  vector <i32> A (N);
  for (i32 i = 0; i < N; ++i) {
    cin >> A[i];
  }

  segmentTree <node, U> tree;
  tree.init(N);

  for (i32 i = 0; i < N; ++i) {
    U cur = {0, A[i]};
    tree.upd(0, 0, N - 1, i, i, cur);
  }

  while (Q--) {
    i32 type;
    cin >> type;

    if (type == 1) {
      i32 l, r, x;
      cin >> l >> r >> x;
      l--; r--;
      U up {x, 0};
      tree.upd(0, 0, N - 1, l, r, up);
    }
    else if (type == 2) {
      i32 l, r, x;
      cin >> l >> r >> x;
      l--; r--;
      U up {0, x};
      tree.upd(0, 0, N - 1, l, r, up);
    }
    else {
      i32 l, r;
      cin >> l >> r;
      l--; r--;
      node res = tree.qry(0, 0, N - 1, l, r);
      cout << res.sum << '\n';
    }
  }
}

int main() {
  ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
  i32 tests = 1;
  // cin >> tests;
  for (i32 test = 0; test < tests; ++test) {
    solve();
  }
}