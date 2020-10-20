enum {prefix = 0, suffix};
lli h[2][N];
string s;
int n;

lli prefix_query(int l, int r){
  return (h[prefix][r] - h[prefix][l - 1] + mod) % mod * ipw[l - 1] % mod;
}

lli suffix_query(int l, int r){
  return (h[suffix][l] - h[suffix][r + 1] + mod) % mod * ipw[n - r] % mod;
}

bool palindrome(int l, int r){
  l++, r++;
  return prefix_query(l, r) == suffix_query(l, r);
}

void pre(string &s){
  n = sz(s);
  s = "$" + s;
  h[prefix][0] = 0;
  For1(i, n){
    h[prefix][i] = (h[prefix][i - 1] + 1LL * (s[i] - 'a' + 1) * pw[i - 1]) % mod;
  }
  h[suffix][n + 1] = 0;
  Rof(i, n, 1, -1){
    h[suffix][i] = (h[suffix][i + 1] + 1LL * (s[i] - 'a' + 1) * pw[n - i]) % mod;
  }
}
