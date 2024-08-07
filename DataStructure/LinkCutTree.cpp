// 1-based
template <typename Val, typename SVal> struct LCT {
  struct node {
    int pa, ch[2]; bool rev; int size;
    Val v, sum, rsum; SVal sv, sub, vir;
    node() : pa{0}, ch{0, 0}, rev{false}, size{1}, v{},
      sum{}, rsum{}, sv{}, sub{}, vir{} {}
  };
#define cur o[u]
#define lc cur.ch[0]
#define rc cur.ch[1]
  vector<node> o;
  bool is_root(int u) const {
    return o[cur.pa].ch[0]!=u && o[cur.pa].ch[1]!=u; }
  bool is_rch(int u) const {
    return o[cur.pa].ch[1] == u && !is_root(u); }
  void down(int u) {
    for (int c : {lc, rc}) if (c) {
      if (cur.rev) set_rev(c);
    }
    cur.rev = false;
  }
  void up(int u) {
    cur.sum = o[lc].sum + cur.v + o[rc].sum;
    cur.rsum = o[rc].rsum + cur.v + o[lc].rsum;
    cur.sub = cur.vir + o[lc].sub + o[rc].sub + cur.sv;
    cur.size = o[lc].size + o[rc].size + 1;
  }
  void set_rev(int u) {
    swap(lc, rc), swap(cur.sum, cur.rsum);
    cur.rev ^= 1;
  }
  /* --- */
  void rotate(int u) {
    int f = cur.pa, g = o[f].pa, l = is_rch(u);
    if (cur.ch[l ^ 1]) o[cur.ch[l ^ 1]].pa = f;
    if (not is_root(f)) o[g].ch[is_rch(f)] = u;
    o[f].ch[l] = cur.ch[l ^ 1], cur.ch[l ^ 1] = f;
    cur.pa = g, o[f].pa = u; up(f);
  }
  void splay(int u) {
    vector<int> stk = {u};
    while (not is_root(stk.back()))
      stk.push_back(o[stk.back()].pa);
    while (not stk.empty())
      down(stk.back()), stk.pop_back();
    for (int f = cur.pa; not is_root(u); f = cur.pa) {
      if (!is_root(f))
        rotate(is_rch(u) == is_rch(f) ? f : u);
      rotate(u);
    }
    up(u);
  }
  void access(int x) {
    for (int u = x, last = 0; u; u = cur.pa) {
      splay(u);
      cur.vir = cur.vir + o[rc].sub - o[last].sub;
      rc = last; up(last = u);
    }
    splay(x);
  }
  int find_root(int u) {
    int la = 0;
    for (access(u); u; u = lc) down(la = u);
    return la;
  }
  void split(int x, int y) { chroot(x); access(y); }
  void chroot(int u) { access(u); set_rev(u); }
  /* --- */
  LCT(int n = 0) : o(n + 1) { o[0].size = 0; }
  void set_val(int u, const Val &v) {
    splay(u); cur.v = v; up(u); }
  void set_sval(int u, const SVal &v) {
    access(u); cur.sv = v; up(u); }
  Val query(int x, int y) {
    split(x, y); return o[y].sum; }
  SVal subtree(int p, int u) {
    chroot(p); access(u); return cur.vir + cur.sv; }
  bool connected(int u, int v) {
    return find_root(u) == find_root(v); }
  void link(int x, int y) {
    chroot(x); access(y);
    o[y].vir = o[y].vir + o[x].sub; 
    up(o[x].pa = y);
  }
  void cut(int x, int y) {
    split(x, y); o[y].ch[0] = o[x].pa = 0; up(y); }
#undef cur
#undef lc
#undef rc
};
