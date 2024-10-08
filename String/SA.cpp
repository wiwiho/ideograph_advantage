struct SuffixArray {
  vector<int> sa, lcp, rank; // lcp[i] is lcp of sa[i] and sa[i-1]
                             // sa[0] = s.size()
                             // character should be 1-based
  SuffixArray(string& s, int lim=256) { // or basic_string<int>
    int n = s.size() + 1, k = 0, a, b;
    vector<int> x(n, 0), y(n), ws(max(n, lim));
    rank.assign(n, 0);
    for (int i = 0; i < n - 1; i++) x[i] = s[i];
    sa = lcp = y, iota(sa.begin(), sa.end(), 0);
    for (int j = 0, p = 0; p < n; j = max(1, j * 2), lim = p) {
      p = j, iota(y.begin(), y.end(), n - j);
      for (int i = 0; i < n; i++) 
        if (sa[i] >= j) y[p++] = sa[i] - j;
      for (int &i : ws) i = 0;
      for (int i = 0; i < n; i++) ws[x[i]]++;
      for (int i = 1; i < lim; i++) ws[i] += ws[i - 1];
      for (int i = n; i--;) sa[--ws[x[y[i]]]] = y[i];
      swap(x, y), p = 1, x[sa[0]] = 0;
      for(int i = 1; i < n; i++){
        a = sa[i - 1], b = sa[i];
        x[b] = (y[a] == y[b] && y[a + j] == y[b + j]) ? p - 1 : p++;
      }
    }
    for (int i = 1; i < n; i++) rank[sa[i]] = i;
    for (int i = 0, j; i < n - 1; lcp[rank[i++]] = k)
      for (k && k--, j = sa[rank[i] - 1];
          s[i + k] == s[j + k]; k++);
  }
};
