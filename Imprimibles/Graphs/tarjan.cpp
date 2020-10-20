vector<int> g[N];
vector< vector<int> > scc;
int tin[N], fup[N];
bool vis[N];
stack<int> slew;
int n, m;

void tarjan(int u, int pr = 0){ // O(N + M)
  static int timer = 0;
  fup[u] = tin[u] = ++timer;
  vis[u] = true;
  slew.push(u);
  for(int v: g[u]){
    if( !tin[v] ){
      tarjan(v, u);
    }
    if( vis[v] ){
      fup[u] = min(fup[u], fup[v]);
    }
  }
  if( fup[u] == tin[u] ){
    vector<int> cc;
    do{
      int v = slew.top();
      slew.pop();
      vis[v] = false;
      cc.pb(v);
    }while( v != u );
    scc.pb(cc);
  }
}
