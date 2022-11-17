const int len = 2000005, sigma = 26;
struct AC_Automatan { //1-base
	int nx[len][sigma], fl[len], cnt[len], pri[len], top;
	//pri: bfs order of trie
	int newnode() {
		fill(nx[top], nx[top] + sigma, -1);
		return top++;
	}
	void init() { top = 1, newnode(); }
	int input(
			string &s) { // return the end_node of string
		int X = 1;    #include <bits/stdc++.h>
    #pragma GCC optimize ("Ofast")
    using namespace std;
     
    void __print(int x) {cerr << x;}
    void __print(long x) {cerr << x;}
    void __print(long long x) {cerr << x;}
    void __print(unsigned x) {cerr << x;}
    void __print(unsigned long x) {cerr << x;}
    void __print(unsigned long long x) {cerr << x;}
    void __print(float x) {cerr << x;}
    void __print(double x) {cerr << x;}
    void __print(long double x) {cerr << x;}
    void __print(char x) {cerr << '\'' << x << '\'';}
    void __print(const char *x) {cerr << '\"' << x << '\"';}
    void __print(const string &x) {cerr << '\"' << x << '\"';}
    void __print(bool x) {cerr << (x ? "true" : "false");}
    template<typename T, typename V>
    void __print(const pair<T, V> &x) {cerr << '{'; __print(x.first); cerr << ", "; __print(x.second); cerr << '}';}
    template<typename T>
    void __print(const T &x) {int f = 0; cerr << '{'; for (auto &i: x) cerr << (f++ ? ", " : ""), __print(i); cerr << "}";}
     
    void _print(){}
    void _print(string s){s.clear();}
    template <typename T, typename... V>
    void _print(string s, T t, V... v) {
    	stringstream ss;
    	ss << s;
    	string curr;
    	getline(ss, curr, ',');
    	string left;
    	getline(ss, left);
    	while(curr[0] == ' ') curr.erase(curr.begin());
    	cerr << "    " << curr << " = ";
    	__print(t);
    	cerr << "\n";
    	if (sizeof...(v)) _print(left, v...);
    }
    #ifdef zisk
    #define debug(...) (cerr << "LINE " << __LINE__ << ":\n", _print(#__VA_ARGS__, __VA_ARGS__))
    #else
    #define debug(...) (void)0
    #endif
     
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    #define vi vector<int>
    #define pb emplace_back
    #define mp make_pair
    #define mt make_tuple
    #define pii pair<int,int>
    #define F(n) Fi(i,n)
    #define Fi(i,n) Fl(i,0,n)
    #define Fl(i,l,n) for(int i=l;i<n;i++)
    #define RF(n) RFi(i,n)
    #define RFi(i,n) RFl(i,0,n)
    #define RFl(i,l,n) for(int i=n-1;i>=l;i--)
    #define all(v) begin(v),end(v)
    #define siz(v) ((long long)(v.size()))
    #define get_pos(v,x) (lower_bound(all(v),x)-begin(v))
    #define sort_uni(v) sort(begin(v),end(v)),v.erase(unique(begin(v),end(v)),end(v))
    #define mem(v,x) memset(v,x,sizeof v)
    #define ff first
    #define ss second
    #define RAN(a,b) uniform_int_distribution<int> (a, b)(rng)
    #define cmax(a,b) (a = max(a,b))
    #define cmin(a,b) (a = min(a,b))
     
    int ___;
    typedef long double ld;
     
    ld fastsqrt(ld x){
        int T = 60;
        ld l = 0, r = x;
        while(T--){
            ld mid = (l + r) / 2;
            if(mid * mid < x) l = mid;
            else r = mid;
        }
        return (l + r) / 2;
    }
    // #define sqrtl fastsqrt
     
    // Wiwi's geometry template
    using Pt = pair<ld, ld>;
    using tppp = tuple<Pt, Pt, Pt>;
    using tnnn = tuple<ld, ld, ld>;
    using Line = pair<Pt, Pt>;
    const ld eps = 1e-13;
    #define X first
    #define Y second
    Pt operator+(Pt a, Pt b)
    { return {a.X + b.X, a.Y + b.Y}; }
    Pt operator-(Pt a, Pt b)
    { return {a.X - b.X, a.Y - b.Y}; }
    Pt operator*(ld i, Pt v)
    { return {i * v.X, i * v.Y}; }
    Pt operator*(Pt v, ld i)
    { return {i * v.X, i * v.Y}; }
    Pt operator/(Pt v, ld i)
    { return {v.X / i, v.Y / i}; }
    ld dot(Pt a, Pt b)
    { return a.X * b.X + a.Y * b.Y; }
    ld cross(Pt a, Pt b)
    { return a.X * b.Y - a.Y * b.X; }
    ld abs2(Pt v)
    { return v.X * v.X + v.Y * v.Y; };
    int sgn(ld v){ return v > eps ? 1 : ( v < -eps ? -1 : 0); }
    int ori(Pt a, Pt b, Pt c)
    { return sgn(cross(b - a, c - a)); }
    bool collinearity(Pt a, Pt b, Pt c)
    { return ori(a, b, c) == 0; }
    bool btw(Pt p, Pt a, Pt b)
    { return collinearity(p, a, b) && sgn(dot(a - p, b - p)) <= 0; }
    ld pi = acosl(-1);
     
    Pt Rect(const ld& r, const ld& theta){
    	return make_pair(r * cosl(theta), r * sinl(theta));
    }
     
    ld topos(const ld &x){
    	return x - 2 * pi * floorl(x / (2 * pi)) ;
    }
     
    ld PolarAngle(const Pt &a){
    	return topos(atan2l(a.Y, a.X));
    }
     
    struct Circle{
    	Pt O;
    	ld r;
    };
     
    struct Sector{
    	Circle C;
    	ld alpha, beta;
    	Pt O, A, B;
    	vector<pair<ld, ld> > range;
    };
    ld getAngleFromLengths(const ld &a, const ld &b, const ld &c){
    	return acosl( ( b * b + c * c - a * a ) / (2 * b * c) );
    }
    ld getAngleFromPoints(Pt A, Pt B, Pt C){
    	return getAngleFromLengths(sqrtl(abs2(B - C)), sqrtl(abs2(C - A)), sqrtl(abs2(A - B)));
    }
    ld shoelace(const vector<Pt> &v){
    	int n = v.size();
    	if(v.empty()) return 0;
    	ld ans = 0;
    	for(int i = 0 ; i < n - 1; i++){
    		ans += v[i].X * v[i+1].Y - v[i+1].X * v[i].Y;
    	}
    	ans += v[n-1].X * v[0].Y - v[0].X * v[n-1].Y;
    	return ans / 2;
    }
    ld projection_dist(const Pt &A, const Line &L){
    	return shoelace({A, L.X, L.Y}) * 2 / sqrtl(abs2(L.X - L.Y));
    }
    Pt projection(const Pt &A, const Line &L){
        return L.X + dot(A - L.X, L.Y - L.X) / dot(L.Y - L.X, L.Y - L.X) * (L.Y - L.X);
    }
    ld normalize(Pt A, Line L){
    	A = projection(A, L);
    	const ld EPS = 1e-9;
    	ld u = sqrtl(abs2(A - L.X));
    	ld v = sqrtl(abs2(A - L.Y));
    	ld w = sqrtl(abs2(L.X - L.Y));
    	
    	if( abs (u + v - w) < EPS){
    		return u / w;
    	}
    	if( abs (v + w - u) < EPS){
    		return u / w;
    	}
    	if( abs (w + u - v) < EPS){
    		return -(u / w);
    	}
     
    	debug(u + v - w, v + w - u, w + u - v);
    	// assert(0);
    }
    Pt lineIntersectLine(const Line &A, const Line &B, int& pt = ___){
    	if( sgn(cross(A.Y - A.X, B.Y - B.X)) == 0){
    		pt = 0;
    		return mp(0, 0);
    	}
    	pt = 1;
    	ld xr = normalize(B.X, A);
    	ld yr = normalize(B.Y, A);
    	ld xw = projection_dist(B.X, A) / sqrtl(abs2(B.X - B.Y));
    	ld yw = projection_dist(B.Y, A) / sqrtl(abs2(B.X - B.Y));
    	ld res = ( yw * xr - yr * xw ) / (yw - xw);
    	return (1 - res) * A.X + res * A.Y;
    }
     
    Line circleIntersectCircle(Circle &a, Circle &b, int& pt = ___) {
    	Pt o1 = a.O, o2 = b.O;
    	double r1 = a.r, r2 = b.r, d2 = abs2(o1 - o2), d = sqrt(d2);
    	if(d < max(r1, r2) - min(r1, r2) || d > r1 + r2){
    		pt = 0;
    		return mp(mp(0, 0), mp(0, 0));
    	}
    	Pt u = (o1 + o2) * 0.5 + (o1 - o2) * ((r2 * r2 - r1 * r1) / (2 * d2));
    	double A = sqrt((r1 + r2 + d) * (r1 - r2 + d) * (r1 + r2 - d) * (-r1 + r2 + d));
    	Pt v = (Pt){o1.Y - o2.Y, -o1.X + o2.X} * (A / (2 * d2)) ;
     
    	Pt p1 = u + v, p2 = u - v;
    	pt = 2;
    	return mp(p1, p2);
    }
    Line circleIntersectLine(const Circle &C, const Line &L, int& pt = ___) {
      Pt p = L.X + (L.Y - L.X) * dot(C.O - L.X, L.Y - L.X) / abs2(L.Y - L.X);
      double s = cross(L.Y - L.X, C.O - L.X), h2 = C.r * C.r - s * s / abs2(L.Y - L.X);
      if (h2 < 0) return pt = 0, mp(mp(0, 0), mp(0, 0));
      if (h2 == 0) return pt = 1, mp(p, p);
      Pt h = (L.Y - L.X) / sqrtl(abs2(L.Y - L.X)) * sqrt(h2);
      return pt = 2, mp(p - h, p + h);
    }
    const int maxN = 1010;
    Sector arr[maxN];
    bool contained[maxN];
    ld checkContained(ld alpha, ld beta, ld theta){
    	if(alpha - eps < theta && theta - eps < beta) return (theta - alpha) / (beta - alpha);
    	if(alpha - eps  < beta) return -1;
    	alpha = topos(alpha + 2*pi/3);
    	beta = topos(beta + 2*pi/3);
    	theta = topos(theta + 2*pi/3);
    	if(alpha - eps < theta && theta - eps < beta) return (theta - alpha) / (beta - alpha);
    	if(alpha - eps  < beta) return -1;
    	alpha = topos(alpha + 2*pi/3);
    	beta = topos(beta + 2*pi/3);
    	theta = topos(theta + 2*pi/3);
    	if(alpha - eps < theta && theta - eps < beta) return (theta - alpha) / (beta - alpha);
    	if(alpha - eps  < beta) return -1;
    	// assert(0);
    }
     
    int checkContained(Pt A, Pt B, Pt C){
    	// is C in A ~ B
    	if( sgn(cross(A, C)) >= 0 && sgn(cross(C, B)) >= 0) return 1;
    	return -1;
    }
     
    ld angleInterp(ld alpha, ld beta, ld p){
    	if(alpha > beta) beta += 2 * pi;
    	return topos(alpha + p * (beta - alpha));
    }
    bool pointInSector(Sector& S, Pt& P){
    	if(abs2(P - S.O) > abs2(S.A - S.O)) return 0;
    	if(checkContained(S.A - S.O, S.B - S.O, P - S.O) == -1) return 0;
    	return 1;
    }
    ld getParam(Sector& S, Pt& P){
    	ld s = checkContained(S.alpha, S.beta, PolarAngle(P - S.O));
    	// assert(s != -1);
    	if( abs(s) < eps ){
    		return sqrtl(abs2(P - S.O)) / sqrtl(abs2(S.A - S.O));
    	}
    	if( abs(s - 1) < eps){
    		return 2 + sqrtl(abs2(P - S.B)) / sqrtl(abs2(S.O - S.B));
    	}
    	return 1 + s;
    }
    Pt getPoint(Sector& S, ld p){
    	// debug(S.O, S.A, S.B, p);
    	if(abs(p    ) < eps) return S.O;
    	if(abs(p - 1) < eps) return S.A;	
    	if(abs(p - 2) < eps) return S.B;	
    	if(abs(p - 3) < eps) return S.O;	
     
    	if(p < 1) return S.O + p * (S.A - S.O);
    	else if (p < 2) return S.O + Rect(S.C.r, angleInterp(S.alpha, S.beta, p - 1));
    	return S.B + (p - 2) * (S.O - S.B);
    }
    vector<Pt> getIntersectPts(int _, int __){
    	Sector &x = arr[_];
    	Sector &y = arr[__];
     
    	Pt tmp;
    	Line tmp2;
    	int sig;
     
    	vector<Pt> intersection_points;
     
    #define lil lineIntersectLine
    #define cil circleIntersectLine
    #define cic circleIntersectCircle
     
    	// x's OA intersects ...
    	// y's OA
    	tmp = lil(mp(x.O, x.A), mp(y.O, y.A), sig);
    	if(sig){
    		ld p1 = normalize(tmp, mp(x.O, x.A));
    		ld p2 = normalize(tmp, mp(y.O, y.A));
    		if(-eps < p1 && p1 < 1 + eps
    				&& -eps < p2 && p2 < 1 + eps){
    			intersection_points.pb(tmp);
    		}
    	}
    	// y's AB
    	tmp2 = cil(y.C, mp(x.O, x.A), sig);
    	if(sig){
    		{
    			tmp = tmp2.X;
    			ld p1 = normalize(tmp, mp(x.O, x.A));	
    			ld p2 = checkContained(y.A - y.O, y.B - y.O, tmp - y.O);
    			if(-eps < p1 && p1 < 1 + eps && p2 != -1){
    				intersection_points.pb(tmp);
    			}
    		}
    		{
    			tmp = tmp2.Y;
    			ld p1 = normalize(tmp, mp(x.O, x.A));	
    			ld p2 = checkContained(y.A - y.O, y.B - y.O, tmp - y.O);
    			if(-eps < p1 && p1 < 1 + eps && p2 != -1){
    				intersection_points.pb(tmp);
    			}
    		}
    	}
     
    	// y's BO
    	tmp = lil(mp(x.O, x.A), mp(y.B, y.O), sig);
    	if(sig){
    		ld p1 = normalize(tmp, mp(x.O, x.A));
    		ld p2 = normalize(tmp, mp(y.B, y.O));
    		if(-eps < p1 && p1 < 1 + eps
    				&& -eps < p2 && p2 < 1 + eps){
    			intersection_points.pb(tmp);
    		}
    	}
    	// x's AB intersects ...
    	// y's OA
    	tmp2 = cil(x.C, mp(y.O, y.A), sig);
    	if(sig){
    		{
    			tmp = tmp2.X;
    			ld p1 = normalize(tmp, mp(y.O, y.A));	
    			ld p2 = checkContained(x.A - x.O, x.B - x.O, tmp - x.O);
    			if(-eps < p1 && p1 < 1 + eps && p2 != -1){
    				intersection_points.pb(tmp);
    			}
    		}
    		{
    			tmp = tmp2.Y;
    			ld p1 = normalize(tmp, mp(y.O, y.A));	
    			ld p2 = checkContained(x.A - x.O, x.B - x.O, tmp - x.O);
    			if(-eps < p1 && p1 < 1 + eps && p2 != -1){
    				intersection_points.pb(tmp);
    			}
    		}
    	}
     
    	// y's AB
    	tmp2 = cic(x.C, y.C, sig);
    	if(sig){
    		{
    			tmp = tmp2.X;
    			ld p1 = checkContained(x.A - x.O, x.B - x.O, tmp - x.O);
    			ld p2 = checkContained(y.A - y.O, y.B - y.O, tmp - y.O);
    			if(p1 != -1 && p2 != -1){
    				intersection_points.pb(tmp);
    			}
    		}
    		{
    			tmp = tmp2.Y;
    			ld p1 = checkContained(x.A - x.O, x.B - x.O, tmp - x.O);
    			ld p2 = checkContained(y.A - y.O, y.B - y.O, tmp - y.O);
    			if(p1 != -1 && p2 != -1){
    				intersection_points.pb(tmp);
    			}
    		}
    	}
    	// y's BO
     
    	tmp2 = cil(x.C, mp(y.B, y.O), sig);
    	if(sig){
    		{
    			tmp = tmp2.X;
    			ld p1 = normalize(tmp, mp(y.B, y.O));	
    			ld p2 = checkContained(x.A - x.O, x.B - x.O, tmp - x.O);
    			if(-eps < p1 && p1 < 1 + eps && p2 != -1){
    				intersection_points.pb(tmp);
    			}
    		}
    		{
    			tmp = tmp2.Y;
    			ld p1 = normalize(tmp, mp(y.B, y.O));	
    			ld p2 = checkContained(x.A - x.O, x.B - x.O, tmp - x.O);
    			if(-eps < p1 && p1 < 1 + eps && p2 != -1){
    				intersection_points.pb(tmp);
    			}
    		}
    	}
     
    	// x's BO intersects ...
     
    	// y's OA
    	tmp = lil(mp(x.B, x.O), mp(y.O, y.A), sig);
    	if(sig){
    		ld p1 = normalize(tmp, mp(x.B, x.O));
    		ld p2 = normalize(tmp, mp(y.O, y.A));
    		if(-eps < p1 && p1 < 1 + eps
    				&& -eps < p2 && p2 < 1 + eps){
    			intersection_points.pb(tmp);
    		}
    	}
    	// y's AB
     
    	tmp2 = cil(y.C, mp(x.B, x.O), sig);
    	if(sig){
    		{
    			tmp = tmp2.X;
    			ld p1 = normalize(tmp, mp(x.B, x.O));	
    			ld p2 = checkContained(y.A - y.O, y.B - y.O, tmp - y.O);
    			if(-eps < p1 && p1 < 1 + eps && p2 != -1){
    				intersection_points.pb(tmp);
    			}
    		}
    		{
    			tmp = tmp2.Y;
    			ld p1 = normalize(tmp, mp(x.B, x.O));	
    			ld p2 = checkContained(y.A - y.O, y.B - y.O, tmp - y.O);
    			if(-eps < p1 && p1 < 1 + eps && p2 != -1){
    				intersection_points.pb(tmp);
    			}
    		}
    	}
     
    	// y's BO
    	tmp = lil(mp(x.B, x.O), mp(y.B, y.O), sig);
    	if(sig){
    		ld p1 = normalize(tmp, mp(x.B, x.O));
    		ld p2 = normalize(tmp, mp(y.B, y.O));
    		if(-eps < p1 && p1 < 1 + eps
    				&& -eps < p2 && p2 < 1 + eps){
    			intersection_points.pb(tmp);
    		}
    	}
     
    #undef lil
    #undef cil
    #undef cic
    	return intersection_points;
    }
    void sectorIntersectSector(int _, int __){
    	if(contained[_] || contained[__]) return ;
    	Sector &x = arr[_];
    	Sector &y = arr[__];
    	vector<Pt> ip = getIntersectPts(_, __);
    	if(!ip.size()){
    		if( pointInSector(y, x.O) ){
    			contained[_] = 1;
    			return ;
    		}
    		if( pointInSector(x, y.O)){
    			contained[__] = 1;
    			return ;
    		}
    		return ;
    	}
     
    	vector<ld> paramX = {0, 3};
    	for(Pt p: ip) paramX.pb(getParam(x, p));
    	vector<ld> paramY = {0, 3};
    	for(Pt p: ip) paramY.pb(getParam(y, p));
     
    	sort(all(paramX));
    	sort(all(paramY));
    	for(int i = 1; i < siz(paramX); i++){
    		if(abs(paramX[i] - paramX[i-1]) < eps) paramX.erase(paramX.begin()+i);
    	}
    	for(int i = 1; i < siz(paramY); i++){
    		if(abs(paramY[i] - paramY[i-1]) < eps) paramY.erase(paramY.begin()+i);
    	}
     
    	//debug(ip, paramX, paramY);
     
    	for(int i = 1; i < siz(paramX); i++){
    		Pt test = getPoint(x, (paramX[i-1] + paramX[i]) / 2);
    		if( pointInSector(y, test) ){
    			x.range.pb(mp(paramX[i-1], paramX[i]));
    		}
    	}
    	for(int i = 1; i < siz(paramY); i++){
    		Pt test = getPoint(y, (paramY[i-1] + paramY[i]) / 2);
    		if( pointInSector(x, test) ){
    			y.range.pb(mp(paramY[i-1], paramY[i]));
    		}
    	}
    }
     
    long double ans = 0;
     
    ld sumByParam(Sector& S, pair<ld, ld> p){
    	if(abs(p.ss - p.ff) < eps) return 0;
    	if(p.ff + eps < 1 && p.ss - eps > 1){
    		ld a = sumByParam(S, mp(p.ff, 1));
    		ld b = sumByParam(S, mp(1, p.ss));
    		return a + b;
    	}
    	if(p.ff + eps < 2 && p.ss - eps > 2){
    		ld a = sumByParam(S, mp(p.ff, 2));
    		ld b = sumByParam(S, mp(2, p.ss));
    		return a + b;
    	}
     
     
    	ld mid = (p.ff + p.ss) / 2;
    	ld tmp;
    	Pt st = getPoint(S, p.ff);
    	Pt ed = getPoint(S, p.ss);
    	if( mid < 1 || mid > 2){
    		tmp = (st.X * ed.Y - st.Y * ed.X) / 2;
    	}else{
    		ld alpha = angleInterp(S.alpha, S.beta, p.ff - 1);
    		ld beta = angleInterp(S.alpha, S.beta, p.ss - 1);
    		ld tmp1 = S.C.r * ( S.O.X * sinl(alpha) - S.O.Y * cosl(alpha) ) / 2;
    		ld tmp2 = S.C.r * ( S.O.X * sinl(beta ) - S.O.Y * cosl(beta ) ) / 2;
     
    		tmp = tmp2 - tmp1;
    		tmp += topos(beta - alpha) * S.C.r * S.C.r / 2;
    	}
     
    	// debug(S.O, S.A, S.B, p, tmp, st, ed);
    	return tmp;
    }
     
    signed main(){
     
    	cin.tie(0);
    	ios_base::sync_with_stdio(false);
     
    	int n;
    	cin >> n;
    	for(int i = 0; i < n; i++){ // input
    		Pt O, A, B;
    		cin >> O.X >> O.Y >> A.X >> A.Y >> B.X >> B.Y;
    		arr[i].C.O = O, arr[i].C.r = sqrtl(abs2(O - A));
    		arr[i].alpha = PolarAngle(A - O);
    		arr[i].beta = PolarAngle(B - O);
    		arr[i].O = O;
    		arr[i].A = A;
    		arr[i].B = B;
    	}
     
    	for(int i = 0; i < n; i++){
    		debug(i);
    		cerr.flush();
    		for(int j = i+1; j < n; j++){
    			if(!contained[i] && !contained[j]) sectorIntersectSector(i, j);
    		}
    	}
     
    	for(int i = 0; i < n; i++){
    		if(contained[i]) continue;
    		if(!arr[i].range.size()){
    			//ld tmp = topos(arr[i].beta - arr[i].alpha) / 2 * abs2(arr[i].B - arr[i].O);	
    			//ans += tmp;
    			ans += sumByParam(arr[i], mp(0, 3));
    			//debug(tmp);
    			continue;
    		}
    		vector<pair<ld, int> > temp;
    		for(auto p : arr[i].range){
    			temp.pb(mp(p.ff, 1));
    			temp.pb(mp(p.ss, -1));
    		}
    		sort(all(temp));
    		int layer = 0;
    		ld ptr = 0;
    		for(auto p : temp){
    			if(layer == 0){
    				ans += sumByParam(arr[i], mp(ptr, p.ff));
    			}
    			layer += p.ss;
    			if(layer == 0){
    				ptr = p.ff;
    			}
    		}
    		ans += sumByParam(arr[i], mp(ptr, 3));
     
    	}
     
    	cout << fixed << setprecision(20) << ans;
     
    	return 0;
    }

		for (char c : s) {
			if (!~nx[X][c - 'a']) nx[X][c - 'a'] = newnode();
			X = nx[X][c - 'a'];
		}
		return X;
	}
	void make_fl() { //fail link
		queue<int> q;
		q.push(1), fl[1] = 0;
		for (int t = 0; !q.empty();) {
			int R = q.front();
			q.pop(), pri[t++] = R;
			for (int i = 0; i < sigma; ++i)
				if (~nx[R][i]) {
					int X = nx[R][i], Z = fl[R];
					for (; Z && !~nx[Z][i];) Z = fl[Z];
					fl[X] = Z ? nx[Z][i] : 1, q.push(X);
				}
		}
	}
	void get_v(string &s) {
		int X = 1;
		fill(cnt, cnt + top, 0);
		for (char c : s) {
			while (X && !~nx[X][c - 'a']) X = fl[X];
			X = X ? nx[X][c - 'a'] : 1, ++cnt[X];
		}
		for (int i = top - 2; i > 0; --i)
			cnt[fl[pri[i]]] += cnt[pri[i]];
	}
};
