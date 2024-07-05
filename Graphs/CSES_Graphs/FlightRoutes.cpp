#include<bits/stdc++.h>
using namespace std;
 
using ll = long long;
const ll mod = 1e9 + 7;
using a2 = array <ll, 2>;
 
void solve() {
    ll n, m, k;
    cin >> n >> m >> k;
 
    vector <vector <a2>> a (n);
 
    for (ll i = 0; i < m; i++) {
        ll u, v, w;
        cin >> u >> v >> w;
        u--; v--;
        a[u].push_back({v, w});
    }   
 
    priority_queue <a2, vector <a2>, greater <a2>> pq;
    vector <priority_queue <ll>> dis (n);
 
    dis[0].push(0);
    pq.push({0, 0});
 
    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        if (d > dis[u].top()) continue;
        for (auto [v, w] : a[u]) {
            if (dis[v].size() < k) {
                dis[v].push(d + w);
                pq.push({d + w, v});
            }
            else if (dis[v].top() > d + w) {
                dis[v].pop();
                dis[v].push(d + w);
                pq.push({d + w, v});
            }
        }
    }
 
    vector <ll> res;
 
    while (!dis[n - 1].empty())
        res.push_back(dis[n - 1].top()), dis[n - 1].pop();
    reverse(res.begin(), res.end());
 
    for (ll &x : res) 
        cout << x << ' ';
    cout << "\n";
}