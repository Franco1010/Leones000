lli gcd(lli a, lli b){return a?gcd(b%a,a):b;}
lli mulmod(lli a, lli b, lli m) {
	lli r=a*b-(lli)((long double)a*b/m+.5)*m;
	return r<0?r+m:r;
}
lli expmod(lli b, lli e, lli m){
	if(!e)return 1;
	lli q=expmod(b,e/2,m);q=mulmod(q,q,m);
	return e&1?mulmod(b,q,m):q;
}
bool is_prime_prob(lli n, int a){
	if(n==a)return true;
	lli s=0,d=n-1;
	while(d%2==0)s++,d/=2;
	lli x=expmod(a,d,n);
	if((x==1)||(x+1==n))return true;
	fore(rep,0,s-1){
		x=mulmod(x,x,n);
		if(x==1)return false;
		if(x+1==n)return true;
	}
	return false;
}
bool rabin(lli n){ // true iff n is prime
	if(n==1)return false;
	int ar[]={2,3,5,7,11,13,17,19,23};
	fore(i,0,9)if(!is_prime_prob(n,ar[i]))return false;
	return true;
}
const int MAXP=1e6+1; // sieve size
int sv[MAXP]; // sieve
lli add(lli a, lli b, lli m){return (a+=b)<m?a:a-m;}
lli rho(lli n){
	static lli s[MAXP];
	while(1){
		lli x=rand()%n,y=x,c=rand()%n;
		lli *px=s,*py=s,v=0,p=1;
		while(1){
			*py++=y=add(mulmod(y,y,n),c,n);
			*py++=y=add(mulmod(y,y,n),c,n);
			if((x=*px++)==y)break;
			lli t=p;
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
	fore(i,2,MAXP)if(!sv[i])for(lli j=i;j<MAXP;j+=i)sv[j]=i;
}
void fact(lli n, map<lli,int>& f){ // call init_sv first!!!
	for(auto&& p:f){
		while(n%p.f==0){
			p.s++;
			n/=p.f;
		}
	}
	if(n<MAXP)while(n>1)f[sv[n]]++,n/=sv[n];
	else if(rabin(n))f[n]++;
	else {lli q=rho(n);fact(q,f);fact(n/q,f);}
}
