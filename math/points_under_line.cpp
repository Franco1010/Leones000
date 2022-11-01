long long f(long long a, long long b, long long c){
	if(c<=0) return 0;
	if(a<b) swap(a, b);
	long long m=c/a;
	if(a==b) return m*(m-1)/2;
	long long k=(a-1)/b, h=(c-a*m)/b;
	return f(b,a-b*k,c-b*(k*m+h))+k*m*(m-1)/2+m*h;
}

// # of lattice points s.t. ax+by<=c, 0<x<=X, 0<y<=Y (a,b is positive integer)
long long g(long long a, long long b, long long c, long long X, long long Y){
	if(a*X+b*Y<=c) return X*Y;
	return f(a,b,c)-f(a,b,c-a*X)-f(a,b,c-b*Y)+f(a,b,c-a*X-b*Y);
}