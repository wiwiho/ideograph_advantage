struct MCMF { // 0-based, O(SPFA * |f|)
  struct edge {
    ll from, to, cap, flow, cost, rev;
  };
  int n;
  int s, t; ll mx;
  //mx: maximum amount of flow
  vector<vector<edge>> g;
  vector<ll> dis, up;
  bool BellmanFord(ll &flow, ll &cost) {
    vector<edge*> past(n);
    vector<int> inq(n);
    dis.assign(n, INF); up.assign(n, 0);
    queue<int> q;
    q.push(s), inq[s] = 1;
    up[s] = mx - flow, past[s] = 0, dis[s] = 0;
    while (!q.empty()) {
      int u = q.front();
      q.pop(), inq[u] = 0;
      if (!up[u]) continue;
      for (auto &e : g[u])
        if (e.flow != e.cap &&
            dis[e.to] > dis[u] + e.cost) {
          dis[e.to] = dis[u] + e.cost, past[e.to] = &e;
          up[e.to] = min(up[u], e.cap - e.flow);
          if (!inq[e.to]) inq[e.to] = 1, q.push(e.to);
        }
    }
    if (dis[t] == INF) return 0;
    flow += up[t], cost += up[t] * dis[t];
    for (ll i = t; past[i]; i = past[i]->from) {
      auto &e = *past[i];
      e.flow += up[t], g[e.to][e.rev].flow -= up[t];
    }
    return 1;
  }
  pll MinCostMaxFlow(int _s, int _t) {
    s = _s, t = _t;
    ll flow = 0, cost = 0;
    while (BellmanFord(flow, cost));
    return pll(flow, cost);
  }
  void init(int _n, ll _mx) {
    n = _n, mx = _mx;
    g.assign(n, vector<edge>());
  }
  void add_edge(int a, int b, ll cap, ll cost) {
    g[a].pb(edge{a, b, cap, 0, cost, SZ(g[b])});
    g[b].pb(edge{b, a, 0, 0, -cost, SZ(g[a]) - 1});
  }
};
