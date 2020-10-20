vector<int> g[N];
int pr[N], dep[N], tot[N], heavy[N];
int head[N], pos[N], who[N];
int timer;
int n;

int dfs(int u){ // O(N + M)
  tot[u] = 1, heavy[u] = head[u] = 0;
  for(int v: g[u]) if( !dep[v] ){
    pr[v] = u;
    dep[v] = dep[u] + 1;
    tot[u] += dfs(v);
    if( tot[v] > tot[heavy[u]] ){
      heavy[u] = v;
    }
  }
  return tot[u];
}

void decompose(int u, int h){ // O(N * logN)
  head[u] = h, pos[u] = ++timer, who[timer] = u;
  if( heavy[u] != 0 ){
    decompose(heavy[u], h);
  }
  for(int v: g[u]){
    if( v != pr[u] && v != heavy[u] ){
      decompose(v, v);
    }
  }
}

void hld(int r = 1){
  pr[r] = timer = 0;
  dep[r] = 1; // Need some of depth
  dfs(r);
  decompose(r, r);
}

template <class todo>
void process_path(int u, int v, todo op){ // O(logN)
  for(; head[u] != head[v]; v = pr[head[v]]){
    if( dep[head[u]] > dep[head[v]] ){
      swap(u, v);
    }
    op(pos[head[v]], pos[v]);
  }
  if( dep[u] > dep[v] ){
    swap(u, v);
  }
  if( u != v ){
    op(pos[heavy[u]], pos[v]);
  }
  op(pos[u], pos[u]); // process lca(u, v) ?
}

template <class T>
void update_path(int u, int v, T x){ // O(logN)
  process_path(u, v, [&](int l, int r){
    st.update(l, r, x);
  });
}

template <class T>
T query_path(int u, int v){ // O(logN)
  T ans = {};
  process_path(u, v, [&](int l, int r){
    ans = unite(ans, st.query(l, r));
  });
  return ans;
}
