using ld = ll;
using pdd = pair<ld, ld>;
#define X first
#define Y second
// ld eps = 1e-7;

pdd operator+(pdd a, pdd b) { /*...*/ }
pdd operator-(pdd a, pdd b) { /*...*/ }
pdd operator*(ld i, pdd v) { /*...*/ }
pdd operator*(pdd v, ld i) { /*...*/ }
pdd operator/(pdd v, ld i) { /*...*/ }
ld dot(pdd a, pdd b) { /*...*/ }
ld cross(pdd a, pdd b) { /*...*/ }
ld abs2(pdd v) { /*...*/ }
ld abs(pdd v) { /*...*/ }
int sgn(ld v) { /*...*/ }
int ori(pdd a, pdd b, pdd c) { /*...*/ }
bool collinearity(pdd a, pdd b, pdd c) { /*...*/ }
bool btw(pdd p, pdd a, pdd b) { /*...*/ }

bool seg_intersect(pdd p1, pdd p2, pdd p3, pdd p4){
  if(btw(p1, p3, p4) || btw(p2, p3, p4) || btw(p3, p1, p2) || btw(p4, p1, p2))
    return true;
  return ori(p1, p2, p3) * ori(p1, p2, p4) < 0 &&
    ori(p3, p4, p1) * ori(p3, p4, p2) < 0;
}
pdd intersect(pdd p1, pdd p2, pdd p3, pdd p4){
  ld a123 = cross(p2 - p1, p3 - p1);
  ld a124 = cross(p2 - p1, p4 - p1);
  return (p4 * a123 - p3 * a124) / (a123 - a124);
}
pdd perp(pdd p1)
{ return pdd(-p1.Y, p1.X); }
pdd projection(pdd p1, pdd p2, pdd p3)
{ return p1 + (p2 - p1) * dot(p3 - p1, p2 - p1) / abs2(p2 - p1); }
pdd reflection(pdd p1, pdd p2, pdd p3)
{ return p3 + perp(p2 - p1) * cross(p3 - p1, p2 - p1) / abs2(p2 - p1) * 2; }
pdd linearTransformation(pdd p0, pdd p1, pdd q0, pdd q1, pdd r) {
  pdd dp = p1 - p0, dq = q1 - q0, num(cross(dp, dq), dot(dp, dq));
  return q0 + pdd(cross(r - p0, num), dot(r - p0, num)) / abs2(dp);
} // from line p0--p1 to q0--q1, apply to r 
