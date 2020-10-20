vector<int> g[N], rg[N];
vector<int> order;
int vis[N];
int scc[N], k = 0;
int n, m;

void dfs1(int u){
  vis[u] = 1;
  for(int v: g[u]) if( vis[v] != 1 ){
    dfs1(v);
  }
  order.pb(u);
}

void dfs2(int u){
  vis[u] = 2;
  scc[u] = k;
  for(int v: rg[u]) if( vis[v] != 2 ){
    dfs2(v);
  }
}

void kosaraju(){ // O(N + M)
  For1(u, n) if( vis[u] != 1 ){
    dfs1(u);
  }
  reverse(all(order));
  for(int u: order) if( vis[u] != 2 ){
    ++k;
    dfs2(u);
  }
}
