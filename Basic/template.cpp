#include <bits/stdc++.h>
using namespace std;

#define iter(v) v.begin(),v.end()
#define SZ(v) int(v.size())
#define pb emplace_back
#define ff first
#define ss second
#define fs ff
#define sc ss

using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

#ifdef zisk
void debug() { cerr << "\e[0m\n"; }
template<class T> void _d(T&& x) {
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

int main(){
  ios_base::sync_with_stdio(false); cin.tie(0);
}
