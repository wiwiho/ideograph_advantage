// from 8BQube
// at most 2n-1 states, 3n-4 edges

// to find longest common substring for multiple strings S_1, ..., S_k
// assign a special (distinct) character D_i to each string
// let T = S_1 D_1 ... S_k D_k, then build SAM of T
// answer is state with max length reachable to all D_i
const int maxn = 1000010;
struct SAM { //1 base
  vector<int> adj[maxn];
  int tot, root, lst, par[maxn], mx[maxn], fi[maxn], iter;
  //mx:maxlen of node, mx[par[i]]+1:minlen of node
  //fi: first endpos
  //corresponding substring of node can be found by fi and mx
  int nxt[maxn][33];
  int newNode() {
    int res = ++tot;
    fill(nxt[res], nxt[res] + 33, 0);
    par[res] = mx[res] = 0;
    fi[res] = iter;
    return res;
  }
  void init() {
    tot = 0;
    iter = 0;
    root = newNode();
    par[root] = 0, mx[root] = 0;
    lst = root;
  }
  void push(int c) {
    int p = lst;
    int np = newNode();
    mx[np] = mx[p] + 1;
    for (; p && nxt[p][c] == 0; p = par[p])
      nxt[p][c] = np;
    if (p == 0) par[np] = root;
    else {
      int q = nxt[p][c];
      if (mx[p] + 1 == mx[q]) par[np] = q;
      else {
        int nq = newNode();
        mx[nq] = mx[p] + 1;
        for (int i = 0; i < 33; i++)
          nxt[nq][i] = nxt[q][i];
        par[nq] = par[q];
        fi[nq] = fi[q];
        par[q] = nq;
        par[np] = nq;
        for (; p && nxt[p][c] == q; p = par[p])
          nxt[p][c] = nq;
      }
    }
    lst = np;
  }

  void push(string str) {
    for (int i = 0; str[i]; i++) {
      iter++;
      push(str[i] - 'a' + 1);
    }
  }
  ll get_diff_strings(){
    ll tot = 0;
    for(int i = 1; i <= tot; i++) tot += mx[i] - mx[par[i]];
    return tot;
  }
  bool in[maxn];
  int cnt[maxn]; //cnt is number of occurences of node
  void count() {
    for (int i = 1; i <= tot; ++i)
      ++in[par[i]];
    queue<int> q;
    for (int i = 1; i <= tot; ++i)
      if (!in[i]) q.push(i);
    while (!q.empty()) {
      int u = q.front();
      q.pop();
      cnt[par[u]] += cnt[u];
      if (!--in[par[u]])
        q.push(par[u]);
    }
  }
} sam;
