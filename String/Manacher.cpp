/* center i: radius z[i * 2 + 1] / 2
   center i, i + 1: radius z[i * 2 + 2] / 2
   both aba, abba have radius 2 */
vector<int> manacher(const string &tmp){ // 0-based
  string s = "%";
  int l = 0, r = 0;
  for(char c : tmp) s += c, s += '%';
  vector<int> z(SZ(s));
  for(int i = 0; i < SZ(s); i++){
    z[i] = r > i ? min(z[2 * l - i], r - i) : 1;
    while(i - z[i] >= 0 && i + z[i] < SZ(s) 
           && s[i + z[i]] == s[i - z[i]]) 
      ++z[i];
    if(z[i] + i > r) r = z[i] + i, l = i;
  }
  return z;
}
