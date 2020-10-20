vector<int> g[N];
vector<int> order;
int indeg[N];
int n, m;

void topsort(){ // O(N + M), first fill the indeg[]
  queue<int> qu;
  For1(u, n){
    if( !indeg[u] ){
      qu.push(u);
    }
  }
  while( !qu.empty() ){
    int u = qu.front();
    qu.pop();
    order.pb(u);
    for(int v: g[u]){
      if( --indeg[v] == 0 ){
        qu.push(v);
      }
    }
  }
}
