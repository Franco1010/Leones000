pair<lli,lli> extendedEuclid (lli a, lli b){ //a * x + b * y = gcd(a,b)
	lli x,y;
	if (b==0) return {1,0};
	auto p=extendedEuclid(b,a%b);
	x=p.s;
	y=p.f-(a/b)*x;
	if(a*x+b*y==-gcd(a,b)) x=-x, y=-y;
	return {x,y};
}
pair<pair<lli,lli>,pair<lli,lli> > diophantine(lli a,lli b, lli r) {
  //a*x+b*y=r where r is multiple of gcd(a,b);
	lli d=gcd(a,b);
	a/=d; b/=d; r/=d;
	auto p = extendedEuclid(a,b);
	p.f*=r; p.s*=r;
	assert(a*p.f+b*p.s==r);
	return {p,{-b,a}}; // solutions: p+t*ans.snd
}
