struct HLD{ // 1-based
  int n, ts = 0; // ord is 1-based
  vector<vector<int>> g;
  vector<int> par, top, down, ord, dpt, sub;
  explicit HLD(int _n): n(_n), g(n + 1), 
  par(n + 1), top(n + 1), down(n + 1), 
  ord(n + 1), dpt(n + 1), sub(n + 1) {}
  void add_edge(int u, int v){ g[u].pb(v); g[v].pb(u); }
  void dfs(int now, int p){
    par[now] = p; sub[now] = 1;
    for(int i : g[now]){
      if(i == p) continue;
      dpt[i] = dpt[now] + 1;
      dfs(i, now);
      sub[now] += sub[i];
      if(sub[i] > sub[down[now]]) down[now] = i;
    }
  }
  void cut(int now, int t){
    top[now] = t; ord[now] = ++ts;
    if(!down[now]) return;
    cut(down[now], t);
    for(int i : g[now]){
      if(i != par[now] && i != down[now])
        cut(i, i);
    }
  }
  void build(){ dfs(1, 1), cut(1, 1); }
  int query(int a, int b){
    int ta = top[a], tb = top[b];
    while(ta != tb){
      if(dpt[ta] > dpt[tb]) swap(ta, tb), swap(a, b);
      // ord[tb], ord[b]
      tb = top[b = par[tb]];
    }
    if(ord[a] > ord[b]) swap(a, b);
    // ord[a], ord[b]
    return a; // lca
  }
};
