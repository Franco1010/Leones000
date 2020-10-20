struct line{
  // with eq. y = mx + c
  mutable lli m, c, p;
  bool operator < (const line &l) const{ return m < l.m; }
  bool operator < (const lli &x) const{ return p < x; }

  lli eval(lli x){
    return m * x + c;
  }
};

struct convex_hull: multiset<line, less<>> {
  // for doubles, use inf = 1/.0, div(a,b) = a/b
  lli div(lli a, lli b){
    return a / b - ((a ^ b) < 0 && a % b);
  }

  bool isect(iterator x, iterator y){
    if( y == end() ){
      x->p = inf;
      return false;
    }
    if( x->m == y->m ){
      x->p = (x->c > y->c ? inf: -inf);
    }else{
      x->p = div(y->c - x->c, x->m - y->m);
    }
    return x->p >= y->p;
  }

  void add(lli m, lli c){
    auto z = insert({m, c, 0}), y = z++, x = y;
    while( isect(y, z) ){
      z = erase(z);
    }
    if( x != begin() && isect(--x, y) ){
      isect(x, y = erase(y));
    }
    while( (y = x) != begin() && (--x)->p >= y->p ){
      isect(x, erase(y));
    }
  }

  // solve dp[i] = max{j < i; dp[j] + b[j] * a[i]}
  // (b[j] >= b[j + 1]) or (a[i] <= a[i + 1])
  lli query(lli x){
    auto l = *lower(x);
    return l.eval(x);
  }
};
