struct prefix_tree{
  vector< map<char, int> > trie
  vector<bool> isw;

  prefix_tree(){
    new_node();
  }

  int new_node(){
    trie.pb(map<char, int>());
    isw.pb(false);
    return sz(trie) - 1;
  }

  void insert(string &s, int u = 0){
    for(char c: s){
      if( !trie[u][c] ){
        trie[u][c] = new_node();
      }
      u = trie[u][c];
    }
    isw[u] = true;
  }

  bool find(string &s, int u = 0){
    for(char c: s){
      if( !trie[u][c] ){
        return false;
      }
      u = trie[u][c];
    }
    return isw[u];
  }
};
