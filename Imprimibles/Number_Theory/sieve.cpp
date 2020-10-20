int p[N >> 6];
#define isp(x) !(p[x >> 6] & (1 << ((x >> 1) % 32)))
#define add(x) p[x >> 6] |= (1 << ((x >> 1) % 32))

bool prime(lli x){
  return x == 2 || (x % 2 && isp(x) && x > 1);
}

void sieve(){
  for(lli i = 3; 1LL * i * i < N; i += 2) if( isp(i) ){
    for(lli j = 1LL * i * i; j < N; j += (i << 1)){
      add(j);
    }
  }
}
----------------------------------------------------------------
void factorize_sieve(){ // O(N)
  iota(p, p + N, 0);
  For(i, 2, N - 1, +1) if( p[i] == i ){
    For(j, i, N - 1, +i) if( p[j] == j ){
      p[j] = i;
    }
  }
}
