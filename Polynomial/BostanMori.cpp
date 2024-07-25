const ll mod = 998244353;
NTT<262144, mod, 3> ntt;
// Finds the k-th coefficient of P / Q in O(d log d log k)
// size of NTT has to > 2 * d
ll BostanMori(vector<ll> P, vector<ll> Q, long long k) {
  int d = max((int)P.size(), (int)Q.size() - 1);
  vector M = {P, Q};
  M[0].resize(d, 0);
  M[1].resize(d + 1, 0);
  int sz = (2 * d + 1 == 1 ? 2 : (1 << (__lg(2 * d) + 1)));
  vector<ll> Qn(sz);
  vector N(2, vector<ll>(sz));
  while(k) {
    fill(iter(Qn), 0);
    for(int i = 0; i < d + 1; i++){
      Qn[i] = M[1][i] * ((i & 1) ? -1 : 1);
      if(Qn[i] < 0) Qn[i] += mod;
    }
    ntt(Qn, sz, false);

    ll t[2] = {k & 1, 0};
    for(int i = 0; i < 2; i++){
      fill(iter(N[i]), 0);
      copy(iter(M[i]), N[i].begin()); 
      ntt(N[i], sz, false);
      for(int j = 0; j < sz; j++)
        N[i][j] = N[i][j] * Qn[j] % mod;
      ntt(N[i], sz, true);
      for(int j = t[i]; j < 2 * siz(M[i]); j += 2){
        M[i][j >> 1] = N[i][j];
      }
    }
    k >>= 1;
  }
  return M[0][0] * ntt.minv(M[1][0]) % mod;
}
ll LinearRecursion(vector<ll> a, vector<ll> c, ll k) { // a_n = \sum_{j=1}^{d} c_j a_(n-j)
    int d = siz(a);
    int sz = (2 * d + 1 == 1 ? 2 : (1 << (__lg(2 * d) + 1)));

    c[0] = mod - 1;
    for(ll &i : c) i = i ? mod - i : 0;
    
    auto A = a; A.resize(sz);
    auto C = c; C.resize(sz);
    ntt(A, sz, false), ntt(C, sz, false);
    for(int i = 0; i < sz; i++) A[i] = A[i] * C[i] % mod;
    ntt(A, sz, true);
    A.resize(d);

    return BostanMori(A, c, k);
}
