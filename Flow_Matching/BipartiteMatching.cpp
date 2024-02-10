//min vertex cover: take all unmatched vertices in L and find alternating tree,
//ans is not reached in L + reached in R
// O(VE)
int n; // 1-based, max matching
int mx[maxn], my[maxn];
bool adj[maxn][maxn], vis[maxn];
bool dfs(int u) {
  if (vis[u]) return 0;
  vis[u] = 1;
  for (int v = 1;v <= n;v++) {
    if (!adj[u][v]) continue;
    if (!my[v] || (my[v] && dfs(my[v]))) {
      mx[u] = v, my[v] = u;
      return 1;
    }
  }
  return 0;
}
// O(E sqrt(V)), O(E log V) for random sparse graphs
struct BipartiteMatching { // 0-based
  int nl, nr;
  vector<int> mx, my, dis, cur;
  vector<vector<int>> g;
  bool dfs(int u) {
    for (int &i = cur[u]; i < SZ(g[u]); ++i) {
      int e = g[u][i];
      if (!~my[e] || (dis[my[e]] == dis[u] + 1 && dfs(my[e])))
        return mx[my[e] = u] = e, 1;
    }
    dis[u] = -1;
    return 0;
  }
  bool bfs() {
    int ret = 0;
    queue<int> q;
    dis.assign(nl, -1);
    for (int i = 0; i < nl; ++i)
      if (!~mx[i]) q.push(i), dis[i] = 0;
    while (!q.empty()) {
      int u = q.front();
      q.pop();
      for (int e : g[u])
        if (!~my[e]) ret = 1;
        else if (!~dis[my[e]]) {
          q.push(my[e]);
          dis[my[e]] = dis[u] + 1;
        }
    }
    return ret;
  }
  int matching() {
    int ret = 0;
    mx.assign(nl, -1); my.assign(nr, -1);
    while (bfs()) {
      cur.assign(nl, 0);
      for (int i = 0; i < nl; ++i)
        if (!~mx[i] && dfs(i)) ++ret;
    }
    return ret;
  }
  void add_edge(int s, int t) { g[s].pb(t); }
  void init(int _nl, int _nr) {
    nl = _nl, nr = _nr;
    g.assign(nl, vector<int>());
  }
};
