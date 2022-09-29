void kmp(string s){
	int siz = s.size();
	vector<int> f(siz, 0);
	f[0] = 0;
	for (int i = 1;i < siz;i++) {
		f[i] = f[i-1];
		bool zero = 0;
		while (s[f[i]] != s[i]) {
			if (f[i] == 0) {
				zero = 1;
				break;	
			}
			f[i] = f[f[i]-1];
		}
		if (!zero) f[i]++;
	}
}
