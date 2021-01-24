#define mid l + (r - l) / 2
typedef struct ST *PST;
struct Node{
  lli s, mx;
  Node(lli s = 0, lli mx = 0): s(s), mx(mx) {};
  Node operator + (const Node& n) {
    return Node(s + n.s, max(mx, n.mx));
  }
};
struct ST {
	Node data;
	PST l, r;
  ST(Node data = Node()): data(data), l(0), r(0) {}
};
Node data(PST& u){return u ? u->data : Node();}
void pull(PST& u){u->data = data(u->l) + data(u->r);}
void update(PST& u, lli l, lli r, lli kth, Node val){
  if(l == r){
    u->data = val;
    return;
  }
  if(kth <= mid){
    if(!u->l) u->l = new ST();
    update(u->l, l, mid, kth, val);
  }
  else {
    if(!u->r) u->r = new ST();
    update(u->r, mid + 1, r, kth, val);
  }
  pull(u);
}
Node query(PST& u, lli l, lli r, lli ll, lli rr){
  if(!u or l > r or r < ll or l > rr) return Node();
  if(ll <= l and r <= rr) return u->data;
  return query(u->l, l, mid, ll, rr) + query(u->r, mid + 1, r, ll, rr);
}
