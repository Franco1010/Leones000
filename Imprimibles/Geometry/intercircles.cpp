//Need radial order
vector<double> intercircles(vector<circle> c){
	vector<double> r(c.size() + 1); // r[k]: area covered by at least k circles
	for(int i = 0; i < c.size(); ++i){           // O(n^2 log n) (high constant)
		int k=1;Cmp s(c[i].o);
		vector<pair<pt,int> > p={
			{c[i].o+pt(1,0)*c[i].r,0},
			{c[i].o-pt(1,0)*c[i].r,0}};
		for(int j = 0; j < c.size(); ++j)if(j!=i){
			bool b0=c[i].in(c[j]),b1=c[j].in(c[i]);
			if(b0&&(!b1||i<j))k++;
			else if(!b0&&!b1){
				auto v=c[i]^c[j];
				if(v.size()==2){
					p.push_back({v[0],1});p.push_back({v[1],-1});
					if(s(v[1],v[0]))k++;
				}
			}
		}
		sort(p.begin(),p.end(),
			[&](pair<pt,int> a, pair<pt,int> b){return s(a.first,b.first);});
		for(int j = 0; j < (int)p.size(); ++j){
			pt p0=p[j?j-1:(int)p.size()-1].first,p1=p[j].first;
			double a=(p0-c[i].o).angle(p1-c[i].o);
			r[k]+=(p0.x-p1.x)*(p0.y+p1.y)/2+c[i].r*c[i].r*(a-sin(a))/2;
			k+=p[j].second;
		}
	}
	return r;
}