int g[N][N];
int dist[N][N];
int n;

void floyd_warshall(){ // O(N ^ 3)
  For1(u, n) For1(v, n){
    dist[u][v] = (u == v ? 0: g[u][v]);
  }
  For1(k, n){ // You can set the order
    For1(u, n) For1(v, n){
      umin(dist[u][v], dist[u][k] + dist[k][v]);
    }
  }
}
