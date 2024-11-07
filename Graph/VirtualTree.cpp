// copy from 8BQube
vector<int> vG[N];
int top, st[N];
int vrt = -1;

void insert(int u) {
	if (top == -1) return st[++top] = vrt = u, void();
	int p = LCA(st[top], u);
    if(dep[vrt] > dep[p]) vrt = p;
	if (p == st[top]) return st[++top] = u, void();
	while (top >= 1 && dep[st[top - 1]] >= dep[p])
		vG[st[top - 1]].pb(st[top]), --top;
	if (st[top] != p)
		vG[p].pb(st[top]), --top, st[++top] = p;
	st[++top] = u;
}

void reset(int u) {
	for (int i : vG[u]) reset(i);
	vG[u].clear();
}

void solve(vector<int> &v) {
	top = -1;
	sort(iter(v),
			[&](int a, int b) { return dfn[a] < dfn[b]; });
	for (int i : v) insert(i);
	while (top > 0) vG[st[top - 1]].pb(st[top]), --top;
	// do something
	reset(vrt);
}
