struct MCMF { // 0-base
  struct Edge {
    ll from, to, cap, flow, cost, rev; 
  };
  int n, s, t;
  vector<vector<Edge>> g;
  vector<Edge*> past;
  vector<ll> dis, up, pot;
  explicit MCMF(int _n): n(_n), g(n), past(n), dis(n), up(n), pot(n) {}
  void add_edge(ll a, ll b, ll cap, ll cost) {
    g[a].pb(Edge{a, b, cap, 0, cost, SZ(g[b])});
    g[b].pb(Edge{b, a, 0, 0, -cost, SZ(g[a]) - 1});
  }
  bool BellmanFord() {
    vector<bool> inq(n);
    fill(iter(dis), INF);
    queue<int> q;
    auto relax = [&](int u, ll d, ll cap, Edge *e) {
      if (cap > 0 && dis[u] > d) {
        dis[u] = d, up[u] = cap, past[u] = e;
        if (!inq[u]) inq[u] = 1, q.push(u);
      }
    };
    relax(s, 0, INF, 0);
    while (!q.empty()) {
      int u = q.front();
      q.pop(), inq[u] = 0;
      for (auto &e : g[u]) {
        ll d2 = dis[u] + e.cost + pot[u] - pot[e.to];
        relax(e.to, d2, min(up[u], e.cap - e.flow), &e);
      }
    }
    return dis[t] != INF;
  }
  pair<ll, ll> solve(int _s, int _t, bool neg = true) {
    s = _s, t = _t; ll flow = 0, cost = 0;
    if (neg) BellmanFord(), pot = dis;
    for (; BellmanFord(); pot = dis) {
      for (int i = 0; i < n; ++i)
        if (dis[i] != INF) dis[i] += pot[i] - pot[s];
      flow += up[t], cost += up[t] * dis[t];
      for (int i = t; past[i]; i = past[i]->from) {
        auto &e = *past[i];
        e.flow += up[t], g[e.to][e.rev].flow -= up[t];
      }
    }
    return {flow, cost};
  }
};
