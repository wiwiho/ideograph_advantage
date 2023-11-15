struct Dinic { // 1-base
  struct edge {
    int to, cap, flow, rev;
  };
  vector<edge> g[maxn];
  int n, s, t, dis[maxn], ind[maxn], cnt[maxn];
  const int inf = 1e9;

  void init(int _n) {
    n = _n + 2;
    s = _n + 1, t = _n + 2;
    for (int i = 0; i <= n; ++i) g[i].clear(), cnt[i] = 0;
  }
  //reset, bfs, dfs same as Dinic
  void add_edge(int u, int v, int lcap, int rcap) {
    cnt[u] -= lcap, cnt[v] += lcap;
    g[u].pb(edge{v, rcap, lcap, (int)g[v].size()});
    g[v].pb(edge{u, 0, 0, (int)g[u].size() - 1});
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
        add_edge(n - 1, i, 0, cnt[i]), sum += cnt[i];
      else if (cnt[i] < 0) add_edge(i, n, 0,-cnt[i]);
    if (sum != maxflow(n - 1, n)) sum = -1;
    for (int i = 1; i <= n - 2; ++i)
      if (cnt[i] > 0)
        g[n - 1].pop_back(), g[i].pop_back();
      else if (cnt[i] < 0)
        g[i].pop_back(), g[n].pop_back();
    return sum != -1;
  }
  int boundedflow(int _s, int _t) {
    add_edge(_t, _s, 0, inf);
    if (!feasible()) return -1; // infeasible flow
    int x = g[_t].back().flow;
    g[_t].pop_back(), g[_s].pop_back();
    /* Minimum feasible flow */
    int y = maxflow(_t, _s);
    return x-y;

    /* Maximum feasible flow
    int y = maxflow(_s, _t);
    return x+y;
    */
  }
};

