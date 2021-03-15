lli inv(lli a, lli m) {//requires diophantine
	assert(gcd(a,m)==1);
	lli x = diophantine(a,m,1).f.f;
	return mod(x, m);
}
pair<lli,lli> sol(tuple<lli,lli,lli> c){ //requires inv, diophantine
    lli a=get<0>(c), x1=get<1>(c), m=get<2>(c), d=gcd(a,m);
    if(d==1) return {mod(x1*inv(a,m),m), m};
    else return x1%d ? ii({-1LL,-1LL}) : sol(make_tuple(a/d,x1/d,m/d));
}
pair<lli,lli> crt(vector< tuple<lli,lli,lli> > cond) { // returns: (sol, lcm)
	lli x1=0,m1=1,x2,m2;
	for(auto t:cond){
		tie(x2,m2)=sol(t);
		if((x1-x2)%gcd(m1,m2))return {-1,-1};
		if(m1==m2)continue;
		lli k=diophantine(m2,-m1,x1-x2).f.s,l=m1*(m2/gcd(m1,m2));
		x1=mod((__int128)m1*k+x1,l);m1=l;
	}
	return sol(make_tuple(1,x1,m1));
} //cond[i]={ai,bi,mi} ai*xi=bi (mi); assumes lcm fits in lli
