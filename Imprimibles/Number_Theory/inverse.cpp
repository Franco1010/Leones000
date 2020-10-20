void do_inverse(){ // mod < 1e7
  inv[0] = inv[1] = 1ll;
  For(i, 2, mod - 1, +1){
    inv[i] = (inv[mod % i] * (mod - (mod / i)) % mod;
  }
}
----------------------------------------------------------------
void factorials(){ // n! y inv(n!)
  fac[0] = 1ll;
  For1(i, N - 1){
    fac[i] = 1ll * fac[i - 1] * i % mod;
  }
  ifac[N - 1] = fpow(fac[N - 1], mod - 2);
  Rof(i, N - 2, 0, -1){
    ifac[i] = 1ll * ifac[i + 1] * (i + 1) % mod;
  }
}
----------------------------------------------------------------
void magic(){ // p ^ k y inv(p ^ k)
  pw[0] = 1LL;
  For1(i, N - 1){
    pw[i] = 1LL * pw[i - 1] * P % mod;
  }
  ipw[N - 1] = fpow(pw[N - 1], mod - 2);
  Rof(i, N - 2, 0, -1){
    ipw[i] = 1LL * ipw[i + 1] * P % mod;
  }
}
