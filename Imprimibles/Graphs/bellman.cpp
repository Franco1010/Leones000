int n;
vector<pair<int,int> > g[MAXN]; // u->[(v,cost)]
long long dist[MAXN];
void bford(int src){ // O(nm)
	fill(dist,dist+n,INF);dist[src]=0;
	for(int i = 0; i<n; i+=1)fore(x,0,n)if(dist[x]!=INF)for(auto t:g[x]){
		dist[t.f]=min(dist[t.f],dist[x]+t.s);
	}
	fore(x,0,n)if(dist[x]!=INF)for(auto t:g[x]){
		if(dist[t.f]>dist[x]+t.s){
			// neg cycle: all nodes reachable from t.fst have -INF distance
			// to reconstruct neg cycle: save "prev" of each node, go up from t.fst until repeating a node. this node and all nodes between the two occurences form a neg cycle
		}
	}
}