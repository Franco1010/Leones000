#define mid (l + r) / 2
typedef struct Node *pNode;
struct Node {
	lli s;
	pNode l, r;
  Node(lli s = 0): s(s), l(0), r(0) {}
};
lli s(pNode u){return u ? u->s : 0;}
void pull(pNode& u, pNode l, pNode r){
  u->s = s(l) + s(r);
}
void update(pNode& u, int l, int r, int kth, lli val){
  if(l == r){
    u->s = val;
    return;
  }
  if(kth <= mid){
    if(!u->l) u->l = new Node();
    update(u->l, l, mid, kth, val);
  }
  else {
    if(!u->r) u->r = new Node();
    update(u->r, mid + 1, r, kth, val);
  }
  pull(u, u->l, u->r);
}
pNode query(pNode u, int l, int r, int ll, int rr){
  if(!u or l > r or r < ll or l > rr) return new Node();
  if(ll <= l and r <= rr) return u;
  pNode res = new Node();
  pull(res, query(u->l, l, mid, ll, rr), query(u->r, mid + 1, r, ll, rr));
  return res;
}
