const int N = 1e5 + 5;
lli sq[320];
int a[N], who[N];
int block; // sqrt(N)
int n;

template <class T>
T query(int l, int r){ // O(sqrtN)
  T ans = {};
  while( l <= r ){
    if( l % block == 0 && l + block - 1 <= r ){
      ans += sq[who[l]];
      l += block;
    }else{
      ans += a[l++];
    }
  }
  return ans;
}

void do_sqrt_descomposition(){ // O(N)
  block = sqrt(n);
  Forn(i, n){
    who[i] = i / block;
    sq[who[i]] += a[i];
  }
}
