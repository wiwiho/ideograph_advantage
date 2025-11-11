// out[i] = me[0]*out[i-1] + me[1]*out[i-2]+...
vector<int> BerlekampMassey(const vector<int> &output) {
  vector<int> d(output.size() + 1), me, he;
  for (int f = 0, i = 1; i <= output.size(); ++i) {
    for (int j = 0; j < me.size(); ++j)
      add(d[i], mul(output[i - j - 2], me[j]));
	add(d[i], -output[i-1]);
    if (d[i] == 0) continue;
    if (me.empty()) {
      me.resize(f = i);
      continue;
    }
    vector<int> o(i - f - 1);
	int k = mul(d[i], -inv(d[f]));
	o.push_back(-k);
    for (auto x : he) o.push_back(mul(x, k));
    if (o.size() < me.size()) o.resize(me.size());
    for (size_t j = 0; j < me.size(); ++j) add(o[j], me[j]);
    if (i-f+he.size() >= me.size()) he = me, f = i;
    me = o;
  }
  for(auto &h: me) add(h, mod);
  return me;
}
