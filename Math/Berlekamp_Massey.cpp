// out[i] = me[0]*out[i-1] + me[1]*out[i-2]+...
template <typename T> // modify for mod
vector<T> BerlekampMassey(const vector<T> &output) {
  vector<T> d(output.size() + 1), me, he;
  for (size_t f = 0, i = 1; i <= output.size(); ++i) {
    for (size_t j = 0; j < me.size(); ++j)
      d[i] += output[i - j - 2] * me[j];
    if ((d[i] -= output[i - 1]) == 0) continue;
    if (me.empty()) {
      me.resize(f = i);
      continue;
    }
    vector<T> o(i - f - 1);
    T k = -d[i] / d[f]; o.push_back(-k);
    for (T x : he) o.push_back(x * k);
    if (o.size() < me.size()) o.resize(me.size());
    for (size_t j = 0; j < me.size(); ++j) o[j] += me[j];
    if (i-f+he.size() >= me.size()) he = me, f = i;
    me = o;
  }
  return me;
}
