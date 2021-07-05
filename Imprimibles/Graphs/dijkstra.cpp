vector<pair<int,int> > g[MAXN];  // u->[(v,cost)]
long long dist[MAXN];
void dijkstra(int x){
	memset(dist,-1,sizeof(dist));
	priority_queue<pair<long long,int> > q;
	dist[x]=0;
    q.push({0,x});
	while(!q.empty()){
		x=q.top().s;
        long long c=-q.top().f;
        q.pop();
		if(dist[x]!=c)continue;
		fore(i,0,g[x].size()){
			int y=g[x][i].f; ll c=g[x][i].s;
			if(dist[y]<0||dist[x]+c<dist[y])
				dist[y]=dist[x]+c,q.push({-dist[y],y});
		}
	}
}