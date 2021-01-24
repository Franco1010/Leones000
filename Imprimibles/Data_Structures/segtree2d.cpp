const lli INF = 1E18;
struct Segtree{
  #define midx (lx + rx) / 2
  #define midy (ly + ry) / 2
  #define leftx(u) (u + 1)
  #define lefty(u) (u + 1)
  #define rightx(u) (u + ((midx - lx + 1) << 1))
  #define righty(u) (u + ((midy - ly + 1) << 1))
  struct Node{
    lli s, mx;
    Node(lli s = 0, lli mx = -INF): s(s), mx(mx) {}
    Node operator + (const Node& n){
      return Node(s + n.s, max(mx, n.mx));
    }
  };
  vector<vector<Node>> st;
  int n;
  Segtree(int n): n(n), st(2 * n, vector<Node>(2*n)) {}
  void updatey(int ux, int lx, int rx, int uy, int ly, int ry, int x, int y, lli val){
    if(ly == ry){
      if(lx == rx){
        st[ux][uy].s = val;
        st[ux][uy].mx = val;
        return;
      }
      st[ux][uy] = st[leftx(ux)][uy] + st[rightx(ux)][uy];
      return;
    }
    if(y <= midy) updatey(ux, lx, rx, lefty(uy), ly, midy, x, y, val);
    else updatey(ux, lx, rx, righty(uy), midy + 1, ry, x, y, val);
    st[ux][uy] = st[ux][lefty(uy)] + st[ux][righty(uy)];
  }
  void updatex(int ux, int lx, int rx, int x, int y, lli val){
    if(lx == rx){
      updatey(ux, lx, rx, 0, 0, n - 1, x, y, val);
      return;
    }
    if(x <= midx) updatex(leftx(ux), lx, midx, x, y, val);
    else updatex(rightx(ux), midx + 1, rx, x, y, val);
    updatey(ux, lx, rx, 0, 0, n - 1, x, y, val);
  }
  Node queryy(int ux, int uy, int ly, int ry, int lly, int rry){
    if(ly > ry or ry < lly or ly > rry) return Node();
    if(lly <= ly and ry <= rry) return st[ux][uy];
    return queryy(ux, lefty(uy), ly, midy, lly , rry) +
            queryy(ux, righty(uy), midy + 1, ry, lly, rry);
  }
  Node queryx(int ux, int lx, int rx, int llx, int rrx, int lly, int rry){
    if(lx > rx or rx < llx or lx > rrx) return Node();
    if(llx <= lx and rx <= rrx) return queryy(ux, 0, 0, n - 1, lly, rry);
    return queryx(leftx(ux), lx, midx, llx, rrx, lly, rry) +
            queryx(rightx(ux), midx + 1, rx, llx, rrx, lly, rry);
  }
  void printy(int ux, int uy, int ly, int ry){
    if(ly == ry){
      if(st[ux][uy].mx == -INF) cout << "∆" << ' ';
      else cout << st[ux][uy].mx << ' ';
      return;
    }
    printy(ux, lefty(uy), ly, midy);
    printy(ux, righty(uy), midy + 1, ry);
  }
  void printx(int ux, int lx, int rx){
    if(lx == rx){
      printy(ux, 0, 0, n - 1);
      cout << ENDL;
      return;
    }
    printx(leftx(ux), lx, midx);
    printx(rightx(ux), midx + 1, rx);
  }
};
