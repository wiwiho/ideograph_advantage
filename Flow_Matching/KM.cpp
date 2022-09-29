int n, m; //1-base, max matching
int mx[maxn], my[maxn];
bool adj[maxn][maxn], vis[maxn];
bool dfs(int n) {
	if (vis[n]) return false;
	vis[n] = 1;
	for (int v = 1;v <= n;v++) {
		if (!adj[n][v]) continue;
		if (!my[v] || (my[v] && dfs(my[v]))) {
			mx[n] = v, my[v] = n;
			return true;
		}
	}
	return false;
}
//min vertex cover: take unmatched vertex in L and find alternating tree,
//ans is not reached in L + reached in R
