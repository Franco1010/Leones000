struct dsu{
  vector<int> pr;

  dsu(int nn = 0){ // O(N)
    pr.resize(nn + 5);
    iota(all(pr), 0);
  }

  int find(int u){ // O(1)
    return pr[u] == u ? u: pr[u] = find(pr[u]);
  }

  bool unite(int u, int v){ // O(1)
    u = find(u), v = find(v);
    if( u != v ){
      pr[v] = u;
      return true;
    }
    return false;
  }
};
