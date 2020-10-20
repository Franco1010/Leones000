lli fpow(lli x, lli y){ // O(logY)
  lli r = 1;
  while( y > 0 ){
    if( y & 1 ) r = r * x;
    x = x * x;
    y >>= 1;
  }
  return r;
}
