using ld = double;
using pdd = pair<ld, ld>;
#define X first
#define Y second
const ld eps = 1e-9;

#define TEMP template<class T>
#define ptt pair<T, T>
TEMP ptt operator+(ptt a, ptt b)
{ return {a.X + b.X, a.Y + b.Y}; }
TEMP ptt operator-(ptt a, ptt b)
{ return {a.X - b.X, a.Y - b.Y}; }
TEMP ptt operator*(T i, ptt v)
{ return {i * v.X, i * v.Y}; }
TEMP ptt operator*(ptt v, T i)
{ return {i * v.X, i * v.Y}; }
TEMP pdd operator/(ptt v, ld i)
{ return {v.X / i, v.Y / i}; }
TEMP T dot(ptt a, ptt b)
{ return a.X * b.X + a.Y * b.Y; }
TEMP T cross(ptt a, ptt b)
{ return a.X * b.Y - a.Y * b.X; }
TEMP T abs2(ptt v)
{ return v.X * v.X + v.Y * v.Y; };
TEMP ld abs(ptt v)
{ return sqrt(abs2(v)); };
int sgn(ll v)
{ return v > 0 ? 1 : (v < 0 ? -1 : 0); }
int sgn(ld v){ return v > eps ? 1 : ( v < -eps ? -1 : 0); }
TEMP int ori(ptt a, ptt b, ptt c)
{ return sgn(cross(b - a, c - a)); }
TEMP bool collinearity(ptt a, ptt b, ptt c)
{ return ori(a, b, c) == 0; }
TEMP bool btw(ptt p, ptt a, ptt b)
{ return collinearity(p, a, b) && sgn(dot(a - p, b - p)) <= 0; }

TEMP bool seg_intersect(ptt p1, ptt p2, ptt p3, ptt p4){
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
TEMP ptt perp(ptt p1)
{ return {-p1.Y, p1.X}; }
pdd projection(pdd p1, pdd p2, pdd p3)
{ return p1 + (p2 - p1) * dot(p3 - p1, p2 - p1) / abs2(p2 - p1); }
pdd reflection(pdd p1, pdd p2, pdd p3)
{ return p3 + perp(p2 - p1) * cross(p3 - p1, p2 - p1) / abs2(p2 - p1) * 2.0; }
pdd linearTransformation(pdd p0, pdd p1, pdd q0, pdd q1, pdd r) {
  pdd dp = p1 - p0, dq = q1 - q0, num(cross(dp, dq), dot(dp, dq));
  return q0 + pdd(cross(r - p0, num), dot(r - p0, num)) / abs2(dp);
} // from line p0--p1 to q0--q1, apply to r 
