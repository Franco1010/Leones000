long long MOD = 1e9 + 7;
long long powm(long long a, long long b, long long mod){
	long long res =1;
	while(b){ if(b&1) res = (res * a) % mod; a = (a*a) % mod; b/=2; }
	return res;
}
vector<int> BM(vector<int> x){
vector<int> ls,cur;int lf,ld;
for(int i = 0; i < (int)(x.size()); ++i){
	long long t=0;
	for(int j = 0; j < (int)(cur.size()); ++j) t=(t+x[i-j-1]*(long long)cur[j])%MOD;
	if((t-x[i])%MOD==0)continue;
	if(!(int)cur.size()){cur.resize(i+1);lf=i;ld=(t-x[i])%MOD;continue;}
	long long k=-(x[i]-t)*powm(ld,MOD-2, MOD)%MOD;
	vector<int> c(i-lf-1);c.push_back(k);
	for(int j = 0; j < (int)(ls.size()); ++j) c.push_back(-ls[j]*k%MOD);
	if((int)c.size()<(int)(cur.size()))c.resize((int)(cur.size()));
	for(int j = 0; j < (int)(cur.size()); ++j) c[j]=(c[j]+cur[j])%MOD;
	if(i-lf+(int)(ls.size())>=(int)(cur.size()))ls=cur,lf=i,ld=(t-x[i])%MOD;
	cur=c;
}
for(int i = 0; i < (int)(cur.size()); ++i) cur[i]=(cur[i]%MOD+MOD)%MOD;
return cur;
}