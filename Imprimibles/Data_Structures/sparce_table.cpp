const int N = 1e5 + 5;
const int LogN = 17;
lli sp[LogN][N], lg[N], a[N];
int n;

void process_all_logs(){
  lg[0] = -1;
  For1(i, N - 1){
    lg[i] = lg[i >> 1] + 1;
  }
}

template <class T>
T query(int l, int r){ // O(logN) = op{+, *, ^, |, &}
  T ans = {};
  Rof(k, LogN - 1, 0, -1){
    if( l + (1 << k) - 1 <= r ){
      ans += sp[k][l]);
      l += (1 << k);
    }
  }
  return ans;
}

template <class T>
T query(int l, int r){ // O(1) = op{min, max, gcd}
  int k = lg[r - l + 1];
  return min(sp[k][l], sp[k][r - (1 << k) + 1]);
}

void do_sparce(){ // O(N * logN)
  Forn(i, n){
    sp[0][i] = a[i];
  }
  For1(k, LogN - 1){
    Forn(i, n - (1 << k) + 1){
      sp[k][i] = sp[k - 1][i] + sp[k - 1][i + (1 << (k - 1))];
    }
  }
}
