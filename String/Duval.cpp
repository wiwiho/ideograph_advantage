// partition s = w[0] + w[1] + ... + w[k-1],
// w[0] >= w[1] >= ... >= w[k-1]
// each w[i] strictly smaller than all its suffix
void duval(const string &s, vector<pii> &w) {
  for (int n = (int)s.size(), i = 0, j, k; i < n; ) {
    for (j = i + 1, k = i; j < n && s[k] <= s[j]; j++)
      k = (s[k] < s[j] ? i : k + 1);
    // if (i < n / 2 && j >= n / 2) {
    // for min cyclic shift, call duval(s + s)
    // then here s.substr(i, n / 2) is min cyclic shift
    // }
    for (; i <= k; i += j - k)
      w.pb(pii(i, j - k)); // s.substr(l, len)
  }
}
