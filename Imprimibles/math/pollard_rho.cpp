long long gcd(long long a, long long b){return a?gcd(b%a,a):b;}
long long mulmod(long long a, long long b, long long m) {
	long long r=a*b-(long long)((long double)a*b/m+.5)*m;
	return r<0?r+m:r;
}
long long expmod(long long b, long long e, long long m){
	if(!e)return 1;
	long long q=expmod(b,e/2,m);q=mulmod(q,q,m);
	return e&1?mulmod(b,q,m):q;
}
bool is_prime_prob(long long n, long long a){
	if(n==a)return true;
	long long s=0,d=n-1;
	while(d%2==0)s++,d/=2;
	long long x=expmod(a,d,n);
	if((x==1)||(x+1==n))return true;
	for(int tt = 0; tt < s - 1; ++tt){
		x=mulmod(x,x,n);
		if(x==1)return false;
		if(x+1==n)return true;
	}
	return false;
}
bool rabin(long long n){ // true iff n is prime
	if(n==1)return false;
	int ar[]={2,3,5,7,11,13,17,19,23};
	for(int i = 0; i < 9; ++i)if(!is_prime_prob(n,ar[i]))return false;
	return true;
}
long long rho(long long n){
	if(!(n&1))return 2;
	long long x=2,y=2,d=1;
	long long c=rand()%n+1;
	while(d==1){
		x=(mulmod(x,x,n)+c)%n;
		y=(mulmod(y,y,n)+c)%n;
		y=(mulmod(y,y,n)+c)%n;
		if(x>=y)d=gcd(x-y,n);
		else d=gcd(y-x,n);
	}
	return d==n?rho(n):d;
}
void fact(long long n, map<long long,int>& f){ //O (lg n)^3
	if(n==1)return;
	if(rabin(n)){f[n]++;return;}
	long long q=rho(n);fact(q,f);fact(n/q,f);
}
// optimized version: replace rho and fact with the following:
const int MAXP=1e6+1; // sieve size
int sv[MAXP]; // sieve
long long add(long long a, long long b, long long m){return (a+=b)<m?a:a-m;}
long long rho(long long n){
	static long long s[MAXP];
	while(1){
		long long x=rand()%n,y=x,c=rand()%n;
		long long *px=s,*py=s,v=0,p=1;
		while(1){
			*py++=y=add(mulmod(y,y,n),c,n);
			*py++=y=add(mulmod(y,y,n),c,n);
			if((x=*px++)==y)break;
			long long t=p;
			p=mulmod(p,abs(y-x),n);
			if(!p)return gcd(t,n);
			if(++v==26){
				if((p=gcd(p,n))>1&&p<n)return p;
				v=0;
			}
		}
		if(v&&(p=gcd(p,n))>1&&p<n)return p;
	}
}
void init_sv(){
	for(int i = 2; i < MAXP; ++i)if(!sv[i])for(long long j=i;j<MAXP;j+=i)sv[j]=i;
}
void fact(long long n, map<long long,int>& f){ // call init_sv first!!!
	for(auto&& p:f){
		while(n%p.first==0){
			p.second++;
			n/=p.first;
		}
	}
	if(n<MAXP)while(n>1)f[sv[n]]++,n/=sv[n];
	else if(rabin(n))f[n]++;
	else {long long q=rho(n);fact(q,f);fact(n/q,f);}
}