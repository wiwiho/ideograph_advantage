// all points are distinct
// cnt[i][j] = # of point k s.t. strictly above ij, and i < k < j
// cnt2[i][j] = # of points k s.t. strictly in ij
// preprocess space: O(n^2), time: O(n^3), query time: O(1)
vector cnt(n, vector<int>(n)), cnt2(n, vector<int>(n));
for (int i = 0; i < n; i++)
  for (int j = 0; j < n; j++){
    if (pts[i] >= pts[j]) continue;
    for (int k = 0; k < n; k++) {
      if (pts[i] < pts[k] && pts[k] < pts[j]) {
        int tmp = ori(pts[i], pts[j], pts[k]);
        if (tmp > 0) cnt[i][j]++; // only for i < j
        else if (tmp == 0) cnt2[i][j]++, cnt2[j][i]++;
      }
    }
  }
auto calc_tri = [&](array<int, 3> arr) { // strictly inside
  sort(iter(arr), [&](int x, int y){ return pts[x] < pts[y]; });
  auto [x, y, z] = arr;
  int tmp = ori(pts[x], pts[y], pts[z]);
  if (tmp == 0) return 0;
  else if (tmp < 0)
    return cnt[x][z] - cnt[x][y] - cnt[y][z] - cnt2[x][y] - cnt2[y][z] - 1;
  else return cnt[x][y] + cnt[y][z] - cnt[x][z] - cnt2[x][z];
};
