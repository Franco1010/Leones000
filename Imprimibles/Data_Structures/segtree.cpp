
template <typename T> struct ST{
	#define mid (l + r) / 2
	#define left(u) (u + 1)
	#define right(u) (u + ((mid - l + 1) << 1))
	vector<T> st;
	T bot;
	ST(int n, T ini, T bot):st(2*n, ini),bot(bot){}

	T f(T a, T b){ return max(a,b);}

	void update(int u, int l, int r, int v, T value){
		if(l>r)return;
		if(l==r){st[u]=value; return;}
		if(v<=mid)update(left(u), l , mid , v , value);
		else update(right(u), mid+1 , r , v , value);
		st[u]=f(st[left(u)], st[right(u)]);
	}

	T query(int u, int l, int r, int ll, int rr){
		if(l>rr or r<ll or l>r)return bot;
		if(ll<=l and r<=rr)return st[u];
		return f(query(left(u), l , mid , ll , rr) , query(right(u), mid+1 , r , ll , rr) );
	}

};
