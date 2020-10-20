struct suffix_automaton{
  vector< map<char, int> > trie;
  vector<int> link;
  vector<int> len;
  int last;

  suffix_automaton(){
    last = new_node();
  }

  int new_node(){
    trie.pb({});
    link.pb(-1);
    len.pb(0);
    return sz(trie) - 1;
  }

  void extend(char c){
    int u = new_node();
    len[u] = len[last] + 1;
    int p = last;
    while( p != -1 && !trie[p].count(c) ){
      trie[p][c] = u;
      p = link[p];
    }
    if( p == -1 ){
      link[u] = 0;
    }else{
      int q = trie[p][c];
      if( len[p] + 1 == len[q] ){
        link[u] = q;
      }else{
        int clone = new_node();
        len[clone] = len[p] + 1;
        trie[clone] = trie[q];
        link[clone] = link[q];
        while( p != -1 && trie[p][c] == q ){
          trie[p][c] = clone;
          p = link[p];
        }
        link[q] = link[u] = clone;
      }
    }
    last = u;
  }
----------------------------------------------------------
  bool find(string &s, int u){
    for(char c: s){
      if( !trie[u].count(c) ){
        return false;
      }
      u = trie[u][c];
    }
    return true;
  }
----------------------------------------------------------
  int longest_common_substring(string &s, int u = 0){
    int mx = 0, cur_len = 0;
    for(char c: s){
      while( u && !trie[u].count(c) ){
        u = link[u];
        cur_len = len[u];
      }
      if( trie[u][c] ){
        u = trie[u][c];
        cur_len++;
      }
      mx = max(mx, cur_len);
    }
    return mx;
  }
----------------------------------------------------------
  // different substrings
  // dp[u] = trie[u].empty() ? 1: 1 + all(trie[u])
  string lexicographically_kth_substring(lli kth, int u = 0){
    string s = "";
    while( kth > 0 ){
      for(auto &[c, v]: trie[u]){
        if( kth <= dp[v] ){
          s.pb(c);
          kth--;
          u = v;
          break;
        }
        kth -= dp[v];
      }
    }
    return s;
  }
----------------------------------------------------------
  // occurs[u] = 1, occurs[clone] = 0
  void all_occurrences_in(string &s){
    vector<int> lens;
    Forn(u, sz(trie)){
      lens.pb(u);
    }
    sort(all(lens), [=](int u, int v){
      return len[u] > len[v];
    });
    for(int u: lens){
      occurs[link[u]] += occurs[u];
    }
  }

  int how_many_times(string &s, int u = 0){
    for(char c: s){
      if( !trie[u][c] ){
        return 0;
      }
      u = trie[u][c];
    }
    return occurs[u];
  }
};
