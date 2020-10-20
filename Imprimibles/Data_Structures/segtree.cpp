struct segtree{
  #define mid (l + r) / 2
  #define left(u) (u + 1)
  #define right(u) (u + ((mid - l + 1) << 1))

  struct node{
    lli sum = 0;
    int mx = -1;
  };

  vector<node> st;
  node z;
  int n;

  friend node operator + (const node a, const node b){
    node c;
    c.sum = a.sum + b.sum;
    c.mx = max(a.mx, b.mx);
    return c;
  }

  void build(int u, int l, int r){ // O(N * logN)
    if( l == r ){
      st[u] = {};
      return;
    }
    build(left(u), l, mid);
    build(right(u), mid + 1, r);
    st[u] = st[left(u)] + st[right(u)];
  }

  segtree(int n1 = 1){
    n = n1;
    st.resize(2 * n); // wow :O!
    build(0, 1, n);
  }

  void update(int u, int l, int r, int kth, int v){ // O(logN)
    if( l == r ){
      st[u] = {};
      return;
    }
    if( kth <= mid ){
      update(left(u), l, mid, kth, v);
    }else{
      update(right(u), mid + 1, r, kth, v);
    }
    st[u] = st[left(u)] + st[right(u)];
  }

  node query(int u, int l, int r, int ll, int rr){ // O(logN)
    if( r < ll || rr < l || r < l ){
      return z;
    }
    if( ll <= l && r <= rr ){
      return st[u];
    }
    return query(left(u), l, mid, ll, rr) +
           query(right(u), mid + 1, r, ll, rr);
  }
  #undef mid
};
