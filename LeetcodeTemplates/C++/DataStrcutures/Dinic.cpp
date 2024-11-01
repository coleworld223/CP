/*
  Time: O(N^2M) flow O(M / sqrt(N)) Bipartite Matching

*/

struct Dinic {
  using F = i64;
  struct Edge { int to; F flo; F cap; };
  int n;
  vector <Edge> eds;
  vector <vector <int>> adj;
  vector <int> lev;
  vector <vector <int> ::iterator> cur;
  void init(int _n) { n = _n; adj.resize(n); cur.resize(n); }
  void ae(int u, int v, F cap, F rcap = 0) {
    assert(min(cap, rcap) >= 0);
    int sz = eds.size();
    adj[u].push_back(sz); eds.push_back({ v, 0, cap });
    adj[v].push_back(sz + 1); eds.push_back({ u, 0, rcap });
  }
  bool bfs(int s, int t) {
    lev = vector <int>(n, -1);
    for (int i = 0; i < n; ++i) { cur[i] = begin(adj[i]); }
    queue <int> q({ s }); lev[s] = 0;
    while (q.size()) {
      int u = q.front();
      q.pop();
      for (auto e : adj[u]) {
        const Edge& E = eds[e];
        int v = E.to;
        if (lev[v] < 0 and E.flo < E.cap) { q.push(v); lev[v] = lev[u] + 1; }
      }
    }
    return lev[t] >= 0;
  }
  F dfs(int v, int t, F flo) {
    if (v == t) { return flo; }
    for (; cur[v] != end(adj[v]); cur[v]++) {
      Edge& E = eds[*cur[v]];
      if (lev[E.to] != lev[v] + 1 or E.flo == E.cap) { continue; }
      F df = dfs(E.to, t, min(flo, E.cap - E.flo));
      if (df) { E.flo += df; eds[(*cur[v] ^ 1)].flo -= df; return df; }
    }
    return 0;
  }
  F maxFlow(int s, int t) {
    F tot = 0;
    while (bfs(s, t)) {
      while (F df = dfs(s, t, numeric_limits<F>::max())) tot += df;
    }
    return tot;
  }
};