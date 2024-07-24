struct E { int s, t; ll w; }; // 0-base
struct PQ {
  struct P {
    ll v; int i;
    bool operator>(const P &b) const { return v > b.v; }
  };
  priority_queue<P, vector<P>, greater<>> pq; ll tag; // min heap
  void push(P p) { p.v -= tag; pq.emplace(p); }
  P top() { P p = pq.top(); p.v += tag; return p; }
  void join(PQ &b) {
    if (pq.size() < b.pq.size())
      swap(pq, b.pq), swap(tag, b.tag);
    while (!b.pq.empty()) push(b.top()), b.pq.pop();
  }
}; // O(E log^2 V), use leftist tree for O(E log V)
vector<int> dmst(const vector<E> &e, int n, int root) {
  vector<PQ> h(n * 2);
  for (int i = 0; i < int(e.size()); ++i)
    h[e[i].t].push({e[i].w, i});
  vector<int> a(n * 2); iota(iter(a), 0);
  vector<int> v(n * 2, -1), pa(n * 2, -1), r(n * 2);
  auto o = [&](auto Y, int x) -> int {
    return x==a[x] ? x : a[x] = Y(Y, a[x]); };
  auto S = [&](int i) { return o(o, e[i].s); };
  int pc = v[root] = n;
  for (int i = 0; i < n; ++i) if (v[i] == -1)
    for (int p = i; v[p]<0 || v[p]==i; p = S(r[p])) {
      if (v[p] == i)
        for (int q = pc++; p != q; p = S(r[p])) {
          h[p].tag -= h[p].top().v; h[q].join(h[p]);
          pa[p] = a[p] = q;
        }
      while (S(h[p].top().i) == p) h[p].pq.pop();
      v[p] = i; r[p] = h[p].top().i;
    }
  vector<int> ans;
  for (int i = pc - 1; i >= 0; i--) if (v[i] != n) {
    for (int f = e[r[i]].t; f!=-1 && v[f]!=n; f = pa[f])
      v[f] = n;
    ans.push_back(r[i]);
  }
  return ans; // default minimize, returns edgeid array
}
