using NumType = ll;
// using NumType = ld;
using Pt = pair<NumType, NumType>;
using Line = pair<Pt, Pt>;
#define X first
#define Y second
// ld eps = 1e-7;

Pt operator+(Pt a, Pt b)
    { return {a.X + b.X, a.Y + b.Y}; }
Pt operator-(Pt a, Pt b)
    { return {a.X - b.X, a.Y - b.Y}; }
Pt operator*(NumType i, Pt v)
    { return {i * v.X, i * v.Y}; }
Pt operator/(Pt v, NumType i)
    { return {v.X / i, v.Y / i}; }
NumType dot(Pt a, Pt b)
    { return a.X * b.X + a.Y * b.Y; }
NumType cross(Pt a, Pt b)
    { return a.X * b.Y - a.Y * b.X; }
NumType abs2(Pt v)
    { return v.X * v.X + v.Y * v.Y; };
int sgn(NumType v)
    { return v > 0 ? 1 : (v < 0 ? -1 : 0); }
// int sgn(NumType v){ return v > eps ? 1 : ( v < -eps ? -1 : 0); }
int ori(Pt a, Pt b, Pt c)
    { return sgn(cross(b - a, c - a)); }
bool collinearity(Pt a, Pt b, Pt c)
    { return ori(a, b, c) == 0; }
bool btw(Pt p, Pt a, Pt b)
    { return collinearity(p, a, b) && sgn(dot(a - p, b - p)) <= 0; }

bool intersect(Line a, Line b){
    Pt p1, p2, p3, p4;
    tie(p1, p2) = a; tie(p3, p4) = b;
    if(btw(p1, p3, p4) || btw(p2, p3, p4) || btw(p3, p1, p2) || btw(p4, p1, p2))
        return true;
    return ori(p1, p2, p3) * ori(p1, p2, p4) < 0 &&
            ori(p3, p4, p1) * ori(p3, p4, p2) < 0;
}
