struct hopcroft_karp{
  vector< vector<int> > g;
  vector<int> dist;
  vector<int> match;
  int n, m;

  hopcroft_karp(int nn){
    n = nn, m = 0;
    g.resize(n + 5);
    dist.resize(n + 5);
    match.resize(n + 5, 0);
  }

  void add_edge(int u, int v){
    g[u].pb(v);
    g[v].pb(u);
    m += 2;
  }

  bool bfs(){
    queue<int> qu;
    For1(u, n - 1){
      if( match[u] ){
        dist[u] = inf;
      }else{
        dist[u] = 0;
        qu.push(u);
      }
    }
    dist[0] = inf;
    while( !qu.empty() ){
      int u = qu.front();
      qu.pop();
      if( u != 0 ){
        for(int v: g[u]){
          if( dist[u] + 1 < dist[match[v]]){
            dist[match[v]] = dist[u] + 1;
            qu.push(match[v]);
          }
        }
      }
    }
    return dist[0] != inf;
  }

  bool dfs(int u){
    if( u != 0 ){
      for(int v: g[u]){
        if( dist[u] + 1 == dist[match[v]] && dfs(match[v]) ){
          match[u] = v, match[v] = u;
          return true;
        }
      }
      dist[u] = inf;
      return false;
    }
    return true;
  }

  int max_matching(){ // O(N + M)
    int matching = 0;
    while( bfs() ){
      For1(u, n){
        if( !match[u] && dfs(u) ){
          matching++;
        }
      }
    }
    return matching;
  }
};
