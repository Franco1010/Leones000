int L[MAXN * 2 + 5];
string manacher(string s) {
  int N = s.len() * 2 + 1;
  L[0] = 0;
  L[1] = 1;
  int C = 1;
  int R = 2;
  int iMirror;
  int maxLPSLength = 0;
  int maxLPSCenterPosition = 0;
  int diff = -1;
  FOR(i, 2, N) {
    iMirror  = 2*C-i;
    L[i] = 0;
    diff = R - i;
    if(diff > 0) L[i] = min(L[iMirror], diff);
    while ( ((i + L[i]) < N && (i - L[i]) > 0) &&
      ( ((i + L[i] + 1) % 2 == 0) ||
      (s[(i + L[i] + 1)/2] == s[(i - L[i] - 1)/2] )))
      L[i]++;

    if(L[i] > maxLPSLength) {
      maxLPSLength = L[i];
      maxLPSCenterPosition = i;
    }
    if (i + L[i] > R)  {
      C = i;
      R = i + L[i];
    }
  }
  int ini = (maxLPSCenterPosition - maxLPSLength)/2;
  int fin = ini + maxLPSLength;
  return s.substr(ini, fin-ini);
}
