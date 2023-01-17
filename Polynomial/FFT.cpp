using val_t = complex<double>;
template<int MAXN>
struct FFT {
	const double PI = acos(-1);
	val_t w[MAXN];
	FFT() {
		for (int i = 0; i < MAXN; ++i) {
			double arg = 2 * PI * i / MAXN;
			w[i] = val_t(cos(arg), sin(arg));
		}
	}
	void bitrev(vector<val_t> &a, int n) //same as NTT	
	void trans(vector<val_t> &a, int n, bool inv = false) {
		bitrev(a, n);
		for (int L = 2; L <= n; L <<= 1) {
			int dx = MAXN / L, dl = L >> 1;
			for (int i = 0; i < n; i += L) {
				for (int j = i, x = 0; j < i + dl; ++j, x += dx) {
					val_t tmp = a[j + dl] * (inv ? conj(w[x]) : w[x]);
					a[j + dl] = a[j] - tmp;
					a[j] += tmp;
				}
			}
		}
		if (inv) {
			for (int i = 0; i < n; ++i) a[i] /= n;
		}
	}
	//multiplying two polynomials A * B:
	//fft.trans(A, siz, 0), fft.trans(B, siz, 0):
	//A[i] *= B[i], fft.trans(A, siz, 1);
};
