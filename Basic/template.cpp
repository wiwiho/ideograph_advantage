//Challenge: Accepted
//#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

#define io ios_base::sync_with_stdio(0);cin.tie(0)
#define iter(v) v.begin(),v.end()
#define SZ(v) (int)v.size()
#define pb emplace_back
#define mp make_pair
#define ff first
#define ss second

using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

#ifdef zisk
void debug(){cout << endl;}
template<class T, class ... U>
void debug(T a, U ... b){cout << a << " ", debug(b...);}
template<class T> void pary(T l, T r){
	while (l != r) cout << *l << " ", l++;
	cout << endl;
}
#else
#define debug(...) void()
#define pary(...) void()
#endif
template<class A, class B>
ostream& operator<<(ostream& o, pair<A,B> p)
    { return o << '(' << p.ff << ',' << p.ss << ')'; }

int main(){
	io;
}
