// stoer wagner algorithm: global min cut
const int maxn = 505;
struct SW { // O(V^3) 0-based
	int n, vis[maxn], del[maxn];
	int edge[maxn][maxn], wei[maxn];
	void init(int _n) {
		n = _n;
		fill(del, del+n, 0);
		for (int i = 0;i < n;i++) fill(edge[i], edge[i] + n, 0);
	}
	void addEdge(int u, int v, int w) {
		edge[u][v] += w, edge[v][u] += w;
	}
	void search(int &s, int &t) {
		fill(vis, vis+n, 0);	
		fill(wei, wei+n, 0);
		s = t = -1;
		while (1) {
			int ma = -1, cur = 0;
			for (int i = 0; i < n; ++i)
				if (!del[i] && !vis[i] && ma < wei[i])
					cur = i, ma = wei[i];
			if (mx == -1) break;
			vis[cur] = 1, s = t, t = cur;
			for (int i = 0; i < n; ++i)
				if (!vis[i] && !del[i]) wei[i] += edge[cur][i];
		}
	}
	int solve() {
		int ret = INF;
		for (int i = 0, x=0, y=0; i < n-1; ++i) {
			search(x, y), ret = min(res, wei[y]), del[y] = 1;
			for (int j = 0; j < n; ++j)
				edge[x][j] = (edge[j][x] += edge[y][j]);
		}
		return ret;
	}
};
