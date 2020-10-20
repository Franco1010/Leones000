struct LazySegTree{
  #define mid (l + r)/2
  #define left(u) (u + 1)
  #define right(u) (u + ((mid - l + 1) << 1))

  struct Node{
    lli s, lazy;
    Node(lli s = 0, int lazy = 0): s(s), lazy(lazy) {}
    Node operator+(const Node &n) const{
      return Node(s + n.s, 0);
    }
  };

  int n;
  Node z;
  vector<Node> st;

  LazySegTree(int n): n(n){
    st.resize(2*n);
  }

  void push(int u, int l, int r){
    if(st[u].lazy){
      st[left(u)].s += st[u].lazy;
      st[left(u)].lazy += st[u].lazy;
      st[right(u)].s += st[u].lazy;
      st[right(u)].lazy += st[u].lazy;
      st[u].lazy = 0;
    }
  }

  void update(int u, int l, int r, int ll, int rr, lli x){ // O(logN)
    if(r < ll or l > rr) return;
    if(ll <= l and r <= rr){
      st[u].s += x;
      st[u].lazy += x;
      return;
    }
    push(u, l, r);
    update(left(u), l, mid, ll, rr, x);
    update(right(u), mid + 1, r, ll, rr, x);
    st[u] = st[left(u)] + st[right(u)];
  }

  lli query(int u, int l, int r, int p){ // O(logN)
    if(l == r) return st[u].s;
    push(u, l, r);
    if(mid >= p) return query(left(u), l, mid, p);
    else return query(right(u), mid + 1, r, p);
  }
};
