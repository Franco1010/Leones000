vector<edge> g[N];
bool vis[N];
int n, m;

void dfs(int u, int pr = 0){ // O(N + M)
  for(edge &e: g[u]) if( !vis[e.v] ){
    dfs(e.v, u);
  }
}
