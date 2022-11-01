int uf[MAXN];
void uf_init(){memset(uf,-1,sizeof(uf));}
int uf_find(int x){return uf[x]<0?x:uf[x]=uf_find(uf[x]);}
bool uf_join(int x, int y){
	x=uf_find(x);y=uf_find(y);
	if(x==y)return false;
	if(uf[x]>uf[y])swap(x,y);
	uf[x]+=uf[y];uf[y]=x;
	return true;
}
vector<pair<long long,pair<int,int> > > es; // edges (cost,(u,v))
long long kruskal(){  // assumes graph is connected
	sort(es.begin(),es.end());
    uf_init();
	long long r=0;
	fore(i,0,es.size()){
		int x=es[i].s.f,y=es[i].s.s;
		if(uf_join(x,y))r+=es[i].f; // (x,y,c) belongs to mst
	}
	return r; // total cost
}