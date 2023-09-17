vector<int> RREF(vector<vector<ll>> &mat){
  int N = mat.size(), M = mat[0].size();
  int rk = 0;
  vector<int> cols;
  for (int i = 0;i < M;i++) {
    int cnt = -1;
    for (int j = N-1;j >= rk;j--)
      if(mat[j][i] != 0) cnt = j;
    if(cnt == -1) continue;
    swap(mat[rk], mat[cnt]);
    ll lead = mat[rk][i];
    for (int j = 0;j < M;j++) mat[rk][j] /= lead;
    for (int j = 0;j < N;j++) {
      if(j == rk) continue;
      ll tmp = mat[j][i];
      for (int k = 0;k < M;k++) 
        mat[j][k] -= mat[rk][k] * tmp;
    }
    cols.pb(i);
    rk++;
  }
  return cols;
}
struct LinearEquation{
  bool ok;
  vector<ll> par; //particular solution (Ax = b)
  vector<vector<ll>> homo; //homogenous (Ax = 0)
  vector<vector<ll>> rref;
  //first M columns are matrix A
  //last column of eq is vector b
  void solve(const vector<vector<ll>> &eq){
    int M = (int)eq[0].size() - 1;
    rref = eq;
    auto piv = RREF(rref);
    int rk = piv.size();
    if(piv.size() && piv.back() == M){
      ok = 0;return;
    }
    ok = 1;
    par.resize(M);
    vector<bool> ispiv(M);
    for (int i = 0;i < rk;i++) {
      par[piv[i]] = rref[i][M];
      ispiv[piv[i]] = 1;
    }
    for (int i = 0;i < M;i++) {
      if (ispiv[i]) continue;
      vector<ll> h(M);
      h[i] = 1;
      for (int j = 0;j < rk;j++) h[piv[j]] = -rref[j][i];
      homo.pb(h);
    }
  }
}
