//Challenge: Accepted
#include <bits/stdc++.h>
#define MAXN 1005
#define INF 1e9
#define pb push_back
using namespace std;
struct MaxFlow { // 1-base
	struct edge {
		int to, cap, flow, rev;
	};
	vector<edge> g[MAXN];
	int s, t, dis[MAXN], ind[MAXN], n;

	void init(int _n) {
		n = _n + 2;
		s = _n + 1, t = _n + 2;
		for (int i = 0; i <= n; ++i) g[i].clear();
	}
	void reset() {
		for (int i = 0; i <= n; ++i)
			for (auto &j : g[i]) j.flow = 0;
	}
	void addedge(int u, int v, int cap) {
		g[u].pb(edge{v, cap, 0, (int)g[v].size()});
		g[v].pb(edge{u, cap, 0, (int)g[u].size() - 1});
	}
	bool bfs() {
		fill(dis, dis+n+1, -1);
		queue<int> q;
		q.push(s), dis[s] = 0;
		while (!q.empty()) {
			int cur = q.front(); q.pop();
			for (auto &e : g[cur]) {
				if (dis[e.to] == -1 && e.flow != e.cap) {
					q.push(e.to);
					dis[e.to] = dis[cur] + 1;
				}
			}
		}
		return dis[t] != -1;
	}
	int dfs(int u, int cap) {
		if (u == t || !cap) return cap;
		for (int &i = ind[u]; i < (int)g[u].size(); ++i) {
			edge &e = g[u][i];
			if (dis[e.to] == dis[u] + 1 && e.flow != e.cap) {
				int df = dfs(e.to, min(e.cap - e.flow, cap));
				if (df) {
					e.flow += df;
					g[e.to][e.rev].flow -= df;
					return df;
				}
			}
		}
		dis[u] = -1;
		return 0;
	}
	int maxflow() {
		int flow = 0, df;
		while (bfs()) {
			fill(ind, ind+n+1, 0);
			while ((df = dfs(s, INF))) flow += df;
		}
		return flow;
	}
}flow;
int main() {
	int n;
	int cases = 1;
	while (cin >> n && n) {
		int s, t, m;
		cin >> s >> t >> m;	
		flow.init(n - 2);
		flow.s = s, flow.t = t;
		for (int i = 0;i < m;i++) {
			int u, v, w;
			cin >> u >> v >> w;
			flow.addedge(u, v, w);
		}
		cout << "Network " << cases << "\n";
		cout << "The bandwidth is " << flow.maxflow() << ".\n\n";	
		cases++;
	}
}
