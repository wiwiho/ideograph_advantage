struct SAT { // 0-based
  int n;
  vector<bool> istrue;
  SCC scc;
  SAT(int _n): n(_n), istrue(n + n), scc(n + n) {}
  int neg(int a) {
    return a >= n ? a - n : a + n;
  }
  void add_clause(int a, int b) {
    scc.add_edge(neg(a), b), scc.add_edge(neg(b), a);
  }
  bool solve() {
    scc.build();
    for (int i = 0; i < n; ++i) {
      if (scc.sccid[i] == scc.sccid[i + n]) return false;
      istrue[i] = scc.sccid[i] < scc.sccid[i + n];
      istrue[i + n] = !istrue[i];
    }
    return true;
  }
};
