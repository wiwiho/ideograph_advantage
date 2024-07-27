// Copy from 8BQube
#define fi(s, n) for (int i = (int)(s); i < (int)(n); ++i)
#define neg(x) (x ? P - x : 0)
#define V (*this)
template <int MAXN, ll P, ll RT>  // MAXN = 2^k
struct Poly : vector<ll> {		  // coefficients in [0, P)
	using vector<ll>::vector;
	static inline NTT<MAXN, P, RT> ntt;
	int n() const { return (int)size(); }  // n() >= 1
	Poly(const Poly &p, int m) : vector<ll>(m) { copy_n(p.data(), min(p.n(), m), data()); }
	Poly &irev() { return reverse(data(), data() + n()), V; }
	Poly &isz(int m) { return resize(m), V; }
	static ll minv(ll x) { return ntt.minv(x); }
	Poly &iadd(const Poly &rhs) {  // n() == rhs.n()
		fi(0, n()) if ((V[i] += rhs[i]) >= P) V[i] -= P;
		return V;
	}
	Poly &imul(ll k) {
		fi(0, n()) V[i] = V[i] * k % P;
		return V;
	}
	Poly Mul(const Poly &rhs) const {
		int m = 1;
		while (m < n() + rhs.n() - 1) m <<= 1;
		assert(m <= MAXN);
		Poly X(V, m), Y(rhs, m);
		ntt(X, m), ntt(Y, m);
		fi(0, m) X[i] = X[i] * Y[i] % P;
		ntt(X, m, true);
		return X.isz(n() + rhs.n() - 1);
	}
	Poly Inv() const {	// V[0] != 0, 2*sz<=MAXN
		if (n() == 1) return {minv(V[0])};
		int m = 1;
		while (m < n() * 2) m <<= 1;
		assert(m <= MAXN);
		Poly Xi = Poly(V, (n() + 1) / 2).Inv().isz(m);
		Poly Y(V, m);
		ntt(Xi, m), ntt(Y, m);
		fi(0, m) {
			Xi[i] *= (2 - Xi[i] * Y[i]) % P;
			if ((Xi[i] %= P) < 0) Xi[i] += P;
		}
		ntt(Xi, m, true);
		return Xi.isz(n());
	}
	Poly &shift_inplace(const ll &c) {	// 2 * sz <= MAXN
		int n = V.n();
		vector<ll> fc(n), ifc(n);
		fc[0] = ifc[0] = 1;
		for (int i = 1; i < n; i++) {
			fc[i] = fc[i - 1] * i % P;
			ifc[i] = minv(fc[i]);
		}
		for (int i = 0; i < n; i++) V[i] = V[i] * fc[i] % P;
		Poly g(n);
		ll cp = 1;
		for (int i = 0; i < n; i++) g[i] = cp * ifc[i] % P, cp = cp * c % P;
		V = V.irev().Mul(g).isz(n).irev();
		for (int i = 0; i < n; i++) V[i] = V[i] * ifc[i] % P;
		return V;
	}
	Poly shift(const ll &c) const { return Poly(V).shift_inplace(c); }
	Poly _Sqrt() const {  // Jacobi(V[0], P) = 1
		if (n() == 1) return {QuadraticResidue(V[0], P)};
		Poly X = Poly(V, (n() + 1) / 2)._Sqrt().isz(n());
		return X.iadd(Mul(X.Inv()).isz(n())).imul(P / 2 + 1);
	}
	Poly Sqrt() const {	 // 2 * sz <= MAXN
		Poly a;
		bool has = 0;
		for (int i = 0; i < n(); i++) {
			if (V[i]) has = 1;
			if (has) a.push_back(V[i]);
		}
		if (!has) return V;
		if ((n() + a.n()) % 2 || Jacobi(a[0], P) != 1) {
			return Poly();
		}
		a = a.isz((n() + a.n()) / 2)._Sqrt();
		int sz = a.n();
		a.isz(n());
		rotate(a.begin(), a.begin() + sz, a.end());
		return a;
	}
	pair<Poly, Poly> DivMod(const Poly &rhs) const {  // (rhs.)back() != 0
		if (n() < rhs.n()) return {{0}, V};
		const int m = n() - rhs.n() + 1;
		Poly X(rhs);
		X.irev().isz(m);
		Poly Y(V);
		Y.irev().isz(m);
		Poly Q = Y.Mul(X.Inv()).isz(m).irev();
		X = rhs.Mul(Q), Y = V;
		fi(0, n()) if ((Y[i] -= X[i]) < 0) Y[i] += P;
		return {Q, Y.isz(max(1, rhs.n() - 1))};
	}
	Poly Dx() const {
		Poly ret(n() - 1);
		fi(0, ret.n()) ret[i] = (i + 1) * V[i + 1] % P;
		return ret.isz(max(1, ret.n()));
	}
	Poly Sx() const {
		Poly ret(n() + 1);
		fi(0, n()) ret[i + 1] = minv(i + 1) * V[i] % P;
		return ret;
	}
	Poly _tmul(int nn, const Poly &rhs) const {
		Poly Y = Mul(rhs).isz(n() + nn - 1);
		return Poly(Y.data() + n() - 1, Y.data() + Y.n());
	}
	vector<ll> _eval(const vector<ll> &x, const vector<Poly> &up) const {
		const int m = (int)x.size();
		if (!m) return {};
		vector<Poly> down(m * 2);
		// down[1] = DivMod(up[1]).second;
		// fi(2, m * 2) down[i] = down[i / 2].DivMod(up[i]).second;
		down[1] = Poly(up[1]).irev().isz(n()).Inv().irev()._tmul(m, V);
		fi(2, m * 2) down[i] = up[i ^ 1]._tmul(up[i].n() - 1, down[i / 2]);
		vector<ll> y(m);
		fi(0, m) y[i] = down[m + i][0];
		return y;
	}
	static vector<Poly> _tree1(const vector<ll> &x) {
		const int m = (int)x.size();
		vector<Poly> up(m * 2);
		fi(0, m) up[m + i] = {neg(x[i]), 1};
		for (int i = m - 1; i > 0; --i) up[i] = up[i * 2].Mul(up[i * 2 + 1]);
		return up;
	}
	vector<ll> Eval(const vector<ll> &x) const {  // 1e5, 1s
		auto up = _tree1(x);
		return _eval(x, up);
	}
	static Poly Interpolate(const vector<ll> &x, const vector<ll> &y) {	 // 1e5, 1.4s
		const int m = (int)x.size();
		vector<Poly> up = _tree1(x), down(m * 2);
		vector<ll> z = up[1].Dx()._eval(x, up);
		fi(0, m) z[i] = y[i] * minv(z[i]) % P;
		fi(0, m) down[m + i] = {z[i]};
		for (int i = m - 1; i > 0; --i)
			down[i] = down[i * 2].Mul(up[i * 2 + 1]).iadd(down[i * 2 + 1].Mul(up[i * 2]));
		return down[1];
	}
	Poly Ln() const {  // V[0] == 1, 2*sz<=MAXN
		return Dx().Mul(Inv()).Sx().isz(n());
	}
	Poly Exp() const {	// V[0] == 0,2*sz<=MAXN
		if (n() == 1) return {1};
		Poly X = Poly(V, (n() + 1) / 2).Exp().isz(n());
		Poly Y = X.Ln();
		Y[0] = P - 1;
		fi(0, n()) if ((Y[i] = V[i] - Y[i]) < 0) Y[i] += P;
		return X.Mul(Y).isz(n());
	}
	// M := P(P - 1). If k >= M, k := k % M + M.
	Poly Pow(ll k) const {	// 2*sz<=MAXN
		int nz = 0;
		while (nz < n() && !V[nz]) ++nz;
		if (nz * min(k, (ll)n()) >= n()) return Poly(n());
		if (!k) return Poly(Poly{1}, n());
		Poly X(data() + nz, data() + nz + n() - nz * k);
		const ll c = ntt.mpow(X[0], k % (P - 1));
		return X.Ln().imul(k % P).Exp().imul(c).irev().isz(n()).irev();
	}
	// sum_j w_j [x^j] f(x^i) for i \in [0, m]
	Poly power_projection(Poly wt, int m) {	 // 4*sz <= MAXN!
		assert(n() == wt.n());
		if (!n()) {
			return Poly(m + 1, 0);
		}
		if (V[0] != 0) {
			ll c = V[0];
			V[0] = 0;
			Poly A = V.power_projection(wt, m);
			fi(0, m + 1) A[i] = A[i] * fac[i] % P;	// factorial
			Poly B(m + 1);
			ll pow = 1;
			fi(0, m + 1) B[i] = pow * ifac[i] % P, pow = pow * c % P;  // inv. of fac
			A = A.Mul(B).isz(m + 1);
			fi(0, m + 1) A[i] = A[i] * fac[i] % P;
			return A;
		}

		int n = 1;
		while (n < V.n()) n *= 2;
		isz(n), wt.isz(n).irev();
		int k = 1;
		Poly p(wt, 2 * n), q(V, 2 * n);
		q.imul(P - 1);

		while (n > 1) {
			Poly r(2 * n * k);
			fi(0, 2 * n * k) r[i] = (i % 2 == 0 ? q[i] : neg(q[i]));
			Poly pq = p.Mul(r).isz(4 * n * k);
            Poly qq = q.Mul(r).isz(4 * n * k);
			fi(0, 2 * n * k) {
				pq[2 * n * k + i] += p[i];
				qq[2 * n * k + i] += q[i] + r[i];
				pq[2 * n * k + i] %= P;
				qq[2 * n * k + i] %= P; 
			}
			fill(p.begin(), p.end(), 0);
			fill(q.begin(), q.end(), 0);
			for(int j = 0; j < 2 * k; j++) fi(0, n / 2) {
				p[n * j + i] = pq[(2 * n) * j + (2 * i + 1)];
				q[n * j + i] = qq[(2 * n) * j + (2 * i + 0)];
			}
			n /= 2, k *= 2;
		}
		Poly ans(k);
		fi(0, k) ans[i] = p[2 * i];
		return ans.irev().isz(m + 1);
	}
	Poly FPSinv() {
		const int n = V.n() - 1;
		if (n == -1) return {};
		assert(V[0] == 0);
		if (n == 0) return V;
		assert(V[1] != 0);
		ll c = V[1], ic = minv(c);
		imul(ic);
		Poly wt(n + 1);
		wt[n] = 1;

		Poly A = V.power_projection(wt, n);
		Poly g(n);
		fi(1, n + 1) g[n - i] = n * A[i] % P * minv(i) % P;
		g = g.Pow(neg(minv(n)));
		g.insert(g.begin(), 0);

		ll pow = 1;
		fi(0, g.n()) g[i] = g[i] * pow % P, pow = pow * ic % P;
		return g;
	}
	Poly TMul(const Poly &rhs) const { // this[i] - rhs[j] = k;
		return Poly(*this).irev().Mul(rhs).isz(n()).irev();
	}
	Poly FPScomp(Poly g) { // solves V(g(x))
		auto rec = [&](auto &rec, int n, int k, Poly Q) -> Poly {
			if (n == 1) {
				Poly p(2 * k);
				irev();
				fi(0, k) p[2 * i] = V[i];
				return p;
			}
			Poly R(2 * n * k);
			fi(0, 2 * n * k) R[i] = (i % 2 == 0 ? Q[i] : neg(Q[i]));
			Poly QQ = Q.Mul(R).isz(4 * n * k);
			fi(0, 2 * n * k) { 
				QQ[2 * n * k + i] += Q[i] + R[i];
				QQ[2 * n * k + i] %= P;
			}
			Poly nxt_Q(2 * n * k);
			for(int j = 0; j < 2 * k; j++) fi(0, n / 2) {
				nxt_Q[n * j + i] = QQ[(2 * n) * j + (2 * i + 0)];
			}
			Poly nxt_p = rec(rec, n / 2, k * 2, nxt_Q);
			Poly pq(4 * n * k);
			for(int j = 0; j < 2 * k; j++) fi(0, n / 2) {
				pq[(2 * n) * j + (2 * i + 1)] += nxt_p[n * j + i];
				pq[(2 * n) * j + (2 * i + 1)] %= P;
			}
			Poly p(2 * n * k);
			fi(0, 2 * n * k) p[i] = (p[i] + pq[2 * n * k + i]) % P;
			pq.pop_back();
			Poly x = pq.TMul(R);
			fi(0, 2 * n * k) p[i] = (p[i] + x[i]) % P;
			return p;
		};
		int sz = 1;
		while(sz < n() || sz < g.n()) sz <<= 1;
		return isz(sz), rec(rec, sz, 1, g.imul(P-1).isz(2 * sz)).isz(sz).irev();
	}
};
#undef fi
#undef V
#undef neg
using Poly_t = Poly<1 << 19, 998244353, 3>;
