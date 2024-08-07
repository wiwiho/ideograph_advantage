template<class T>
struct DynamicHull {
  struct seg { int x, l, r; };
  T f; int C; deque<seg> dq; // range: 1~C
  explicit DynamicHull(T _f, int _C): f(_f), C(_C) {}
  // max t s.t. f(x, t) >= f(y, t), x < y, maintain max
  int intersect(int x, int y) {
    int l = 0, r = C + 1;
    while (l + 1 < r) {
      int mid = (l + r) / 2;
      if (f(x, mid) >= f(y, mid)) l = mid;
      else r = mid;
    }
    return l;
  }
  void push_back(int x) {
    for (int i; !dq.empty() && 
        (i = dq.back().l, f(dq.back().x, i) < f(x, i)); )
      dq.pop_back();
    if (dq.empty()) return dq.pb(seg({x, 1, C})), void();
    dq.back().r = intersect(dq.back().x, x);
    dq.pb(seg({x, dq.back().l + 1, C}));
  }
  int query(int x) {
    while (dq.front().r < x) dq.pop_front();
    return dq.front().x;
  }
};
