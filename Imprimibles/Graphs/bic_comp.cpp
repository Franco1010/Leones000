struct Biconnected{
	// articulation point iff B[i] !=0
	// nbc = number of biconnected components
	struct edge {int u,v,comp;bool bridge;};
	vector<edge> e;
	vector<vector<int>>g;
	int n,nbc,T;
	void add_edge(int u, int v){
		g[u].pb(sz(e));
		g[v].pb(sz(e));
		e.pb({u,v,-1,0});
	}
	vector<int>D,B,art;
	stack<int> st;
	void dfs(int u,int pe){
		B[u]=D[u]=T++;
		for(int ne:g[u])if(ne!=pe){
			int v=e[ne].u^e[ne].v^u;
			if(D[v]<0){
				st.push(ne);
				dfs(v,ne);
				if(B[v]>D[u])e[ne].bridge = true;
				if(B[v]>=D[u]){
					while(1){
						int last=st.top();st.pop();
						e[last].comp=nbc;
						if(last==ne)break;
					}
					nbc++; art[u]++;
				}
				B[u]=min(B[u],B[v]);
			}
			else if(D[v]<D[u])st.push(ne),B[u]=min(B[u],D[v]);
		}
	}

	Biconnected(int n):n(n),nbc(0),T(0){
		D = vector<int>(n,-1);
		art = B = vector<int>(n,0);
		g = vector<int>(n);
	}

	void run(){
		fore(i,0,n)if(D[i]<0)dfs(i,-1),art[i]--;
	}

	auto get_cmp(){
		vector<vector<int>>v(nbc);
		for(auto i:e)v[i.comp].pb(i.u), v[i.comp].pb(i.v);
		return v;
	}

};
