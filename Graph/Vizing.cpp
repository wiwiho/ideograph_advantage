// find D+1 edge coloring of a graph with max deg D, O(nm)
struct Vizing { // returns maxdeg+1 edge coloring in adjacent matrix G
  int n; // 1-based for vertices and colors, simple graph
  vector<vector<int>> C, G;
  vector<int> X, vst;
  Vizing(int _n): n(_n),
  C(n + 1, vector<int>(n + 2)), G(n + 1, vector<int>(n + 1)), 
  X(n + 1, 1), vst(n + 1) {}
  void solve(vector<pii> &E) {
    auto update = [&](int u)
    { for (X[u] = 1; C[u][X[u]]; ++X[u]); };
    auto color = [&](int u, int v, int c) {
      int p = G[u][v];
      G[u][v] = G[v][u] = c;
      C[u][c] = v, C[v][c] = u;
      C[u][p] = C[v][p] = 0;
      if (p) X[u] = X[v] = p;
      else update(u), update(v);
      return p;
    };
    auto flip = [&](int u, int c1, int c2) {
      int p = C[u][c1];
      swap(C[u][c1], C[u][c2]);
      if (p) G[u][p] = G[p][u] = c2;
      if (!C[u][c1]) X[u] = c1;
      if (!C[u][c2]) X[u] = c2;
      return p;
    };
    for (int t = 0; t < SZ(E); ++t) {
      int u = E[t].ff, v0 = E[t].ss, v = v0, c0 = X[u], c = c0, d;
      vector<pii> L;
      fill(iter(vst), 0);
      while (!G[u][v0]) {
        L.emplace_back(v, d = X[v]);
        if (!C[v][c]) for (int a = SZ(L) - 1; a >= 0; --a) c = color(u, L[a].ff, c);
        else if (!C[u][d]) for (int a = SZ(L) - 1; a >= 0; --a) color(u, L[a].ff, L[a].ss);
        else if (vst[d]) break;
        else vst[d] = 1, v = C[u][d];
      }
      if (!G[u][v0]) {
        for (; v; v = flip(v, c, d), swap(c, d));
        if (int a; C[u][c0]) {
          for (a = SZ(L) - 2; a >= 0 && L[a].ss != c; --a);
          for (; a >= 0; --a) color(u, L[a].ff, L[a].ss);
        }
        else --t;
      }
    }
  }
};
