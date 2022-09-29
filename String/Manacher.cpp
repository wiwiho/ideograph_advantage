vector<int> manacher(string s) {
	int n = s.size();
	vector<int> v(n);
	int pnt = -1, len = 1;
	for (int i = 0;i < n;i++) {
		int cor = 2 * pnt - i;
		if (cor >= 0) v[i] = min(v[cor], cor - pnt + len);
		while (i+v[i] < n && i-v[i] >= 0 && s[i+v[i]] == s[i-v[i]]) v[i]++;
		if (i + v[i] >= pnt + len) pnt = i, len = v[i];	
	}
	for (int i = 0;i < n;i++) v[i] = 2 * v[i] - 1;
	return v;	
}
