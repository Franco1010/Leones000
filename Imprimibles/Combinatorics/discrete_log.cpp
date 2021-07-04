long long powm(long long a, long long b, long long mod){
	long long res =1;
	while(b){ if(b&1) res = (res * a) % mod; a = (a*a) % mod; b/=2; }
	return res;
}
long long discrete_log(long long a,long long b,long long m) {
    a%=m, b%=m;
    if(b == 1) return 0;
    int cnt=0;
    long long tmp=1;
    for(int g=__gcd(a,m);g!=1;g=__gcd(a,m)) {
        if(b%g) return -1;
        m/=g, b/=g;
        tmp = tmp*a/g%m;
        ++cnt;
        if(b == tmp) return cnt;
    }
    map<long long,int> w;
    int s = ceil(sqrt(m));
    long long base = b;
    for(int i = 0; i < s; ++i) {
        w[base] = i;
        base=base*a%m;
    }
    base=powm(a,s,m);
    long long key=tmp;
    for(int i = 1; i < s + 2; ++i) {
        key=base*key%m;
        if(w.count(key)) return i*s-w[key]+cnt;
    }
    return -1;
}