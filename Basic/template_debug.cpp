ostream& operator<<(ostream &o, pair<auto, auto> p) {
  return o << '(' << p.ff << ',' << p.ss << ')';
}

#ifdef zisk
void debug() { cerr << "\n"; }
void debug(auto... a) { ((cerr << a << " "), ...) << "\n"; }
void pary(auto &&range) {
  for (auto i : range) cerr << i << " ";
  cerr << "\n";
}
void pary(auto l, auto r) { pary(ranges::subrange(l, r)); }
#else
#define debug(...) void()
#define pary(...) void()
#endif
