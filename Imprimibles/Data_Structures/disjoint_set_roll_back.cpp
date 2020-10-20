struct dsu{
  vector<int> pr, tot;
  stack<ii> what;

  dsu(int nn = 0){ // O(N)
    pr.resize(nn + 5);
    iota(all(pr), 0);
    tot.resize(nn + 5, 1);
  }

  int find(int u){ // O(logN)
    return pr[u] == u ? u: find(pr[u]);
  }


  void unite(int u, int v){ // O(logN)
    u = find(u), v = find(v);
    if( u == v ){
      what.push({-1, -1});
    }else{
      if( tot[u] < tot[v] ){
        swap(u, v);
      }
      what.push({u, v});
      tot[u] += tot[v];
      pr[v] = u;
    }
  }

  ii rollback(){ // O(1)
    ii last = what.top();
    what.pop();
    int u = last.f, v = last.s;
    if( u != -1 ){
      tot[u] -= tot[v];
      pr[v] = v;
    }
    return last;
  }
};
