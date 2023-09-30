const int maxn = 300005, maxc = 26;
struct AC_Automaton { //1-base
	int nx[maxn][maxc], fl[maxn], cnt[maxn], pri[maxn], tot;
	//pri: bfs order of trie (0-base)
	int newnode() {
		tot++;
		fill(nx[tot], nx[tot] + maxc, -1);
		return tot;
	}
	void init() { tot = 0, newnode(); }
	int input(string &s) { // return the end_node of string
		int X = 1;
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
			for (int i = 0; i < maxc; ++i)
				if (~nx[R][i]) {
					int X = nx[R][i], Z = fl[R];
					for (; Z && !~nx[Z][i];) Z = fl[Z];
					fl[X] = Z ? nx[Z][i] : 1, q.push(X);
				}
		}
	}
	void get_v(string &s) {
		//number of times prefix appears in strings
		int X = 1;
		fill(cnt, cnt + tot+1, 0);
		for (char c : s) {
			while (X && !~nx[X][c - 'a']) X = fl[X];
			X = X ? nx[X][c - 'a'] : 1, ++cnt[X];
		}
		for (int i = tot-1; i > 0; --i)
			cnt[fl[pri[i]]] += cnt[pri[i]];
	}
} ac;

