struct KM { // 0-based, maximum matching, O(V^3)
  int n, ql, qr;
  vector<vector<ll>> w;
  vector<ll> hl, hr, slk;
  vector<int> fl, fr, pre, qu, vl, vr;
  void init(int _n) {
    n = _n;
    // -INF for perfect matching
    w.assign(n, vector<ll>(n, 0));
    pre.assign(n, 0);
    qu.assign(n, 0);
  }
  void add_edge(int a, int b, ll wei) {
    w[a][b] = wei;
  }
  bool check(int x) {
    if (vl[x] = 1, ~fl[x])
      return (vr[qu[qr++] = fl[x]] = 1);
    while (~x) swap(x, fr[fl[x] = pre[x]]);
    return 0;
  }
  void bfs(int s) {
    slk.assign(n, INF); vl.assign(n, 0); vr.assign(n, 0);
    ql = qr = 0, qu[qr++] = s, vr[s] = 1;
    for (ll d;;) {
      while (ql < qr)
        for (int x = 0, y = qu[ql++]; x < n; ++x)
          if (!vl[x] && slk[x] >= (d = hl[x] + hr[y] - w[x][y])) {
            if (pre[x] = y, d) slk[x] = d;
            else if (!check(x)) return;
          }
      d = INF;
      for (int x = 0; x < n; ++x)
        if (!vl[x] && d > slk[x]) d = slk[x];
      for (int x = 0; x < n; ++x) {
        if (vl[x]) hl[x] += d;
        else slk[x] -= d;
        if (vr[x]) hr[x] -= d;
      }
      for (int x = 0; x < n; ++x)
        if (!vl[x] && !slk[x] && !check(x)) return;
    }
  }
  ll solve() {
    fl.assign(n, -1); fr.assign(n, -1); hl.assign(n, 0); hr.assign(n, 0);
    for (int i = 0; i < n; ++i)
      hl[i] = *max_element(iter(w[i]));
    for (int i = 0; i < n; ++i) bfs(i);
    ll res = 0;
    for (int i = 0; i < n; ++i) res += w[i][fl[i]];
    return res;
  }
};
