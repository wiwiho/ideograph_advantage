struct Dinic { // 1-base
  struct edge {
    int to, cap, flow, rev;
  };
  vector<edge> g[maxN];
  int n, s, t, dis[maxN], ind[maxN], cnt[maxN];
  const int inf = 1e9;

  void init(int _n) {
    n = _n + 2;
    s = _n + 1, t = _n + 2;
    for (int i = 0; i <= n; ++i) g[i].clear(), cnt[i] = 0;
  }
  void reset() {
    for (int i = 0; i <= n; ++i) 
      for (auto &j : g[i]) j.flow = 0;
  }
  void add_edge(int u, int v, int lcap, int rcap) {
    cnt[u] -= lcap, cnt[v] += lcap;
    g[u].pb(edge{v, rcap, lcap, (int)g[v].size()});
    g[v].pb(edge{u, 0, 0, (int)g[u].size() - 1});
  }
  void add_edge(int u, int v, int cap) {
    g[u].pb(edge{v, cap, 0, (int)g[v].size()});
    g[v].pb(edge{u, 0, 0, (int)g[u].size() - 1});
    //change g[v] to cap for undirected graphs
  }
  bool bfs() {
    fill(dis, dis+n+1, -1);
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
  int dfs(int u, int cap) {
    if (u == t || !cap) return cap;
    for (int &i = ind[u]; i < (int)g[u].size(); ++i) {
      edge &e = g[u][i];
      if (dis[e.to] == dis[u] + 1 && e.flow != e.cap) {
        int df = dfs(e.to, min(e.cap - e.flow, cap));
        if (df) {
          e.flow += df;
          g[e.to][e.rev].flow -= df;
          return df;
        }
      }
    }
    dis[u] = -1;
    return 0;
  }
  int maxflow(int _s, int _t) {
    s = _s, t = _t;
    int flow = 0, df;
    while (bfs()) {
      fill(ind, ind+n+1, 0);
      while ((df = dfs(s, inf))) flow += df;
    }
    return flow;
  }
  bool feasible() {
    int sum = 0;
    for (int i = 1; i <= n - 2; ++i)
      if (cnt[i] > 0)
        add_edge(n - 1, i, cnt[i]), sum += cnt[i];
      else if (cnt[i] < 0) add_edge(i, n, -cnt[i]);
    if (sum != maxflow(n - 1, n)) sum = -1;
    for (int i = 1; i <= n - 2; ++i)
      if (cnt[i] > 0)
        g[n - 1].pop_back(), g[i].pop_back();
      else if (cnt[i] < 0)
        g[i].pop_back(), g[n].pop_back();
    return sum != -1;
  }
  int boundedflow(int _s, int _t) {
    add_edge(_t, _s, inf);
    if (!feasible()) return -1; // infeasible flow
    int x = g[_t].back().flow;
    g[_t].pop_back(), g[_s].pop_back();

    int y = maxflow(_t, _s);
    return x-y;
  }
};

