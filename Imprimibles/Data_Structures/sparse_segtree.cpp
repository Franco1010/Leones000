#define mid l + (r - l) / 2
typedef struct Node *pNode;
struct Node {
	lli s, mx;
	pNode l, r;
  Node(lli s = 0, lli mx = -INF): s(s), mx(mx), l(0), r(0) {}
};
lli s(pNode u){return u ? u->s : 0;}
lli mx(pNode u){return u ? u->mx : -INF;}
void pull(pNode& u, pNode l, pNode r){
  u->s = s(l) + s(r);
  u->mx = max(mx(l), mx(r));
}
void update(pNode& u, lli l, lli r, lli kth, lli val){
  if(l == r){
    u->s = val;
    u->mx = val;
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
pNode query(pNode u, lli l, lli r, lli ll, lli rr){
  if(!u or l > r or r < ll or l > rr) return new Node();
  if(ll <= l and r <= rr) return u;
  pNode res = new Node();
  pull(res, query(u->l, l, mid, ll, rr), query(u->r, mid + 1, r, ll, rr));
  return res;
}
