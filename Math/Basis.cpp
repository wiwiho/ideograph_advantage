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
};
