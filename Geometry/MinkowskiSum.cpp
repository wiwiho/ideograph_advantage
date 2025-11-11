TEMP void reorder_poly(vector<ptt>& pts){
  rotate(pts.begin(), min_element(iter(pts), 
    [&](ptt x, ptt y){ 
    return x.Y != y.Y ? x.Y < y.Y : x.X < y.X; }), 
    pts.end());
}
TEMP vector<ptt> minkowski(vector<ptt> P, vector<ptt> Q){
  reorder_poly(P); reorder_poly(Q);
  int psz = P.size(), qsz = Q.size();
  P.pb(P[0]); P.pb(P[1]); Q.pb(Q[0]); Q.pb(Q[1]);
  vector<ptt> ans; int i = 0, j = 0;
  while (i < psz || j < qsz) {
    ans.pb(P[i] + Q[j]);
    int t = sgn(cross(P[i + 1]-P[i], Q[j + 1]-Q[j]));
    if(t >= 0) i++; if(t <= 0) j++;
  }
  return ans;
}
