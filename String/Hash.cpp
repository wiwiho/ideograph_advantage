int n;
string s;
vector<ll> h, rh;
vector<ll> kp;
const ll K = 26, MOD = 1000000007;

void topos(ll &a){
	a = (a % MOD + MOD) % MOD;
}

int ord(char c){
	return c - 'a';
}

pll geth(int l, int r){
	if(l > r) return mp(0, 0);
	ll ans = h[r] - h[l - 1] * kp[r - l + 1];
	topos(ans);
	return mp(ans, r - l + 1);
}

pll getrh(int l, int r){
	if(l > r) return mp(0, 0);
	l = n - l + 1;
	r = n - r + 1;
	swap(l, r);
	ll ans = rh[r] - rh[l - 1] * kp[r - l + 1];
	topos(ans);
	return mp(ans, r - l + 1);
}

pll concat(pll a, pll b){
	ll ans = a.F * kp[b.S] + b.F;
	ans %= MOD;
	return mp(ans, a.S + b.S);
}

void build(){
	n = s.size();
	s = " " + s;

	h.resize(n + 1);
	rh.resize(n + 1);
	kp.resize(n + 1);
	kp[0] = 1;
	for(int i = 1; i <= n; i++){
		kp[i] = kp[i - 1] * K % MOD;
	}
	for(int i = 1; i <= n; i++){
		h[i] = h[i - 1] * K % MOD + ord(s[i]);
		h[i] %= MOD;
		rh[i] = rh[i - 1] * K % MOD + ord(s[n - i + 1]);
		rh[i] %= MOD;
	}
}
