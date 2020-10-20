vector<int> g[N];
int tin[N], fup[N];
int n, m;

void bridges(int u, int pr = 0){ // O(N + M)
  static int timer = 0;
  fup[u] = tin[u] = ++timer;
  for(int v: g[u]) if( v != pr ){
    if( !tin[v] ){
      bridges(v, u);
      fup[u] = min(fup[u], fup[v]);
      if( fup[v] > tin[u] ){
        // bridge u -> v
      }
    }
    fup[u] = min(fup[u], tin[v]);
  }
}
