pll solve_crt(ll x1, ll m1, ll x2, ll m2){
  ll g = gcd(m1, m2);
  if ((x2 - x1) % g) return {0, 0}; // no sol
  m1 /= g; m2 /= g;
  ll _, p, q;
  extgcd(m1, m2, _, p, q); // p <= C
  ll lcm = m1 * m2 * g;
  ll res = ((__int128)p * (x2 - x1) % lcm * m1 % lcm + x1) % lcm;
  // be careful with overflow, C^3
  return {(res + lcm) % lcm, lcm}; // (x, m)
}
