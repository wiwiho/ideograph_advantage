struct MinCostCirculation { // 0-based, O(VE * ElogC)
  struct edge {
    ll from, to, cap, fcap, flow, cost, rev; 
  };
  int n;
  vector<edge*> past;
  vector<vector<edge>> g;
  vector<ll> dis;
  void BellmanFord(int s) {
    vector<int> inq(n);
    dis.assign(n, INF);
    queue<int> q;
    auto relax = [&](int u, ll d, edge *e) {
      if (dis[u] > d) {
        dis[u] = d, past[u] = e;
        if (!inq[u]) inq[u] = 1, q.push(u);
      }
    };
    relax(s, 0, 0);
    while (!q.empty()) {
      int u = q.front();
      q.pop(), inq[u] = 0;
      for (auto &e : g[u])
        if (e.cap > e.flow)
          relax(e.to, dis[u] + e.cost, &e);
    }
  }
  void try_edge(edge &cur) {
    if (cur.cap > cur.flow) return ++cur.cap, void();
    BellmanFord(cur.to);
    if (dis[cur.from] + cur.cost < 0) {
      ++cur.flow, --g[cur.to][cur.rev].flow;
      for (int i = cur.from; past[i]; i = past[i]->from) {
        auto &e = *past[i];
        ++e.flow, --g[e.to][e.rev].flow;
      }
    }
    ++cur.cap;
  }
  void solve(int mxlg) { // mxlg >= log(max cap)
    for (int b = mxlg; b >= 0; --b) {
      for (int i = 0; i < n; ++i)
        for (auto &e : g[i])
          e.cap *= 2, e.flow *= 2;
      for (int i = 0; i < n; ++i)
        for (auto &e : g[i])
          if (e.fcap >> b & 1)
            try_edge(e);
    }
  }
  void init(int _n) {
    n = _n;
    past.assign(n, nullptr);
    g.assign(n, vector<edge>());
  }
  void add_edge(ll a, ll b, ll cap, ll cost) {
    g[a].pb(edge{a, b, 0, cap, 0, cost, SZ(g[b]) + (a == b)});
    g[b].pb(edge{b, a, 0, 0, 0, -cost, SZ(g[a]) - 1});
  }
}; 
