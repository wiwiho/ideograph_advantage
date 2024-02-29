struct StoerWagner { // 0-based, O(V^3)
  int n;
  vector<int> vis, del;
  vector<ll> wei;
  vector<vector<ll>> edge;
  void init(int _n) {
    n = _n;
    del.assign(n, 0);
    edge.assign(n, vector<ll>(n));
  }
  void add_edge(int u, int v, ll w) {
    edge[u][v] += w, edge[v][u] += w;
  }
  void search(int &s, int &t) {
    vis.assign(n, 0); wei.assign(n, 0);
    s = t = -1;
    while (1) {
      ll mx = -1, cur = 0;
      for (int i = 0; i < n; ++i)
        if (!del[i] && !vis[i] && mx < wei[i])
          cur = i, mx = wei[i];
      if (mx == -1) break;
      vis[cur] = 1, s = t, t = cur;
      for (int i = 0; i < n; ++i)
        if (!vis[i] && !del[i]) wei[i] += edge[cur][i];
    }
  }
  ll solve() {
    ll ret = INF;
    for (int i = 0, x=0, y=0; i < n-1; ++i) {
      search(x, y), ret = min(ret, wei[y]), del[y] = 1;
      for (int j = 0; j < n; ++j)
        edge[x][j] = (edge[j][x] += edge[y][j]);
    }
    return ret;
  }
};
