struct BCC{
  vector<int> v, e, cut;
};
struct BlockCutTree{ // 0-based, allow multi edges but not allow loops
  int n, m, cnt = 0;
  // n:|V|, m:|E|, cnt:|bcc|
  vector<BCC> bcc;
  vector<vector<pii>> g; // original graph
  vector<pii> edges; // 0-based
  vector<vector<int>> vbcc;
  // vbcc[i] = BCCs containing vertex i, vbcc[i].size()>1 iff i is an articulation
  vector<int> ebcc;
  // edge i is a bridge iff bcc[ebcc[i]].e.size() == 1
  // block cut tree:
  // adj[bcc i]: bcc[i].cut
  // adj[cut i]: vbcc[i]

  BlockCutTree(int _n, vector<pii> _edges):
      n(_n), m(SZ(_edges)), g(_n), edges(_edges), vbcc(_n), ebcc(SZ(_edges)){
    for(int i = 0; i < m; i++){
      auto [u, v] = edges[i];
      g[u].pb(pii(v, i)); g[v].pb(pii(u, i));
    }
  }

  void build(){
    vector<int> in(n, -1), low(n, -1);
    vector<vector<int>> up(n);
    vector<int> stk;
    int ts = 0;
    auto _dfs = [&](auto dfs, int now, int par, int pe) -> void{
      if(pe != -1) up[now].pb(pe);
      in[now] = low[now] = ts++;
      stk.pb(now);
      for(auto [v, e] : g[now]){
        if(e == pe) continue;
        if(in[v] != -1){
          if(in[v] < in[now]) up[now].pb(e);
          low[now] = min(low[now], in[v]);
          continue;
        }
        dfs(dfs, v, now, e);
        low[now] = min(low[now], low[v]);
      }
      if((now != par && low[now] >= in[par]) || (now == par && SZ(g[now]) == 0)){
        bcc.pb();
        while(true){
          int v = stk.back();
          stk.pop_back();
          vbcc[v].pb(cnt);
          bcc[cnt].v.pb(v);
          for(int e : up[v]){
            ebcc[e] = cnt;
            bcc[cnt].e.pb(e);
          }
          if(v == now) break;
        }
        if(now != par){
          vbcc[par].pb(cnt);
          bcc[cnt].v.pb(par);
        }
        cnt++;
      }
    };
    for(int i = 0; i < n; i++){
      if(in[i] == -1) _dfs(_dfs, i, i, -1);
    }
    for(int i = 0; i < cnt; i++)
      for(int j : bcc[i].v)
        if(SZ(vbcc[j]) > 1) bcc[i].cut.pb(j);
  }
};
