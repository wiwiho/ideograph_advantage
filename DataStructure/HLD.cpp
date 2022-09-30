struct Heavy_light_Decomposition { // 1-base
	int n, up[maxn], dep[maxn], to[maxn], siz[maxn], pa[maxn];
	int C, ti[maxn], ord[maxn], wdown[maxn], edge[maxn], et = 0;
	vector<pii> G[maxn];
	void init(int _n) {
		n = _n, C = 0, et = 1;
		for (int i = 1;i <= n;i++) 
			G[i].clear(), to[i] = 0;
	}
	void add_edge(int a, int b, int w) {
		G[a].push_back(pii(b, et)), G[b].push_back(pii(a, et));
		edge[et++] = w;
	}
	void dfs(int u, int f, int d) {
		siz[u] = 1, pa[u] = f, dep[u] = d;
		for (auto &v: G[u]) 
			if (v.ff != f) {
				dfs(v.ff, u, d+1), siz[u] += siz[v];
				if (siz[to[u]] < siz[v]) to[u] = v;
			} 
	}
	void cut(int u, int link) {
		ti[u] = C;
		ord[C++] = u, up[u] = link;
		if (!to[u]) return;
		cut(to[u], link);
		for (auto v:G[u]) {
			if (v.ff != pa[u] && v.ff != to[u]) cut(v.ff, v.ff);
		}
	}
	void build() { dfs(1, 1, 1), cut(1, 1); }
	int query(int a, int b) {
		int ta = up[a], tb = up[b], re = 0;
		while (ta != tb)
			if (dep[ta] < dep[tb])
				/*query*/, tb = up[b = pa[tb]];
			else /*query*/, ta = up[a = pa[ta]];
		if (a == b) return re;
		if (ti[a] > ti[b]) swap(a, b);
		/*query*/
		return re;
	}	
};
