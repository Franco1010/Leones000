const int MAXN = 1;
long long c1[MAXN+9],c2[MAXN+9];  // MAXN must be power of 2 !!
void fht(long long* p, int n, bool inv){
	for(int l=1;2*l<=n;l*=2)for(int i=0;i<n;i+=2*l)for(int j = 0; j < l; ++j){
		long long u=p[i+j],v=p[i+l+j];
		if(!inv)p[i+j]=u+v,p[i+l+j]=u-v; // XOR
		else p[i+j]=(u+v)/2,p[i+l+j]=(u-v)/2;
		//if(!inv)p[i+j]=v,p[i+l+j]=u+v; // AND
		//else p[i+j]=-u+v,p[i+l+j]=u;
		//if(!inv)p[i+j]=u+v,p[i+l+j]=u; // OR
		//else p[i+j]=v,p[i+l+j]=u-v;
	}
}
// like polynomial multiplication, but XORing exponents
// instead of adding them (also ANDing, ORing)
vector<long long> multiply(vector<long long>& p1, vector<long long>& p2){
	int n=1<<(32-__builtin_clz(max((int)(p1.size()),(int)(p2.size())-1)));
	for(int i = 0; i < n; ++i)c1[i]=0,c2[i]=0;
	for(int i = 0; i < (int)(p1.size()); ++i) c1[i]=p1[i];
	for(int i = 0; i < (int)(p2.size()); ++i) c2[i]=p2[i];
	fht(c1,n,false);fht(c2,n,false);
	for(int i = 0; i < n; ++i) c1[i]*=c2[i];
	fht(c1,n,true);
	return vector<long long>(c1,c1+n);
}