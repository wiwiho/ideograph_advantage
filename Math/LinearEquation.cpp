vector<int> RREF(vector<vector<ll>> &mat) { // SCOPE HASH
  int N = SZ(mat), M = SZ(mat[0]);
  int rk = 0;
  vector<int> cols;
  for (int i = 0; i < M; i++) {
    int cnt = -1;
    for (int j = N - 1; j >= rk; j--)
      if(mat[j][i] != 0) cnt = j;
    if (cnt == -1) continue;
    swap(mat[rk], mat[cnt]);
    ll lead = mat[rk][i];
    for (int j = 0; j < M; j++) mat[rk][j] = mat[rk][j] * inv(lead) % MOD;
    for (int j = 0; j < N; j++) {
      if (j == rk) continue;
      ll tmp = mat[j][i];
      for (int k = 0; k < M; k++) 
        mat[j][k] = (mat[j][k] - mat[rk][k] * tmp % MOD + MOD) % MOD;
    }
    cols.pb(i);
    rk++;
  }
  return cols;
}
// sol = particualr + linear combination of homogenous
struct LinearEquation { // SCOPE HASH
  bool ok;
  vector<ll> par; //particular solution (Ax = b)
  vector<vector<ll>> homo; //homogenous (Ax = 0)
  vector<vector<ll>> rref;
  //first M columns are matrix A
  //last column of eq is vector b
  void solve(const vector<vector<ll>> &eq) {
    int M = SZ(eq[0]) - 1;
    rref = eq;
    auto piv = RREF(rref);
    int rk = piv.size();
    if(piv.size() && piv.back() == M)
      return ok = 0, void();
    ok = 1;
    par.resize(M);
    vector<bool> ispiv(M);
    for (int i = 0;i < rk;i++) {
      par[piv[i]] = rref[i][M];
      ispiv[piv[i]] = 1;
    }
    for (int i = 0; i < M; i++) {
      if (ispiv[i]) continue;
      vector<ll> h(M);
      h[i] = 1;
      for (int j = 0; j < rk; j++)
        h[piv[j]] = rref[j][i] ? MOD - rref[j][i] : 0;
      homo.pb(h);
    }
  }
};
