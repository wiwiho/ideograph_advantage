const int digit = 60; // [0, 2^digit)
struct Basis{
  int total = 0, rank = 0;
  vector<ll> b;
  Basis(): b(digit) {}
  bool add(ll v){ // Gauss Jordan Elimination
    total++;
    for(int i = digit - 1; i >= 0; i--){
      if(!(1LL << i & v)) continue;
      if(b[i] != 0){
        v ^= b[i];
        continue;
      }
      for(int j = 0; j < i; j++)
        if(1LL << j & v) v ^= b[j];
      for(int j = i + 1; j < digit; j++)
        if(1LL << i & b[j]) b[j] ^= v;
      b[i] = v;
      rank++;
      return true;
    }
    return false;
  }
  ll getmax(ll x = 0){
    for(ll i : b) x = max(x, x ^ i);
    return x;
  }
  ll getmin(ll x = 0){
    for(ll i : b) x = min(x, x ^ i);
    return x;
  }
  bool can(ll x){
    return getmin(x) == 0;
  }
  ll kth(ll k){ // kth smallest, 0-indexed
    vector<ll> tmp;
    for(ll i : b) if(i) tmp.pb(i);
    ll ans = 0;
    for(int i = 0; i < SZ(tmp); i++)
      if(1LL << i & k) ans ^= tmp[i];
    return ans;
  }
};
