ostream& operator<<(ostream &o, pair<auto, auto> p)
{ return o << '(' << p.ff << ',' << p.ss << ')'; }
#ifdef zisk
void debug() { cerr << "\033[0m\n"; }
template<class T> void _d(T&& x) {
  if constexpr (ranges::range<T>) { cerr << "{ "; 
    for (auto&& i : x) _d(i); cerr << "} "; 
  } else cerr << x << " ";
} // ranges::subrange(l, r)
void debug(auto&&... a) 
{ cerr << "\033[33m"; (_d(a), ...); debug(); }
#else
#define debug(...) void()
#endif
