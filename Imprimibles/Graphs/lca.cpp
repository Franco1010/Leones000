vector<int> g[N];
int dep[N];
int tin[N], tout[N], tour[N];
int pr[LogN][N];
int timer = 0;
int n, m;

void dfs(int u, int pr[]){ // O(N + M)
  tin[u] = ++timer;
  tour[timer] = u;
  for(int v: g[u]) if( v != pr[u] ){
    pr[v] = u;
    dep[v] = dep[u] + 1;
    dfs(v, pr);
  }
  tour[u] = timer;
}
---------------------------------------------------------
bool anc(int u, int v){ // O(1)
  return tin[u] <= tin[v] && tout[v] <= tout[u];
}

int lca(int u, int v){ // O(logN)
  if( dep[u] > dep[v] ){
    swap(u, v);
  }
  if( anc(u, v) ){
    return u;
  }
  Rof(k, LogN - 1, 0, -1){
    if( pr[k][u] && !anc(pr[k][u], v) ){
      u = pr[k][u];
    }
  }
  return pr[0][u];
}
----------------------------------------------------------
int lca(int u, int v){ // O(logN)
  if( dep[u] > dep[v] ){
    swap(u, v);
  }
  Rof(k, LogN - 1, 0, -1){
    if( dep[v] - dep[u] >= (1 << k) ){
      v = pr[k][v];
    }
  }
  if( u != v ){
    Rof(k, LogN - 1, 0, -1){
      if( pr[k][v] && pr[k][v] != pr[k][u] ){
        u = pr[k][u];
        v = pr[k][v];
      }
    }
    return pr[0][u];
  }
  return u;
}
