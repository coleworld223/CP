#include <bits/stdc++.h>
using namespace std;

using ll = int;

struct BinaryLiftingTree {
    ll LOG;
    ll n;
    vector <vector <ll>> up;
    // Requires a parent array
    BinaryLiftingTree(vector <ll>& _par) {
        n = _par.size();
        LOG = ceil(log2(n + 1)) + 1;
        up.resize(n, vector <ll> (LOG, -1));
        for (ll i = 0; i < n; i++) {
            up[i][0] = _par[i];
        }
        work();
    }

    void work() {
        for (ll bit = 1; bit < LOG; bit++) {
            for (ll u = 0; u < n; u++) {
                if (up[u][bit - 1] != -1) up[u][bit] = up[up[u][bit - 1]][bit - 1];
            }
        }
    }

    void go_up(ll &u, ll k) {
        for (ll bit = 0; bit < LOG; bit++) if ((k >> bit & 1) && u != -1) {
            u = up[u][bit];
        }
    }
};

void solve() {
    ll n, q;
    cin >> n >> q;

    vector <ll> p (n);
    vector <vector <ll>> b (n);

    for (ll i = 0; i < n; i++) {
        cin >> p[i];
        b[--p[i]].push_back(i);
    }

    vector <ll> cycId (n, -1), cycNo (n, -1), len (n, -1);
    ll id = 0;

    for (ll i = 0; i < n; i++) if (cycId[i] == -1) {
        ll at = i;
        vector <ll> path = {i};
        cycId[at] = -2;
        while (cycId[p[at]] == -1) {
            at = p[at];
            path.push_back(at);
            cycId[at] = -2;
        }

        if (cycId[p[at]] == -2) {
            bool cyc = 0;
            ll cnt = 0;
            for (ll x : path) {
                cyc = (cyc | p[at] == x);
                if (cyc) cycNo[x] = cnt++;
                cycId[x] = id;
            }
            len[id] = cnt;
            id++;
        }
        else {
            for (ll x : path) {
                cycId[x] = cycId[p[at]];
            }
        }
    }

    queue <ll> que;
    vector <ll> dis (n, -1);

    for (ll i = 0; i < n; i++) if (cycNo[i] != -1) {
        que.push(i);
        dis[i] = 0;
    }

    while (!que.empty()) {
        ll u = que.front();
        que.pop();
        for (ll x : b[u]) {
            if (dis[x] == -1) {
                dis[x] = dis[u] + 1;
                que.push(x);
            }
        }
    }

    BinaryLiftingTree tree(p);

    while (q--) {
        ll u, v;
        cin >> u >> v;
        u--; v--;
        if (cycId[u] != cycId[v]) {
            cout << -1 << '\n';
        }
        else {
            if (cycNo[u] >= 0 && cycNo[v] >= 0) {
                if (cycNo[u] <= cycNo[v]) {
                    cout << cycNo[v] - cycNo[u] << '\n';
                }
                else {
                    cout << len[cycId[u]] - (cycNo[u] - cycNo[v]) << '\n';
                }
            }
            else if (cycNo[u] == -1 && cycNo[v] == -1) {
                if (dis[u] < dis[v]) {
                    cout << -1 << '\n';
                    continue;
                }
                ll d = dis[u] - dis[v];
                tree.go_up(u, d);
                if (u == v) cout << d << '\n';
                else cout << -1 << '\n';
            }
            else if (cycNo[v] != -1) {
                ll d = dis[u];
                tree.go_up(u, d);
                if (cycNo[v] >= cycNo[u]) d += (cycNo[v] - cycNo[u]);
                else d += (len[cycId[u]] - (cycNo[u] - cycNo[v]));
                cout << d << '\n';
            }
            else cout << -1 << '\n';
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