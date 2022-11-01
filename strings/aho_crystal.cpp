const int A = 26;
struct vertex {
	vi next,go,leaf;
	int p,link,nl;
	char pch;
	vertex(int p=-1, char pch=-1):p(p),pch(pch),link(-1),nl(-1), next(A,-1),go(A,0){}
};
vector<vertex> t;
void aho_ini(){t.clear();t.pb(vertex());}
void add(string s, int id){
	int v=0;
	for(auto x:s){
		int c = x-'a';
		if(t[v].next[c]==-1){
			t[v].next[c]=t[v].go[c]=sz(t);
			t.pb(vertex(v,c));
		}
		v=t[v].next[c];
	}
	t[v].leaf.pb(id);
}
int go(int v, int c){return t[v].go[c];}
void BFS(){
	queue<int>q;
	q.push(0);
	t[0].link=t[0].nl=0;
	while(!q.empty()){
		int x = q.front(); q.pop();
		fore(c,0,A){
			if(t[x].next[c]==-1)continue;
			int y = t[x].next[c];
			t[y].link=x?t[t[x].link].go[c]:0;
			int link = t[y].link;
			t[y].nl = sz(t[link].leaf)?link:t[link].nl;
			for(int i = 0; i<A; i++)if(t[y].next[i]==-1)t[y].go[i]=t[link].go[i];
			q.push(y);
		}
	}
}
