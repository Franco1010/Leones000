struct PersistentSegmentTree{
  struct Node{
    int cnt = 0;
    Node *l, *r;
    Node(int val) : l(nullptr), r(nullptr), cnt(val){}
    Node(Node *l, Node *r) : l(l), r(r), cnt(0){
      if(l) cnt += l->cnt;
      if(r) cnt += r->cnt;
    }
  };

  vector<Node*> pst;
  int n;

  PersistentSegmentTree(int _n){
    n = _n;
    pst.pb(build(1, n));
  }

  Node* build(int l, int r){ // O(N * logN)
    if(l == r) return new Node(0);
    int mid = (l + r) >> 1;
    return new Node(build(l, mid), build(mid+1, r));
  }

  Node* update(Node *u, int l, int r, int pos){ // O(logN)
    if(l == r){
      return new Node(u->cnt + 1);
    }
    int mid = (l + r) >> 1;
    if(pos <= mid) return new Node(update(u->l, l, mid, pos), u->r);
    else return new Node(u->l, update(u->r, mid+1, r, pos));
  }

  int query(Node *sl, Node *sr, int l, int r, int kth){ // O(logN)
    if(l == r) return l;
    int dif = sr->l->cnt - sl->l->cnt;
    int mid = (l + r) >> 1;
    if(dif >= kth) return query(sl->l, sr->l, l, mid, kth);
    else return query(sl->r, sr->r, mid+1, r, kth - dif);
  }

  void update(int version, int pos){
    pst.pb(update(pst[version], 1, n, pos));
  }

  int query(int l, int r, int k){
    return query(pst[l-1], pst[r], 1, n, k);
  }
};
