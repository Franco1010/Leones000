const int inf = 1e9;
vector<edge> edges;
int dist[N];
int n, m;

void bellmand_ford(int s){ // O(N * M)
  fill_n(dist, n + 1, inf);
  dist[s] = 0;
  for(;;){
    bool any = false;
    for(edge &e: edges) if( dist[e.u] < inf ){
      if( dist[e.u] + e.dist < dist[e.v] ){
        dist[e.v] = dist[e.u] + e.dist;
        any = true;
      }
    }
    if( !any ) break;
  }
}
