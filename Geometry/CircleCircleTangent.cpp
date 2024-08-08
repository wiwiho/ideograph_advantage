vector<Line> CCtang( const Cir& c1 , const Cir& c2 , int sign1 ){
  vector<Line> ret;
  double d_sq = abs2( c1.O - c2.O );
  if (sgn(d_sq) == 0) return ret;
  double d = sqrt(d_sq);
  pdd v = (c2.O - c1.O) / d;
  double c = (c1.R - sign1 * c2.R) / d; // cos t
  if (c * c > 1) return ret;
  double h = sqrt(max( 0.0, 1.0 - c * c)); // sin t
  for (int sign2 = 1; sign2 >= -1; sign2 -= 2) {
    pdd n = pdd(v.X * c - sign2 * h * v.Y,
        v.Y * c + sign2 * h * v.X);
    pdd p1 = c1.O + n * c1.R;
    pdd p2 = c2.O + n * (c2.R * sign1);
    if (sgn(p1.X - p2.X) == 0 and
        sgn(p1.Y - p2.Y) == 0)
      p2 = p1 + perp(c2.O - c1.O);
    ret.pb(Line(p1, p2));
  }
  return ret;
}
