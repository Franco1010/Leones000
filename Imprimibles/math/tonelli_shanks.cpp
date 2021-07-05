mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
long long rnd(long long a, long long b){return uniform_int_distribution<long long>(a, b)(rng);}
long long powm(long long a, long long b, long long mod){
	long long res =1;
	while(b){ if(b&1) res = (res * a) % mod; a = (a*a) % mod; b/=2; }
	return res;
}
long long legendre(long long a, long long p){
  if(a%p==0)return 0; if(p==2)return 1;
  return powm(a,(p-1)/2,p);
}
long long tonelli_shanks(long long n, long long p){	// sqrt(n) mod p (p must be a prime)
  assert(legendre(n,p)==1); if(p==2)return 1;
  long long s=__builtin_ctzll(p-1), q=(p-1LL)>>s, z=rnd(1,p-1);
  if(s==1)return powm(n,(p+1)/4LL,p);
  while(legendre(z,p)!=p-1)z=rnd(1,p-1);
  long long c=powm(z,q,p), r=powm(n,(q+1)/2,p), t=powm(n,q,p), m=s;
  while(t!=1){
    long long i=1, ts=(t*t)%p;
    while(ts!=1)i++,ts=(ts*ts)%p;
    long long b=c;
    for(int tt = 0; tt < m - i - 1; ++tt) b=(b*b)%p;
    r=r*b%p;c=b*b%p;t=t*c%p;m=i;
  }
  return r;
}