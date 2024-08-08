struct Event {
  pll d; int u, v;
  bool operator<(const Event &b) const {
    int ret = cmp(d, b.d, false);
    return ret == -1 ? false : ret; } // no tie-break
};
void rotatingSweepLine(const vector<pll> &p) {
  const int n = SZ(p);
  vector<Event> e; e.reserve(n * (n - 1));
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++) // pos[i] < pos[j] when the event occurs
      if (i != j) e.pb(p[j] - p[i], i, j);
  sort(iter(e));
  vector<int> ord(n), pos(n);
  iota(iter(ord), 0);
  sort(iter(ord), [&](int i, int j) { // initial order
      return p[i].Y != p[j].Y ? p[i].Y < p[j].Y : p[i].X < p[j].X; });
  for (int i = 0; i < n; i++) pos[ord[i]] = i;
  // initialize
  for (int i = 0, j = 0; i < SZ(e); i = j) {
    // do something
    vector<pii> tmp;
    for (; j < SZ(e) && !(e[i] < e[j]); j++)
      tmp.pb(pii(e[j].u, e[j].v));
    sort(iter(tmp), [&](pii x, pii y){ 
        return pii(pos[x.ff], pos[x.ss]) < pii(pos[y.ff], pos[y.ss]); });
    for (auto [x, y] : tmp) // pos[x] + 1 == pos[y]
      tie(ord[pos[x]], ord[pos[y]], pos[x], pos[y]) = 
        make_tuple(ord[pos[y]], ord[pos[x]], pos[y], pos[x]);
  }
}
