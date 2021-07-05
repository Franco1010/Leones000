#define mid l + (r - l) / 2
struct Node{
  lli s, mx;
  Node(lli s = 0, lli mx = 0): s(s), mx(mx) {};
  Node operator + (const Node& n) {
    return Node(s + n.s, max(mx, n.mx));
  }
};
struct ST {
	Node data;
	lli l, r;
  // ST(Node data = Node()): data(data), l(0), r(0) {}
};
ST st[MAXN];
lli curst = 1; // 0 = NULL
lli newST(){
  st[curst].data = Node();
  st[curst].l = 0;
  st[curst].r = 0;
  return curst++;
}
Node data(lli u){return u ? st[u].data : Node();}
void pull(lli u){st[u].data = data(st[u].l) + data(st[u].r);}
void update(lli u, lli l, lli r, lli kth, Node val){
  if(l == r){
    st[u].data = val;
    return;
  }
  if(kth <= mid){
    if(!st[u].l) st[u].l = newST();
    update(st[u].l, l, mid, kth, val);
  }
  else {
    if(!st[u].r) st[u].r = newST();
    update(st[u].r, mid + 1, r, kth, val);
  }
  pull(u);
}
Node query(lli u, lli l, lli r, lli ll, lli rr){
  if(!u or l > r or r < ll or l > rr) return Node();
  if(ll <= l and r <= rr) return st[u].data;
  return query(st[u].l, l, mid, ll, rr) + query(st[u].r, mid + 1, r, ll, rr);
}