const int inf = 1e9;
vector<edge> g[N];
int dist[N];
int n, m;

void dijkstra(int s){ // O((N + M) * logN)
  fill_n(dist, n + 1, inf);
  priority_queue< tuple<int, int> > pq; // {dist, node}
  pq.push({dist[s] = 0, s});
  while( !pq.empty() ){
    int d, u;
    tie(d, u) = pq.top();
    pq.pop();
    if( dist[u] != -d ){
      continue;
    }
    for(edge &e: g[u]){
      if( dist[u] + e.dist < dist[e.v] ){
        dist[e.v] = dist[u] + e.dist;
        pq.push({-dist[e.v], e.v});
      }
    }
  }
}
