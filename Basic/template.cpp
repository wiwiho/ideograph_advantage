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

int main(){
  ios_base::sync_with_stdio(false); cin.tie(0);
}
