lli factmod(lli n, lli p){
  lli r = 1;
  for(; n > 1; n /= p){
    r = (r * ((n / p) % 2 ? p - 1: 1)) % p;
    For(i, 2, n % p, +1) r = r * i % p;
  }
  return r % p;
}
