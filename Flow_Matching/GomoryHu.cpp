void GomoryHu(Dinic &flow) { // 0-based
  int n = flow.n;
  vector<int> par(n);
  for (int i = 1; i < n; ++i) {
    flow.reset();
    add_edge(i, par[i], flow.maxflow(i, par[i]));
    for (int j = i + 1; j < n; ++j)
      if (par[j] == par[i] && ~flow.dis[j])
        par[j] = i;
  }
}
