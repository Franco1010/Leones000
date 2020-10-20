int lps[N];

void pre(string &s){ // O(N)
  lps[0] = 0;
  For1(i, sz(s) - 1){
    int j = lps[i - 1];
    while( j > 0 && s[i] != s[j] ){
      j = lps[j - 1];
    }
    lps[i] = j + (s[i] == s[j]);
  }
}

int kmp(string &s, string &t){ // O(N), how many times t occurs in s
  pre(t);
  int j = 0, tot = 0;
  Forn(i, sz(a)){
    while( j > 0 and s[i] != t[j] ){
      j = lps[j - 1];
    }
    if( s[i] == t[i] ){
      j++;
    }
    if( j == sz(t) ){
      tot++; // pos: i - sz(t);
    }
  }
  return tot;
}
