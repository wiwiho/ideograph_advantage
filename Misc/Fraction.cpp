struct Frac{ 
	ll p, q;  // p / q
	Frac(ll _p, ll _q): p(_p), q(_q) { if(q < 0) p = -p, q = -q; }
};
Frac operator-(Frac a) { return Frac(-a.p, a.q); }
Frac operator+(Frac a, Frac b){
	ll q = a.q * b.q;
	ll p = a.p * b.q + b.p * a.q;
	return Frac(p, q);
}
Frac inv(Frac a){ return Frac(a.q, a.p); }
Frac operator-(Frac a, Frac b) { return a + (-b); }
Frac operator*(Frac a, Frac b) { return Frac({a.p * b.p, a.q * b.q}); }
Frac operator/(Frac a, Frac b) { return a * inv(b); }
ostream& operator<<(ostream& o, Frac a) { return o << a.p << '/' << a.q; }
