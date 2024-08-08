ll anneal() {
  mt19937 rnd_engine(seed);
  uniform_real_distribution<ll> rnd(0, 1);
  const ll dT = 0.001;
  // Argument p
  ll S_cur = calc(p), S_best = S_cur;
  for (ll T = 2000; T > eps; T -= dT) {
    // Modify p to p_prime
    const ll S_prime = calc(p_prime);
    const ll delta_c = S_prime - S_cur;
    ll prob = min((ll)1, exp(-delta_c / T));
    if (rnd(rnd_engine) <= prob)
      S_cur = S_prime, p = p_prime;
    if (S_prime < S_best) // find min
      S_best = S_prime, p_best = p_prime;
  }
  return S_best;
}
