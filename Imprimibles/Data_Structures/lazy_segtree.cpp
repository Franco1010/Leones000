struct Segtree{ // TODO: poder Monoid y F = function<Monoid(Monoid, Monoid)>;
  #define mid (l + r) / 2
  #define left(u) (u + 1)
  #define right(u) (u + ((mid - l + 1) << 1))
  struct Node{
    lli s, mx, lazy;
    Node(lli s = 0, lli lazy = 0): s(s), mx(mx), lazy(lazy) {}
    Node operator + (const Node &n){
      return Node(s + n.s);
    }
  };
  vector<Node> st;
  Segtree(int n): st(2 * n) {}
  void push(int u, int l, int r){
    if(st[u].lazy){
      st[left(u)].s += st[u].lazy;
      st[left(u)].lazy += st[u].lazy;
      st[right(u)].s += st[u].lazy;
      st[right(u)].lazy += st[u].lazy;
      st[u].lazy = 0;
    }
  }
  void update(int u, int l, int r, int ll, int rr, lli val){ // O(logN)
    if(l > r or r < ll or l > rr) return;
    if(ll <= l and r <= rr){
      st[u].s += val;
      st[u].lazy += val;
      return;
    }
    push(u, l, r);
    update(left(u), l, mid, ll, rr, val);
    update(right(u), mid + 1, r, ll, rr, val);
    st[u] = st[left(u)] + st[right(u)];
  }
  Node query(int u, int l, int r, int ll, int rr){ // O(logN)
    if(l > r or r < ll or l > rr) return Node();
    if(ll <= l and r <= rr) return st[u];
    push(u, l, r);
    return query(left(u), l, mid, ll, rr) + query(right(u), mid + 1, r, ll, rr);
  }
};
