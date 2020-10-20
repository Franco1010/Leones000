vector<int> g[N];
int tin[N], tout[N], tour[2 * N];
int n;

void dfs(int u, int pr = 0){ // O(N + M)
  static int timer = 0;
  tin[u] = ++timer;
  tour[timer] = u;
  for(int v: g[u]) if( v != pr ){
    dfs(v, u);
  }
  tout[u] = timer;
}
