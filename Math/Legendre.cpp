// the Jacobi symbol is a generalization of the Legendre symbol,
// such that the bottom doesn't need to be prime.
// (n|p) -> same as legendre
// (n|ab) = (n|a)(n|b)
// work with long long
int Jacobi(int a, int m) {
	int s = 1;
	for (; m > 1; ) {
		a %= m;
		if (a == 0) return 0;
		const int r = __builtin_ctz(a);
		if ((r & 1) && ((m + 2) & 4)) s = -s;
		a >>= r;
		if (a & m & 2) s = -s;
		swap(a, m);
	}
	return s;
}

// 0: a == 0
// -1: a isn't a quad res of p
// else: return X with X^2 % p == a
// doesn't work with long long
int QuadraticResidue(int a, int p) {
	if (p == 2) return a & 1;
	if(int jc = Jacobi(a, p); jc <= 0) return jc;
	int b, d;
	for (; ; ) {
		b = rand() % p;
		d = (1LL * b * b + p - a) % p;
		if (Jacobi(d, p) == -1) break;
	}
	int f0 = b, f1 = 1, g0 = 1, g1 = 0, tmp;
	for (int e = (1LL + p) >> 1; e; e >>= 1) {
		if (e & 1) {
			tmp = (1LL * g0 * f0 + 1LL * d * (1LL * g1 * f1 % p)) % p;
			g1 = (1LL * g0 * f1 + 1LL * g1 * f0) % p;
			g0 = tmp;
		}
		tmp = (1LL * f0 * f0 + 1LL * d * (1LL * f1 * f1 % p)) % p;
		f1 = (2LL * f0 * f1) % p;
		f0 = tmp;
	}
	return g0;
}
