const int N = 1005;
lli choose[N][N];

void pascal(int N){
  Forn(n, N - 1){
    choose[n][0] = choose[n][n] = 1;
    For1(k, n - 1){
      choose[n][k] = choose[n - 1][k - 1] + choose[n - 1][k];
    }
  }
}
