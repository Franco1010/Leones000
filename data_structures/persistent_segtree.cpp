struct STree { // persistent segment tree for min over integers
	vi st, L, R; int n,tam,rt;
	STree(int n): st(1,NEUT),L(1,0),R(1,0),n(n),rt(0),tam(1){}
	int new_node(int v, int l=0, int r=0){
		int ks=sz(st); st.pb(v); L.pb(l); R.pb(r); return ks;
	}
	int upd(int k, int s, int e, int p, int v){
		int ks=new_node(st[k],L[k],R[k]);
		if(s+1==e){st[ks]=v;return ks;}
		int m=(s+e)/2,ps;
		if(p<m)ps=upd(L[ks],s,m,p,v),L[ks]=ps;
		else ps=upd(R[ks],m,e,p,v),R[ks]=ps;
		st[ks]=oper(st[L[ks]],st[R[ks]]);
		return ks;
	}
	int query(int k, int s, int e, int a, int b){
		if(e<=a||b<=s)return NEUT;
		if(a<=s&&e<=b)return st[k];
		int m=(s+e)/2;
		return oper(query(L[k],s,m,a,b),query(R[k],m,e,a,b));
	}
	int upd(int k, int p, int v){return rt=upd(k,0,n,p,v);}
	int upd(int p, int v){return upd(rt,p,v);} // update on last root
	int query(int k,int a, int b){return query(k,0,n,a,b);};
};