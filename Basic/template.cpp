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

template<class A, class B>
ostream& operator<<(ostream& o, pair<A,B> p)
{ return o << '(' << p.ff << ',' << p.ss << ')'; }

#ifdef zisk
void debug(){cerr << "\n";}
template<class T, class ... U>
void debug(T a, U ... b){cerr << a << " ", debug(b...);}
template<class T> void pary(T l, T r){
  while (l != r) cerr << *l << " ", l++;
  cerr << "\n";
}
#else
#define debug(...) void()
#define pary(...) void()
#endif

int main(){
  ios_base::sync_with_stdio(false); cin.tie(0);
}
