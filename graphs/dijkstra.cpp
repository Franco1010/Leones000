lli n;
vector<vector<ii>> g;
vi dijkstra(int u) {
	vi dist(n, -1);
	dist[u] = 0;
	priority_queue<ii, vector<ii>, greater<ii>> pq;
	pq.push({0, u});
	while(!pq.empty()) {
		ii cur = pq.top(); 
		pq.pop();
    for(auto it:g[cur.s]) {
      if(dist[it.f] == -1 or dist[it.f] > (cur.f + it.s)) {
        dist[it.f] = cur.f + it.s;
        pq.push({dist[it.f], it.f});
      }
    }
	}
  return dist;
}
