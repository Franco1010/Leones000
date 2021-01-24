#define mid l + (r - l) / 2
typedef struct ST *PST;
struct Node{
  lli s, z;
  Node(lli s = 0, lli z = 0): s(s), z(z) {};
  Node operator + (const Node& n) {
    return Node(s + n.s);
  }
};
struct ST {
	Node data;
	PST l, r;
  ST(Node data = Node()): data(data), l(0), r(0) {}
};
Node data(PST& u){return u ? u->data : Node();}
void pull(PST& u){u->data = data(u->l) + data(u->r);}
void push(PST& u, lli l, lli r){
  if(!u->l) u->l = new ST();
  if(!u->r) u->r = new ST();
  if(u->data.z){
    if(l < r){
      u->l->data.z += u->data.z;
      u->r->data.z += u->data.z;
    }
    u->data.s += (r - l + 1ll) * u->data.z;
    u->data.z = 0;
  }
}
void update(PST& u, lli l, lli r, lli ll, lli rr, lli val){
  push(u, l, r);
  if(l > r or r < ll or l > rr or ll > rr) return;
  if(ll <= l and r <= rr){
    u->data.z += val;
    push(u, l, r);
    return;
  }
  update(u->l, l, mid, ll, rr, val);
  update(u->r, mid + 1, r, ll, rr, val);
  pull(u);
}
Node query(PST& u, lli l, lli r, lli ll, lli rr){
  push(u, l, r);
  if(!u or l > r or r < ll or l > rr) return Node();
  if(ll <= l and r <= rr) return u->data;
  return query(u->l, l, mid, ll, rr) + query(u->r, mid + 1, r, ll, rr);
}
