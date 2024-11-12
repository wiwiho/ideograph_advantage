mt19937 rng(880301);
// == PART HASH ==
struct node {
  ll data; int sz;
  node *l, *r;
  node(ll k = 0) : data(k), sz(1), l(0), r(0) {}
  void up() {
    sz = 1;
    if (l) sz += l->sz;
    if (r) sz += r->sz;
  }
  void down() {}
};
node pool[1000010]; int pool_cnt = 0;
node *newnode(ll k){ return &(pool[pool_cnt++] = node(k)); }
int sz(node *a) { return a ? a->sz : 0; }
node *merge(node *a, node *b) {
  if (!a || !b) return a ? a : b;
  if (int(rng() % (sz(a) + sz(b))) < sz(a))
    return a->down(), a->r = merge(a->r, b), a->up(),
           a;
  return b->down(), b->l = merge(a, b->l), b->up(), b;
}
// a: key <= k, b: key > k
void split(node *o, node *&a, node *&b, ll k) {
  if (!o) return a = b = 0, void();
  o->down();
  if (o->data <= k)
    a = o, split(o->r, a->r, b, k), a->up();
  else b = o, split(o->l, a, b->l, k), b->up();
}
// a: size k, b: size n - k
void split2(node *o, node *&a, node *&b, int k) {
  if (sz(o) <= k) return a = o, b = 0, void();
  o->down();
  if (sz(o->l) + 1 <= k)
    a = o, split2(o->r, a->r, b, k - sz(o->l) - 1);
  else b = o, split2(o->l, a, b->l, k);
  o->up();
}
// == PART HASH ==
node *kth(node *o, ll k) { // 1-based
  if (k <= sz(o->l)) return kth(o->l, k);
  if (k == sz(o->l) + 1) return o;
  return kth(o->r, k - sz(o->l) - 1);
}
int Rank(node *o, ll key) { // num of key < key
  if (!o) return 0;
  if (o->data < key)
    return sz(o->l) + 1 + Rank(o->r, key);
  else return Rank(o->l, key);
}
bool erase(node *&o, ll k) {
  if (!o) return 0;
  if (o->data == k) {
    node *t = o;
    o->down(), o = merge(o->l, o->r);
    return 1;
  }
  node *&t = k < o->data ? o->l : o->r;
  return erase(t, k) ? o->up(), 1 : 0;
}
void insert(node *&o, ll k) {
  node *a, *b;
  split(o, a, b, k),
    o = merge(a, merge(new node(k), b));
}
tuple<node*, node*, node*> interval(node *&o, int l, int r) { // 1-based
  node *a, *b, *c; // b: [l, r]
  split2(o, a, b, l - 1), split2(b, b, c, r - l + 1);
  return make_tuple(a, b, c);
}
