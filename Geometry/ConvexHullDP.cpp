sort(iter(pts), [&](pll x, pll y) {
    return x.Y != y.Y ? x.Y < y.Y : x.X < y.X;
    });
auto getvec = [&](pii x) { return pts[x.ss] - pts[x.ff]; };
// DP for convex hull vertices (no points on edges)
auto solve = [&](int bottom) { // O(n^3)
  pll O = pts[bottom];
  vector<pii> trans;
  for (int j = bottom + 1; j < n; j++)
    for (int k = bottom + 1; k < n; k++) {
      if (ori(O, pts[j], pts[k]) <= 0) continue;
      // check whether j->k is legal
      trans.pb(pii(j, k));
    }
  sort(iter(trans), [&](pii x, pii y) -> bool{
      int tmp = cmp(getvec(x), getvec(y), false);
      if (tmp != -1) return tmp;
      pll v = getvec(x);
      return dot(v, pts[x.ff]) > dot(v, pts[y.ff]);
      });
  // vector<ll> dp(n);
  for (int j = bottom + 1; j < n; j++) {
    // check whether bottom -> j is legal
    // init trans -> j
  }
  for (auto [i, j] : trans) {
    // normal trans i -> j
  }
  for (int j = bottom + 1; j < n; j++) {
    // check whether j -> bottom is legal
    // end trans j ->
  }
};
for(int i = 0; i < n; i++) solve(i);
