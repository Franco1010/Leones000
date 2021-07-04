//Need gcd
pair<long long,long long> extendedEuclid (long long a, long long b){ //a * x + b * y = gcd(a,b)
	long long x,y;
	if (b==0) return {1,0};
	auto p=extendedEuclid(b,a%b);
	x=p.second;
	y=p.first-(a/b)*x;
	if(a*x+b*y==-gcd(a,b)) x=-x, y=-y;
	return {x,y};
}
pair<pair<long long,long long>,pair<long long,long long> > diophantine(long long a,long long b, long long r) {
	//a*x+b*y=r where r is multiple of gcd(a,b);
	long long d=gcd(a,b);
	a/=d; b/=d; r/=d;
	auto p = extendedEuclid(a,b);
	p.first*=r; p.second*=r;
	assert(a*p.first+b*p.second==r);
	return {p,{-b,a}}; // solutions: p+t*ans.snd
}