const ll INF = LLONG_MAX;
struct edge{
  int u = -1, v = -1;
  ll w = INF;
  int id = -1;
};

// 0-based, E[i].id = i
bool DMST(int n, vector<edge> &E, int root, vector<edge> &sol){
  vector<int> id(n), vis(n);
  vector<edge> in(n);
  for(edge e : E)
    if(e.u != e.v && e.w < in[e.v].w && e.v != root)
      in[e.v] = e;
  for(int i = 0; i < n; i++)
    if(i != root && in[i].u == -1) return false; // no sol
  int cnt = 0;
  fill(iter(id), -1); fill(iter(vis), -1);
  for(int u = 0; u < n; u++){
    int v = u;
    while(vis[v] != u && id[v] == -1 && in[v].u != -1)
      vis[v] = u, v = in[v].u;
    if(v != root && id[v] == -1){
      for(int x = in[v].u; x != v; x = in[x].u)
        id[x] = cnt;
      id[v] = cnt++;
    }
  }
  if(!cnt) return sol = in, true; // no cycle
  for(int u = 0; u < n; u++)
    if(id[u] == -1) id[u] = cnt++;
  vector<edge> nE;
  for(int i = 0; i < SZ(E); i++){
    edge tmp = E[i];
    tmp.u = id[tmp.u], tmp.v = id[tmp.v];
    if(in[E[i].v].w != INF) tmp.w -= in[E[i].v].w;
    nE.pb(tmp);
  }
  vector<edge> tsol;
  if(!DMST(cnt, nE, id[root], tsol)) return false;
  sol.resize(n);
  for(int i = 0; i < cnt; i++){
    if(i == id[root]) continue;
    int t = tsol[i].id;
    sol[E[t].v] = E[t];
  }
  for(int i = 0; i < n; i++)
    if(sol[i].id == -1) sol[i] = in[i];
  return true;
}
