// for all i in [l, r], floor(n / i) = x
for(int l = 1, r; l <= n; l = r + 1){
  int x = ifloor(n, l);
  r = ifloor(n, x);
}
// for all i in [l, r], ceil(n / i) = x
for(int l, r = n; r >= 1; r = l - 1){
  int x = iceil(n, r);
  l = iceil(n, x);
}
