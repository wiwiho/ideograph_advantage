struct Dinic { // 0-based, O(V^2E), unit flow: O(min(V^{2/3}E, E^{3/2})), bipartite matching: O(sqrt(V)E)
  struct edge { ll to, cap, flow, rev; };
  int n, s, t;
  vector<vector<edge>> g; vector<int> dis, ind;
  explicit Dinic(int _n): n(_n), g(n) {}
  void reset() {
    for (int i = 0; i < n; ++i)
      for (auto &j : g[i]) j.flow = 0;
  }
  void add_edge(int u, int v, ll cap) {
    g[u].pb(edge{v, cap, 0, SZ(g[v])});
    g[v].pb(edge{u, 0, 0, SZ(g[u]) - 1});
    //change g[v] to cap for undirected graphs
  }
  bool bfs() { // SCOPE HASH
    dis.assign(n, -1);
    queue<int> q;
    q.push(s), dis[s] = 0;
    while (!q.empty()) {
      int cur = q.front(); q.pop();
      for (auto &e : g[cur]) {
        if (dis[e.to] == -1 && e.flow != e.cap) {
          q.push(e.to);
          dis[e.to] = dis[cur] + 1;
        }
      }
    }
    return dis[t] != -1;
  }
  ll dfs(int u, ll cap) { // SCOPE HASH
    if (u == t || !cap) return cap;
    for (int &i = ind[u]; i < SZ(g[u]); ++i) {
      edge &e = g[u][i];
      if (dis[e.to] == dis[u] + 1 && e.flow != e.cap) {
        ll df = dfs(e.to, min(e.cap - e.flow, cap));
        if (df) {
          e.flow += df;
          g[e.to][e.rev].flow -= df;
          return df;
    } } }
    dis[u] = -1;
    return 0;
  }
  ll maxflow(int _s, int _t) { // SCOPE HASH
    s = _s; t = _t;
    ll flow = 0, df;
    while (bfs()) {
      ind.assign(n, 0);
      while ((df = dfs(s, INF))) flow += df;
    }
    return flow;
  }
};
