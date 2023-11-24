struct Splay { // LCT + PATH add 
  static Splay nil;
  Splay *ch[2], *f;
  int rev;
  int sz;
  ll val, sum, tag;
  Splay() : rev(0), sz(1), val(1), sum(1), tag(0) {
    f = ch[0] = ch[1] = &nil;
  }
  bool isr() { return f->ch[0] != this && f->ch[1] != this; }
  int dir() { return f->ch[0] == this ? 0 : 1; }
  void setCh(Splay *c, int d) {
    ch[d] = c;
    if (c != &nil) c->f = this;
    pull();
  }
  void push() {
    for(int i = 0; i < 2; i++){
      if(ch[i] == &nil) continue;
      if(rev) swap(ch[i]->ch[0], ch[i]->ch[1]), ch[i]->rev ^= 1;
      if(tag != 0){
        ch[i]->tag += tag;
        ch[i]->val += tag;
        ch[i]->sum += tag * ch[i]->sz;
      }
    }
    tag = 0;
    rev = 0;
  }
  void pull() {
    // take care of the nil!
    sz = 1;
    sum = val;
    for(int i = 0; i < 2; i++){
      if(ch[i] == &nil) continue;
      ch[i]->f = this;
      sz += ch[i]->sz;
      sum += ch[i]->sum;
    }
  }
  void rotate(){
    Splay *p = f;
    int d = dir();
    if (!p->isr()) p->f->setCh(this, p->dir());
    else f = p->f;
    p->setCh(ch[!d], d);
    setCh(p, !d);
    p->pull(), pull();

  }
  void update(){
    if(f != &nil) f->update();
    push();
  }
  void splay(){
    update();
    for(Splay* fa; fa = f, !isr(); rotate())
      if(!fa->isr()) (fa->dir() == dir() ? fa : this)->rotate();
  }
  Splay *access(Splay* q = &nil){
    splay();
    setCh(q, 1);
    pull();
    if (f != &nil) return f->access(this);
    else return q;
  }
  void root_path(){access(), splay();}
  void chroot() {root_path(), swap(ch[0], ch[1]), rev = 1, push(), pull();}
  void split(Splay* y){chroot(), y->root_path();}
  void link(Splay* y){root_path(), y->chroot(), setCh(y, 1);}
  void cut(Splay* y) {split(y), y->push(), y->ch[0] = y->ch[0]->f = &nil;}
  Splay *get_root(){
    root_path();
    auto q = this;
    for(; q->ch[0] != &nil; q = q->ch[0]) q->push();
    return q;
  }
  Splay *lca(Splay* y){
    access(), y->root_path();
    return y->f == &nil ? &nil : y->f;
  }
  bool conn(Splay* y){return get_root() == y->get_root();}
} Splay::nil;
