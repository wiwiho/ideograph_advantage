struct exSAM {
  const int CNUM = 26;
  // len: maxlength, link: fail link
  // lenSorted: topo order, cnt: occur
  vector<int> len, link, lenSorted, cnt;
  vector<vector<int>> next;
  int total = 0;
  int newnode() {
    return total++; 
  }
  void init(int n) { // total number of characters
    len.assign(2 * n, 0); link.assign(2 * n, 0);
    lenSorted.assign(2 * n, 0); cnt.assign(2 * n, 0);
    next.assign(2 * n, vector<int>(CNUM));
    newnode(), link[0] = -1; 
  }
  int insertSAM(int last, int c) {
    // not exSAM: cur = newnode(), p = last
    int cur = next[last][c];
    len[cur] = len[last] + 1;
    int p = link[last];
    while (p != -1 && !next[p][c])
      next[p][c] = cur, p = link[p];
    if (p == -1) return link[cur] = 0, cur;
    int q = next[p][c];
    if (len[p] + 1 == len[q]) return link[cur] = q, cur;
    int clone = newnode();
    for (int i = 0; i < CNUM; ++i)
      next[clone][i] = len[next[q][i]] ? next[q][i] : 0;
    len[clone] = len[p] + 1;
    while (p != -1 && next[p][c] == q)
      next[p][c] = clone, p = link[p];
    link[link[cur] = clone] = link[q];
    link[q] = clone;
    return cur;
  }
  void insert(const string &s) {
    int cur = 0;
    for (auto ch : s) {
      int &nxt = next[cur][int(ch - 'a')];
      if (!nxt) nxt = newnode();
      cnt[cur = nxt] += 1;
    }
  }
  void build() {
    queue<int> q;
    q.push(0);
    while (!q.empty()) {
      int cur = q.front();
      q.pop();
      for (int i = 0; i < CNUM; ++i)
        if (next[cur][i])
          q.push(insertSAM(cur, i));
    }
    vector<int> lc(total);
    for (int i = 1; i < total; ++i) ++lc[len[i]];
    partial_sum(iter(lc), lc.begin());
    for (int i = 1; i < total; ++i) lenSorted[--lc[len[i]]] = i;
  }
  void solve() {
    for (int i = total - 2; i >= 0; --i)
      cnt[link[lenSorted[i]]] += cnt[lenSorted[i]];
  }
};
