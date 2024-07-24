struct SCC{ // 0-based, output reversed topo order
  int n, cnt = 0;
  vector<vector<int>> g;
  vector<int> sccid;
  explicit SCC(int _n): n(_n), g(n), sccid(n, -1) {}
  void add_edge(int u, int v){
    g[u].pb(v);
  }
  void build(){
    vector<int> in(n, -1), low(n), stk;
    vector<bool> instk(n);
    int ts = 0;
    auto dfs1 = [&](auto dfs, int now) -> void{
      stk.pb(now); instk[now] = true;
      in[now] = low[now] = ts++;
      for(int i : g[now]){
        if(in[i] == -1)
          dfs(dfs, i), low[now] = min(low[now], low[i]);
        else if(instk[i] && in[i] < in[now])
          low[now] = min(low[now], in[i]);
      }
      if(low[now] == in[now]){
        for(; stk.back() != now; stk.pop_back())
          sccid[stk.back()] = cnt, instk[stk.back()] = false;
        sccid[now] = cnt++, instk[now] = false, stk.pop_back();
      }
    };
    for(int i = 0; i < n; i++)
      if(in[i] == -1) dfs1(dfs1, i);
  }
};
