template <typename tf, typename tc>struct MCF{
	int n;
  tf INFFLOW;
  tc INFCOST;
	vector<tc> prio, pot;
  vector<tf> curflow;
  vector<int> prevedge,prevnode;
	priority_queue<pair<tc, int>, vector<pair<tc, int>>, greater<pair<tc, int>>> q;
	struct edge{int to, rev; tf f, cap; tc cost;};
	vector<vector<edge>> g;
	MCF(int n):n(n),prio(n),curflow(n),prevedge(n),prevnode(n),pot(n),g(n){
    INFFLOW=numeric_limits<tf>::max() / 2;
    INFCOST=numeric_limits<tc>::max() / 2;
  }
	void add(int s, int t, tf cap, tc cost) {
		g[s].pb((edge){t,sz(g[t]),0,cap,cost});
		g[t].pb((edge){s,sz(g[s])-1,0,0,-cost});
	}
	pair<tf,tc> get_flow(int s, int t) {
		tf flow=0; tc flowcost=0;
		while(1){
			q.push({0, s});
			fill(all(prio),INFCOST);
			prio[s]=0; curflow[s]=INFFLOW;
			while(!q.empty()) {
				auto cur=q.top();
				tc d=cur.fst;
				int u=cur.snd;
				q.pop();
				if(d!=prio[u]) continue;
				for(int i=0; i<sz(g[u]); ++i) {
					edge &e=g[u][i];
					int v=e.to;
					if(e.cap<=e.f) continue;
					tc nprio=prio[u]+e.cost+pot[u]-pot[v];
					if(prio[v]>nprio) {
						prio[v]=nprio;
						q.push({nprio, v});
						prevnode[v]=u; prevedge[v]=i;
						curflow[v]=min(curflow[u], e.cap-e.f);
					}
				}
			}
			if(prio[t]==INFCOST) break;
			fore(i,0,n) pot[i]+=prio[i];
			tf df=min(curflow[t], INFFLOW-flow);
			flow+=df;
			for(int v=t; v!=s; v=prevnode[v]) {
				edge &e=g[prevnode[v]][prevedge[v]];
				e.f+=df; g[v][e.rev].f-=df;
				flowcost+=df*e.cost;
			}
		}
		return {flow,flowcost};
	}
};
