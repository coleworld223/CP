#include<bits/stdc++.h>
using namespace std;

using ll = long long;
const ll mod = 1e9 + 7;
const ll inf = 1e18;

struct Node {
    Node* leftChild = NULL;
    Node* rightChild = NULL;
    ll leftEnd, rightEnd, nodeValue, nodeLazy;

    Node(ll _l, ll _r) {
        leftEnd = _l;
        rightEnd = _r;
        nodeValue = 0;
        nodeLazy = 0;
    }

    void extend() {
        if (!leftChild && leftEnd + 1 <= rightEnd) {
            ll mid = (leftEnd + rightEnd) >> 1;
            leftChild = new Node(leftEnd, mid);
            rightChild = new Node(mid + 1, rightEnd);
        }
    }

    void updateLazy(ll upd) {
        nodeLazy += upd;
    }

    void pushLazy() {
        if (nodeLazy == 0) return;
        ll upd = nodeLazy;
        nodeValue += nodeLazy;
        nodeLazy = 0;
        if (leftEnd + 1 <= rightEnd) {
            extend();
            leftChild -> updateLazy(upd);
            rightChild -> updateLazy(upd);
        }
    }

    void put(ll qFrom, ll qTill, ll putValue) {
        pushLazy();
        if (leftEnd >= qFrom && rightEnd <= qTill) {
            updateLazy(putValue);
            pushLazy();
            return;
        }
        extend();
        ll mid = (leftEnd + rightEnd) >> 1;
        if (qFrom <= mid) leftChild -> put(qFrom, qTill, putValue);
        if (qTill >= mid + 1) rightChild -> put(qFrom, qTill, putValue);
        leftChild -> pushLazy();
        rightChild -> pushLazy();
        nodeValue = max(leftChild -> nodeValue, rightChild -> nodeValue);
    }

    ll findMax(ll qFrom, ll qTill) {
        pushLazy();
        if (leftEnd >= qFrom && rightEnd <= qTill) return nodeValue;
        extend();
        ll mid = (leftEnd + rightEnd) >> 1;
        ll res = -inf;
        if (qFrom <= mid) res = max(res, leftChild -> findMax(qFrom, qTill));
        if (qTill >= mid + 1) res = max(res, rightChild -> findMax(qFrom, qTill));
        return res;
    }
};

void solve() {
    ll n, m;
    cin >> n >> m;

    vector <ll> l (m), r (m), a (m);
    vector <vector <ll>> add (n + 2), rem (n + 2);

    for (ll i = 0; i < m; i++) {
        cin >> l[i] >> r[i] >> a[i];
        add[l[i]].push_back(i);
        rem[r[i]].push_back(i);
    }

    // dp[i] = (sc_i + dp[j] - (sc_ij))

    Node* root = new Node(0, n);
    root -> put(0, 0, 0);
    ll ans = 0;

    for (ll i = 1, sum = 0; i <= n; i++) {
        for (ll id : add[i]) {
            root -> put(l[id], r[id], -a[id]);
            sum += a[id];
        }
        ll h = root -> findMax(0, i - 1) + sum;
        ans = max(ans, h);
        root -> put(i, i, h);
        for (ll id : rem[i]) {
            sum -= a[id];
            root -> put(l[id], r[id], a[id]);
        }
    }

    cout << ans << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);cin.tie(0);
    int tests = 1;
    // cin >> tests;
    for (int i = 0; i < tests; i++) {
        solve();
    }
}