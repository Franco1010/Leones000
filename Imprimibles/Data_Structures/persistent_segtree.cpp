Node pst[N];
//La memoria se debe calcular de acuerdo al problema
//Depende directamente del tipo de solucion que se este implementando
struct PersistentSegmentTree{
  #define mid (l + r)/2
  int n, nextNode;
  vector<int> root;

  PersistentSegmentTree(int _n){
    n = _n;
    nextNode = 0;
    pst[nextNode++] = Node(0);
    root.pb(0);
    build(root[0], 1, n);
  }

  void build(int u, int l, int r){// O(N * logN)
    if(l == r){
      return;
    }
    pst[u].l = nextNode++;
    pst[u].r = nextNode++;
    build(pst[u].l, l, mid);
    build(pst[u].r, mid + 1, r);
  }

  int update(int u, int l, int r, int pos){// O(logN)
    int npos = nextNode++;
    pst[npos] = pst[u];
    if(l == r){
      pst[npos].cnt++;
      pst[npos].l = pst[npos].r = -1;
      return npos;
    }
    if(pos <= mid) pst[npos].l = update(pst[u].l, l, mid, pos);
    else pst[npos].r = update(pst[u].r, mid+1, r, pos);
    pst[npos].cnt = pst[pst[npos].l] + pst[pst[npos].r];
    return npos;
  }

  int query(int sl, int sr, int l, int r, int kth){// O(logN)
    if(l == r) return l;
    int dif = pst[pst[sr].l].cnt - pst[pst[sl].l].cnt;
    if(dif >= kth) return query(pst[sl].l, pst[sr].l, l, mid, kth);
    else return query(pst[sl].r, pst[sr].r, mid + 1, r, kth - dif);
  }

  void update(int version, int pos){
    root.pb(update(root[version], 1, n, pos));
  }

  int query(int l, int r, int k){
    return query(root[l-1], root[r], 1, n, k);
  }
  #undef mid
};
