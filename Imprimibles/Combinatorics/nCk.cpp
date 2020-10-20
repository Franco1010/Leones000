lli choose(lli n, lli k){
  return 1ll * fac[n] * ifac[k] % mod * ifac[n - k] % mod;
}

lli choose(lli n, lli k){
  double r = 1;
  For1(i, k) r = r * (n - k + i) / i;
  return lli(r + 0.01);
}
