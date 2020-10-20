template <class F>
struct dinic{
  const static F finf = numeric_limits<F>::max() / 2;

  struct edge{
    int v;
    F cap, flow;
    int inv;
    edge(int nv, F ncap, int ninv):
      v(nv), cap(ncap), flow(0), inv(ninv){}
  };

  vector< vector<edge> > g;
  vector<int> dist, ptr;
  int s, t;
  int n, m;

  dinic(int nn, int ss = -1, int tt = -1){
    n = nn + 5;
    m = 0;
    s = ss == -1 ? n + 1: ss;
    t = tt == -1 ? n + 2: tt;
    g.resize(n + 5);
    dist.resize(n + 5);
    ptr.resize(n + 5);
  }

  void add_edge(int u, int v, F cap){
    edge a(v, cap, sz(g[v]));
    edge b(u, 0, sz(g[u]));
    g[u].pb(a);
    g[v].pb(b);
    m += 2;
  }

  bool bfs(){
    fill(all(dist), -1);
    queue<int> qu;
    dist[s] = 0;
    qu.push(s);
    while( !qu.empty() ){
      int u = qu.front();
      qu.pop();
      for(edge &e: g[u]) if( e.cap - e.flow > 0 ){
        if( dist[e.v] == -1 ){
          dist[e.v] = dist[u] + 1;
          qu.push(e.v);
        }
      }
    }
    return dist[t] != -1;
  }

  F dfs(int u, F flow = finf){
    if( flow <= 0 ){
      return 0;
    }
    if( u == t ){
      return flow;
    }
    for(int &cid = ptr[u]; cid < sz(g[u]); cid++){
      edge &e = g[u][cid];
      if( e.cap - e.flow <= 0 ){
        continue;
      }
      if( dist[u] + 1 == dist[e.v] ){
        F nflow = dfs(e.v, min(flow, e.cap - e.flow));
        if( nflow > 0 ){
          e.flow += nflow;
          g[e.v][e.inv].flow -= nflow;
          return nflow;
        }
      }
    }
    return 0;
  }

  F max_flow(){ // O((N ^ 2) * M)
    F flow = 0;
    while( bfs() ){
      fill(all(ptr), 0);
      while( F nflow = dfs(s) ){
        flow += nflow;
      }
    }
    return flow;
  }
};
