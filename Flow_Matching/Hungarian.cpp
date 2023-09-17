struct KM{ //1-base, max perfect matching in O(n^3)
	int n;
	int c[maxn][maxn];
	int lx[maxn], ly[maxn], mx[maxn], my[maxn], slack[maxn];
	bool vx[maxn], vy[maxn];
	bool dfs(int p, bool ch) {
		if (vx[p]) return 0;
		vx[p] = 1;
		for (int v = 1;v <= n;v++) {
			slack[v] = min(slack[v], lx[p] + ly[v] - c[p][v]);
			if (lx[p] + ly[v] - c[p][v] > 0) continue;
			vy[v] = 1;
			if (!my[v] || dfs(my[v], ch)) {
				if (ch) mx[p] = v, my[v] = p;
				return 1;
			}
		}
		return 0;
	}
	ll solve() {
		for (int i = 1;i <= n;i++){
			lx[i] = -inf;
      for (int j = 1;j <= n;j++) lx[i] = max(lx[i], a[i][j]);
		}
		for (int i = 1;i <= n;i++) {
			for (int j = 1;j <= n;j++) vx[j] = vy[j] = 0;
			for (int j = 1;j <= n;j++) slack[j] = inf; 
			if (dfs(i, 1)) continue;
			bool aug = 0;
			while (!aug) {
				for (int j = 1;j <= n;j++) {
					if (!vy[j] && slack[j] == 0) { 
						vy[j] = 1;
						if (dfs(my[j], 0)) {
							aug = 1;
							break;
						}
					}
				}
				if (aug) break;
				int delta = inf;
				for (int j = 1;j <= n;j++) {
					if (!vy[j]) delta = min(delta, slack[j]);
				}
				for (int j = 1;j <= n;j++) {
					if (vx[j]) lx[j] -= delta;
					if (vy[j]) ly[j] += delta;
					else {
						slack[j] -= delta;
						if (slack[j] == 0 && !my[j]) aug = 1; 
					}
				}
			}
			for (int j = 1;j <= n;j++) vx[j] = vy[j] = 0;
			dfs(i, 1);
		}
		ll ans = 0;
		for (int i = 1;i <= n;i++) ans += lx[i] + ly[i];
		return ans;
	}
};
