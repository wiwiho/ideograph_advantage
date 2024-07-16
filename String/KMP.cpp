// 0-based
// fail[i] = max k<i s.t. s[0..k] = s[i-k..i]
vector<int> kmp_build_fail(const string &s){
  int n = SZ(s);
  vector<int> fail(n, -1);
  int cur = -1;
  for(int i = 1; i < n; i++){
    while(cur != -1 && s[cur + 1] != s[i])
      cur = fail[cur];
    if(s[cur + 1] == s[i])
      cur++;
    fail[i] = cur;
  }
  return fail;
}

void kmp_match(const string &s, const vector<int> &fail, const string &t){
  int cur = -1;
  int n = SZ(s), m = SZ(t);
  for(int i = 0; i < m; i++){
    while(cur != -1 && (cur + 1 == n || s[cur + 1] != t[i]))
      cur = fail[cur];
    if(cur + 1 < n && s[cur + 1] == t[i])
      cur++;
    // cur = max k s.t. s[0..k] = t[i-k..i]
  }
}
