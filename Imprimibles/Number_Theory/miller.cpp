bool check_composite(ulli n, ulli p, ulli d, int s){
  ulli x = fpow(p, d, n);
  if( x == 1 || x == n - 1 ){
    return false;
  }
  For1(it, s - 1){
    x = (__uint128_t) x * x % n;
    if( x == n - 1 ){
      return false;
    }
  }
  return true;
}

bool miller(ulli n){
  if( n < 2 ){
    return false;
  }
  int r = 0;
  ulli d = n - 1;
  while( (d & 1) == 0 ){
    d >>= 1;
    r++;
  }
  for(int p: {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}){
    if( n == p )
      return true;
    if( check_composite(n, p, d, r) )
      return false;
  }
  return true;
}
