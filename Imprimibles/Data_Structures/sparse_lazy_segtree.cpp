#define mid l + (r - l) / 2
struct Node{
  lli s, z;
  Node(lli s = 0, lli z = 0): s(s), z(z) {};
  Node operator + (const Node& n) {
    return Node(s + n.s);
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
void push(lli u, lli l, lli r){
  if(!st[u].l) st[u].l = newST();
  if(!st[u].r) st[u].r = newST();
  if(st[u].data.z){
    if(l < r){
      st[st[u].l].data.z += st[u].data.z;
      st[st[u].r].data.z += st[u].data.z;
    }
    st[u].data.s += (r - l + 1ll) * st[u].data.z;
    st[u].data.z = 0;
  }
}
void update(lli u, lli l, lli r, lli ll, lli rr, lli val){
  push(u, l, r);
  if(l > r or r < ll or l > rr or ll > rr) return;
  if(ll <= l and r <= rr){
    st[u].data.z += val;
    push(u, l, r);
    return;
  }
  update(st[u].l, l, mid, ll, rr, val);
  update(st[u].r, mid + 1, r, ll, rr, val);
  pull(u);
}
Node query(lli u, lli l, lli r, lli ll, lli rr){
  push(u, l, r);
  if(!u or l > r or r < ll or l > rr) return Node();
  if(ll <= l and r <= rr) return st[u].data;
  return query(st[u].l, l, mid, ll, rr) + query(st[u].r, mid + 1, r, ll, rr);
}
