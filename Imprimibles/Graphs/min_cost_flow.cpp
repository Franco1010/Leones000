template <class F, class C>
struct mcmf{
  const static C cinf = numeric_limits<C>::max() / 2;
  const static F finf = numeric_limits<F>::max() / 2;

  struct edge{
    int v;
    F cap, flow;
    C cost;
    int inv;
    edge(int nv, C ncost, F ncap, int ninv):
      v(nv), cost(ncost), cap(ncap), flow(0), inv(ninv){}
  };

  vector< vector<edge> > g;
  vector<C> mn;
  vector<int> state, path, from;
  int s, t;
  int n, m;

  mcmf(int nn, int ss = -1, int tt = -1){
    n = nn + 5;
    m = 0;
    s = ss == -1 ? n + 1: ss;
    t = tt == -1 ? n + 2: tt;
    g.resize(n + 5);
    mn.resize(n + 5);
    state.resize(n + 5);
    path.resize(n + 5);
    from.resize(n + 5);
  }

  void add_edge(int u, int v, C cost, F cap){
    edge a(v, cost, cap, sz(g[v]));
    edge b(u, -cost, 0, sz(g[u]));
    g[u].pb(a);
    g[v].pb(b);
    m += 2;
  }

  bool bfs(){
    For1(u, n){
      state[u] = 2;
      mn[u] = cinf;
      path[u] = -1;
    }
    deque<int> qu;
    qu.push_back(s);
    state[s] = 1;
    mn[s] = 0;
    while( !qu.empty() ){
      int u = qu.front();
      qu.pop_front();
      state[u] = 0;
      for(edge &e: g[u]) if( e.cap - e.flow > 0 ){
        if( mn[u] + e.cost < mn[e.v] ){
          mn[e.v] = mn[u] + e.cost;
          path[e.v] = u;
          from[e.v] = g[e.v][e.inv].inv;
          if( state[e.v] == 0 || (!qu.empty() && mn[qu.front()] > mn[e.v]) ){
            qu.push_front(e.v);
          }else if( state[e.v] == 2 ){
            qu.push_back(e.v);
          }
          state[e.v] = 1;
        }
      }
    }
    return mn[t] != cinf;
  }

  pair<C, F> min_cost_flow(){ // O((N ^ 2) * M)
    C cost = 0;
    F flow = 0;
    while( bfs() ){
      F nflow = finf;
      for(int u, v = t; v != s; v = u){
        u = path[v];
        edge &e = g[u][from[v]];
        nflow = min(nflow, e.cap - e.flow);
      }
      for(int u, v = t; v != s; v = u){
        u = path[v];
        g[u][from[v]].flow += nflow;
        g[v][g[u][from[v]].inv].flow -= nflow;
        cost += g[u][from[v]].cost * nflow;
      }
      flow += nflow;
    }
    return make_pair(cost, flow);
  }
};
