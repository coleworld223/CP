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