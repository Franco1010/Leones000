//Needs gcd

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

long long inv(long long a, long long m) {
	assert(gcd(a,m)==1);
	long long x = diophantine(a,m,1).first.first;
	return ((x%m)+m)%m;
}

#define mod(a,m) (((a)%m+m)%m)
pair<long long,long long> sol(tuple<long long,long long,long long> c){ //requires inv, diophantine
    long long a=get<0>(c), x1=get<1>(c), m=get<2>(c), d=gcd(a,m);
    if(d==1) return {mod(x1*inv(a,m),m), m};
    else return x1%d ? pair<long long, long long>({-1LL,-1LL}) : sol(make_tuple(a/d,x1/d,m/d));
}
pair<long long,long long> crt(vector< tuple<long long,long long,long long> > cond) { // returns: (sol, lcm)
	long long x1=0,m1=1,x2,m2;
	for(auto t:cond){
		tie(x2,m2)=sol(t);
		if((x1-x2)%gcd(m1,m2))return {-1,-1};
		if(m1==m2)continue;
		long long k=diophantine(m2,-m1,x1-x2).first.second,l=m1*(m2/gcd(m1,m2));
		x1=mod((__int128)m1*k+x1,l);m1=l;
	}
	return sol(make_tuple(1,x1,m1));
} //cond[i]={ai,bi,mi} ai*xi=bi (mi); assumes lcm fits in ll
