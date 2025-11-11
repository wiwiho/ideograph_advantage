struct GaussJordan { // SCOPE HASH
  int rk = 0; ll det = 1; // UB if n!=m
  vector<vector<ll>> rref;
  vector<int> cols;
  GaussJordan(const vector<vector<ll>> &_rref): rref(_rref) {
    if (rref.empty()) return;
    int N = SZ(rref), M = SZ(rref[0]);
    auto swap_row = [&](int x, int y) {
      rref[x].swap(rref[y]); if (x != y) det = -det;
    };
    auto mul_row = [&](int x, ll mul) {
      for (auto &v : rref[x]) v = v * mul % MOD;
      det = det * inv(mul) % MOD;
    };
    auto minus_row = [&](int x, int y, ll mul) {
      for (int k = 0; k < M; k++)
        rref[x][k] = (rref[x][k] - rref[y][k] * mul % MOD + MOD) % MOD;
    };
    for (int i = 0; i < M; i++) {
      int cnt = -1;
      for (int j = N - 1; j >= rk; j--)
        if(rref[j][i] != 0) cnt = j;
      if (cnt == -1) continue;
      swap_row(rk, cnt);
      mul_row(rk, inv(rref[rk][i]));
      for (int j = 0; j < N; j++)
        if (j != rk) minus_row(j, rk, rref[j][i]);
      cols.pb(i); rk++;
    }
    if (rk < N) det = 0;
    det = (det % MOD + MOD) % MOD;
  }
};
// sol = particualr + linear combination of homogenous
struct LinearEquation { // SCOPE HASH
  bool ok;
  vector<ll> par; //Ax = b
  vector<vector<ll>> homo; //Ax = 0
  LinearEquation(int M, const GaussJordan& elim): par(M) {
    auto &piv = elim.cols;
    auto &rref = elim.rref;
    if (!piv.empty() && piv.back() == M)
    { ok = 0; return; }
    ok = 1;
    vector<bool> ispiv(M);
    for (int i = 0; i < elim.rk; i++) {
      par[piv[i]] = rref[i][M];
      ispiv[piv[i]] = 1;
    }
    for (int i = 0; i < M; i++) {
      if (ispiv[i]) continue;
      vector<ll> h(M);
      h[i] = 1;
      for (int j = 0; j < elim.rk; j++)
        h[piv[j]] = rref[j][i] ? MOD - rref[j][i] : 0;
      homo.pb(h);
    }
  }
};
