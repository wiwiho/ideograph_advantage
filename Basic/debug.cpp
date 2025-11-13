#ifdef zisk
void debug() { cerr << "\e[0m\n"; }
template<class T> void _d(T&& x) { // SCOPE HASH
  if constexpr (ranges::range<T> && 
      !is_convertible_v<T, string_view>) {
    cerr << "{ "; for (auto&& i : x) _d(i); 
    cerr << "} "; 
  } else if constexpr (requires { get<0>(x); }) {
    cerr << "( ";
    apply([](auto&&... a){ (_d(a), ...); }, x);
    cerr << ") ";
  } else cerr << x << " ";
} // ranges::subrange(l, r)
void debug(auto&&... a) 
{ cerr << "\e[1;33m"; (_d(a), ...); debug(); }
#define safe debug(__PRETTY_FUNCTION__,__LINE__,"safe")
#else
#define safe void()
#define debug(...) void()
#endif
