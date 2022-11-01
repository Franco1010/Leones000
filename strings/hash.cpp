struct Hash {
	int P=1777771,MOD[2],PI[2];
	vector<int> h[2],pi[2];
	Hash(string& s){
		MOD[0]=999727999;MOD[1]=1070777777;
		PI[0]=325255434;PI[1]=10018302;
		for(int k = 0; k < 2; ++k)h[k].resize(s.size()+1),pi[k].resize(s.size()+1);
		for(int k = 0; k < 2; ++k){
			h[k][0]=0;pi[k][0]=1;
			long long p=1;
			for(int i = 1; i < (int)(s.size()) + 1; ++i){
				h[k][i]=(h[k][i-1]+p*s[i-1])%MOD[k];
				pi[k][i]=(1LL*pi[k][i-1]*PI[k])%MOD[k];
				p=(p*P)%MOD[k];
			}
		}
	}
	long long get(int s, int e){
		long long h0=(h[0][e]-h[0][s]+MOD[0])%MOD[0];
		h0=(1LL*h0*pi[0][s])%MOD[0];
		long long h1=(h[1][e]-h[1][s]+MOD[1])%MOD[1];
		h1=(1LL*h1*pi[1][s])%MOD[1];
		return (h0<<32)|h1;
	}
};