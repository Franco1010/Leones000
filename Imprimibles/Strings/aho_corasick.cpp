struct AhoCorasick{
  struct Vertex {
    map<char, int> next, go;
    int p, link;
    char pch;
    vector<int> leaf;
    Vertex(int p=-1, char pch=-1): p(p), pch(pch), link(-1){}
  };
  vector<Vertex> t;
  const Vertex &operator[](const int &i) const{return t[i];}
  AhoCorasick(){
    t.clear(); t.pb(Vertex());
  }
  void addString(string s, int id){ // O(N)
    int v = 0;
    for(char c : s){
      if(!t[v].next.count(c)){
        t[v].next[c] = t.size();
        t.pb(Vertex(v, c));
      }
      v = t[v].next[c];
    }
    t[v].leaf.pb(id);
  }
  int getLink(int v){ // O(1)
    if(t[v].link < 0){
      if(!v or !t[v].p) t[v].link = 0;
      else t[v].link = go(getLink(t[v].p), t[v].pch);
    }
    return t[v].link;
  }
  int go(int v, char c){ // O(logN)
    if(!t[v].go.count(c)){
      if(t[v].next.count(c)) t[v].go[c] = t[v].next[c];
      else t[v].go[c] = v == 0 ? 0 : go(getLink(v), c);
    }
    return t[v].go[c];
  }
};
