vector<int> g[N];
int cdp[N], tot[N];
bool rem[N];

void dfs(int u, int pr = 0){ // O(N + M)
  tot[u] = 1;
  for(int v: g[u]) if( v != pr && !rem[v] ){
    dfs(v, u);
    tot[u] += tot[v];
  }
}

int centroid(int u, int x, int pr = 0){ // O(logN)
  for(int v: g[u]){
    if( v != pr && !rem[v] && 2 * tot[v] > x ){
      return centroid(v, tot, u);
    }
  }
  return u;
}

void decompose(int u, int pr = 0){ // O(N * logN)
  dfs(u);
  cdp[u = centroid(u, tot[u])] = pr;
  rem[u] = true;
  for(int v: g[u]) if( !rem[v] ){
    decompose(v, u);
  }
}
