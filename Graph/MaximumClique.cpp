const int MAXN = 40;
typedef bitset<MAXN> bst;
struct Maximum_Clique {
  bst N[MAXN], empty;
  int p[MAXN], n;
  bst ans;
  // find all maximal clique
  void BronKerbosch2(bst R, bst P, bst X) {
    if (P == empty && X == empty){
      if(ans.count() < R.count()) ans = R;
      return;
    }
    bst tmp = P | X;
    int u;
    if ((R | P | X).count() <= ans.count()) return;
    for (int uu = 0; uu < n; ++uu) {
      u = p[uu];
      if (tmp[u] == 1) break;
    }
    // if (double(clock())/CLOCKS_PER_SEC > .999)
    // return;
    bst now2 = P & ~N[u];
    for (int vv = 0; vv < n; ++vv) {
      int v = p[vv];
      if (now2[v] == 1) {
        R[v] = 1;
        BronKerbosch2(R, P & N[v], X & N[v]);
        R[v] = 0, P[v] = 0, X[v] = 1;
      }
    }
  }
  void init(int _n) {
    n = _n;
    for (int i = 0; i < n; ++i) N[i].reset();
  }
  void add_edge(int u, int v) {
    N[u][v] = N[v][u] = 1;
  }
  void complement(){
    for(int i = 0; i < n; i++)
      for(int j = 0; j < n; j++)
        if(i != j) N[i][j] = !N[i][j];
  }
  void solve() {
    bst R, P, X;
    ans = 0, P.flip();
    for (int i = 0; i < n; ++i) p[i] = i;
    mt19937 rng(123123);
    shuffle(p, p + n, rng), BronKerbosch2(R, P, X);
  }
};
