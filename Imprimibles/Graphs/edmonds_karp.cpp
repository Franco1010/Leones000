template <class F>
struct edmonds_karp{
  vector< vector<int> > g;
  vector< vector<F> > cap, mem;
  vector<int> path;
  vector<F> flow;
  int s, t;
  int n, m;

  edmonds_karp(int nn, int ss = -1, int tt = -1){
    n = nn + 5;
    m = 0;
    s = ss == -1 ? n + 1: ss;
    t = tt == -1 ? n + 2: tt;
    g.resize(n + 5);
    cap.resize(n + 5, vector<F>(n + 5));
    // mem.resize(n + 5, vector<F>(n + 5)); // Original capacity
    path.resize(n + 5);
    flow.resize(n + 5);
  }

  void add_edge(int u, int v, F ncap){
    g[u].pb(v);
    g[v].pb(u);
    cap[u][v] = cap[v][u] = ncap;
    // mem[u][v] = mem[v][u] = ncap;
  }

  F bfs(){
    fill(all(path), -1);
    fill(all(flow), 0);
    queue<int> qu;
    qu.push(s);
    flow[s] = numeric_limits<F>::max() / 2;
    while( !qu.empty() ){
      int u = qu.front();
      qu.pop();
      for(int v: g[u]){
        if( path[v] == -1 && cap[u][v] > 0 ){
          path[v] = u;
          flow[v] = min(flow[u], cap[u][v]);
          if( v == t ){
            return flow[v];
          }
          qu.push(v);
        }
      }
    }
    return 0;
  }

  F max_flow(){ // O(N * (M ^ 2))
    F flow = 0;
    while( F nflow = bfs() ){
      flow += nflow;
      for(int v = t; v != s; v = path[v]){
        int u = path[v];
        cap[u][v] -= nflow;
        cap[v][u] += nflow;
      }
    }
    return flow;
  }

  void min_cut(){
    For1(u, n - 1) if( flow[u] > 0 ){
      for(int v: g[u]) if( !flow[v] && mem[u][v] ){
        // Cut edge u -> v
      }
    }
  }
};
