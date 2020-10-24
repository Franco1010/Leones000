lli baby_step(lli a, lli b, lli p){
  a %= p;
  b %= p;
  if(b == 1) return 0;
  int cnt = 0;
  int tmp = 1;
  for(int g = gcd(a,p); g != 1; g = gcd(a,p)){
    if(b%g)return -1;
    p /= g; b /= g;
    tmp = tmp * a / g%p;
    cnt++;
    if(b == tmp)return cnt;
  }

  unordered_map<lli, int> baby;
  lli N = ceil(sqrt(p));
  lli base = b;
  fore(i,0,N){
    baby[base]=i;
    base= base * a % p;
  }
  base = powm(a,N,p);
  lli key = tmp;
  fore(i,1,N+2){
    key = base * key % p;
    if(baby.count(key))return i*N-baby[key]+cnt;
  }
  return -1;
}
