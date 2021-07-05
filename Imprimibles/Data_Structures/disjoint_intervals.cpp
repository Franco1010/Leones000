// stores disjoint intervals as [first, second)
struct disjoint_intervals {
	set<pair<int,int> > s;
	void insert(pair<int,int> v){
		if(v.f>=v.s) return;
		auto at=s.lower_bound(v);auto it=at;
		if(at!=s.begin()&&(--at)->s>=v.f)v.f=at->f,--it;
		for(;it!=s.end()&&it->f<=v.s;s.erase(it++))
			v.s=max(v.s,it->s);
		s.insert(v);
	}
};