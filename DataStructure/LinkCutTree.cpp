struct Splay { // subtree-sum, path-max
	static Splay nil;
	Splay *ch[2], *f;
	int val, rev, size, vir, id, type;
	pii ma;
	Splay(int _val = 0, int _id = 0)
		: val(_val), rev(0), size(0), vir(0), id(_id) {
			ma = make_pair(val, id);
			f = ch[0] = ch[1] = &nil;
			type = 0;
		}
	bool isr() { //is root
		return f->ch[0] != this && f->ch[1] != this;
	}
	int dir() { return f->ch[0] == this ? 0 : 1; }
	void setCh(Splay *c, int d) {
		ch[d] = c;
		if (c != &nil) c->f = this;
		pull();
	}
	void push() {
		if (!rev) return;
		swap(ch[0], ch[1]);
		if (ch[0] != &nil) ch[0]->rev ^= 1;
		if (ch[1] != &nil) ch[1]->rev ^= 1;
		rev = 0;
	}
	void pull() {
		// take care of the nil!
		size = ch[0]->size + ch[1]->size + vir + type;
		ma = max(make_pair(val, id), max(ch[0]->ma, ch[1]->ma));
		if (ch[0] != &nil) ch[0]->f = this;
		if (ch[1] != &nil) ch[1]->f = this;
	}
} Splay::nil;
Splay *nil = &Splay::nil;
void rotate(Splay *x) {
	Splay *p = x->f;
	int d = x->dir();
	if (!p->isr()) p->f->setCh(x, p->dir());
	else x->f = p->f;
	p->setCh(x->ch[!d], d);
	x->setCh(p, !d);
	p->pull(), x->pull();
}
void splay(Splay *x) {
	vector<Splay *> splayVec;
	for (Splay *q = x;; q = q->f) {
		splayVec.pb(q);
		if (q->isr()) break;
	}
	reverse(iter(splayVec));
	for (auto it : splayVec) it->push();
	while (!x->isr()) {
		if (x->f->isr()) rotate(x);
		else if (x->dir() == x->f->dir())
			rotate(x->f), rotate(x);
		else rotate(x), rotate(x);
	}
}
Splay *access(Splay *x) {
	Splay *q = nil;
	for (; x != nil; x = x->f){
		splay(x);
		x->vir -= q->size; x->vir += x->ch[1]->size;
		x->setCh(q, 1); x->pull();
		q = x;
	}
	return q;
}
void root_path(Splay *x) { access(x), splay(x); }
void chroot(Splay *x) {
	root_path(x), x->rev ^= 1;
	x->push(), x->pull();
}
void split(Splay *x, Splay *y) {
	chroot(x), root_path(y);
}
void link(Splay *x, Splay *y) {
	chroot(x), root_path(y);
	x->f = y; y->vir += x->size;
}
void cut(Splay *x, Splay *y) {
	split(x, y);
	y->push();
	y->ch[0] = y->ch[0]->f = nil;
	y->pull();
}
Splay *get_root(Splay *x) {
	for (root_path(x); x->ch[0] != nil; x = x->ch[0])
		x->push();
	splay(x);
	return x;
}
bool conn(Splay *x, Splay *y) {
	return get_root(x) == get_root(y);
}
Splay *lca(Splay *x, Splay *y) {
	access(x), root_path(y);
	if (y->f == nil) return y;
	return y->f;
}
void change(Splay *x, int val) {
	splay(x), x->val = val, x->pull();
}
pii query(Splay *x, Splay *y) {
	split(x, y);
	return y->ma;
}
