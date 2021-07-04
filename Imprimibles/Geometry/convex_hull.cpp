vector<pt> chull(vector<pt> p){
	if(p.size()<3)return p;
	vector<pt> r;
	sort(p.begin(),p.end()); // first x, then y
	for(int i = 0; i < (int)p.size(); ++i){ // lower hull
		while(r.size()>=2&&r.back().left(r[r.size()-2],p[i]))r.pop_back();
		r.push_back(p[i]);
	}
	r.pop_back();
	int k=r.size();
	for(int i=p.size()-1;i>=0;--i){ // upper hull
		while((int)r.size()>=k+2&&r.back().left(r[(int)r.size()-2],p[i]))r.pop_back();
		r.push_back(p[i]);
	}
	r.pop_back();
	return r;
}
