sort(iter(pts), [&](pll x, pll y) {
  return x.Y != y.Y ? x.Y < y.Y : x.X < y.X;
});
auto getvec = [&](pii x) { return pts[x.ss] - pts[x.ff]; };
vector<pii> trans;
for (int j = 0; j < n; j++)
  for (int k = 0; k < n; k++)
    if (j != k) trans.pb(pii(j, k));
sort(iter(trans), [&](pii x, pii y) -> bool{
  int tmp = cmp(getvec(x), getvec(y), false);
  if (tmp != -1) return tmp;
  pll v = getvec(x);
  return dot(v, pts[x.ff]) > dot(v, pts[y.ff]);
});
// DP for convex hull vertices (no points on edges)
auto solve = [&](int bottom) { // O(n^3)
  // vector<ll> dp(n);
  for (int j = bottom + 1; j < n; j++) {
    // check whether bottom -> j is legal
    // init trans -> j
  }
  for (auto [i, j] : trans) {
    if (i <= bottom || j <= bottom ||
        ori(pts[bottom], pts[i], pts[j]) <= 0) continue;
    // check whether i -> j is legal
    // normal trans i -> j
  }
  for (int j = bottom + 1; j < n; j++) {
    // check whether j -> bottom is legal
    // end trans j ->
  }
};
for(int i = 0; i < n; i++) solve(i);
