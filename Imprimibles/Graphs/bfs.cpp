vector<edge> g[N];
int dist[N];
int n, m;

void bfs(int s){ // O(N + M)
  fill_n(dist, n + 1, -1);
  queue<int> qu;
  dist[s] = 0;
  qu.push(s);
  while( !qu.empty() ){
    int u = qu.front();
    qu.pop();
    for(edge &e: g[u]){
      if( dist[e.v] == -1 ){
        dist[e.v] = dist[u] + e.dist;
        qu.push(e.v);
      }
    }
  }
}
