bool isp[N];
lli phi[N];

void phi_and_primes(){
  Forn(i, N){
    isp[i] = true;
    phi[i] = i;
  }
  isp[0] = isp[1] = false;
  For1(i, N - 1) if( i > 1 ){
    if( isp[i] ){
      For(j, i, N - 1, +i){
        isp[j] = (i == j);
        phi[j] /= i;
        phi[j] *= i - 1;
      }
    }
  }
}
