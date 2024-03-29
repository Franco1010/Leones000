lli calc(int l, int r){ // O(N ^ 3) // TODO: agregar version iterativa en O(N ^ 2)
  if( l >= r ){
    return 0ll;
  }
  lli &ans = dp[l][r];
  if( ans == -1 ){
    ans = inf;
    For(k, l, r, +1){
      ans = min(ans, calc(l, k) + calc(k + 1, r) + inc()));
    }
  }
  return ans;
}
