ld goldenRatioSearch(ld a, ld b, auto &&f) {
  ld r = (sqrt(5)-1)/2, eps = 1e-7;
  ld x1 = b - r*(b-a), x2 = a + r*(b-a);
  ld f1 = f(x1), f2 = f(x2);
  while (b-a > eps)
    if (f1 < f2) { //change to > to find maximum
      b = x2; x2 = x1; f2 = f1;
      x1 = b - r*(b-a); f1 = f(x1);
    } else {
      a = x1; x1 = x2; f1 = f2;
      x2 = a + r*(b-a); f2 = f(x2);
    }
  return a;
}
