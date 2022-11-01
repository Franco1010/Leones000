void div_rec(vector<long long>& r, vector<pair<long long,int> >& f, int k, long long c){
	if(k==(int)f.size()){r.push_back(c);return;}
	for(int i = 0; i < f[k].second + 1; ++i) div_rec(r,f,k+1,c),c*=f[k].first;
}
vector<long long> divisors(vector<pair<long long,int> > f){
	vector<long long> r; // returns divisors given factorization
	div_rec(r,f,0,1);
	return r;
}