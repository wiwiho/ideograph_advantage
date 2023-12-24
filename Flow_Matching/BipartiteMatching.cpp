//min vertex cover: take all unmatched vertices in L and find alternating tree,
//ans is not reached in L + reached in R
// O(VE)
int n; //1-base, max matching
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
struct Bipartite_Matching { // 0-base
  int l, r;
  int mp[maxn], mq[maxn];
  int dis[maxn], cur[maxn];
  vector<int> G[maxn];
  bool dfs(int u) {
    for (int &i = cur[u]; i < SZ(G[u]); ++i) {
      int e = G[u][i];
      if (!~mq[e] || (dis[mq[e]] == dis[u] + 1 && dfs(mq[e])))
        return mp[mq[e] = u] = e, 1;
    }
    dis[u] = -1;
    return 0;
  }
  bool bfs() {
    int rt = 0;
    queue<int> q;
    fill_n(dis, l, -1);
    for (int i = 0; i < l; ++i)
      if (!~mp[i])
        q.push(i), dis[i] = 0;
    while (!q.empty()) {
      int u = q.front();
      q.pop();
      for (int e : G[u])
        if (!~mq[e])
          rt = 1;
        else if (!~dis[mq[e]]) {
          q.push(mq[e]);
          dis[mq[e]] = dis[u] + 1;
        }
    }
    return rt;
  }
  int matching() {
    int rt = 0;
    fill_n(mp, l, -1);
    fill_n(mq, r, -1);
    while (bfs()) {
      fill_n(cur, l, 0);
      for (int i = 0; i < l; ++i)
        if (!~mp[i] && dfs(i))
          ++rt;
    }
    return rt;
  }
  void add_edge(int s, int t) {
    G[s].pb(t);
  }
  void init(int _l, int _r) {
    l = _l, r = _r;
    for (int i = 0; i < l; ++i)
      G[i].clear();
  }
} match;
