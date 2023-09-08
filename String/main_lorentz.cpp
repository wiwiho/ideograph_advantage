vector<int> z_function(string const& s);
int get_z(vector<int> const& z, int i) {
  return (0 <= i && i < SZ(z)) ? z[i] : 0;
}
vector<pair<int, int>> rep;

void convert_to_rep(int shift, bool left, int cntr, int l, int k1, int k2) {
	int lef = max(1, l-k2), rig = min(l, k1);
	int minl, maxl;
	if (left) {
		rig = min(rig, l-1);
		minl = shift + cntr - rig, maxl = shift+cntr-lef;	
	} else {
		minl = shift + cntr - l - rig + 1, maxl = shift + cntr - l - lef + 1; 
	}
	//left endpoint: [minl, maxl], length: 2*l
}

void find_rep(string s, int shift = 0) {
  int n = s.size();
  if (n == 1) return;

  int nu = n / 2;
  int nv = n - nu;
  string u = s.substr(0, nu);
  string v = s.substr(nu);
  string ru(u.rbegin(), u.rend());
  string rv(v.rbegin(), v.rend());

  find_rep(u, shift);
  find_rep(v, shift + nu);

  vector<int> z1 = z_function(ru);
  vector<int> z2 = z_function(v + '#' + u);
  vector<int> z3 = z_function(ru + '#' + rv);
  vector<int> z4 = z_function(v);

  for (int cntr = 0; cntr < n; cntr++) {
    int l, k1, k2;
    if (cntr < nu) {
      l = nu - cntr;
      k1 = get_z(z1, nu - cntr);
      k2 = get_z(z2, nv + 1 + cntr);
    } else {
      l = cntr - nu + 1;
      k1 = get_z(z3, nu + 1 + nv - 1 - (cntr - nu));
      k2 = get_z(z4, (cntr - nu) + 1);
    }
    if (k1 + k2 >= l)
      convert_to_rep(shift, cntr < nu, cntr, l, k1, k2);
  }
}

