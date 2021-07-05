vector<int> computeLCP(string& s, vector<int>& sa){
	int n=(int)s.size(),L=0;
	vector<int> lcp(n),plcp(n),phi(n);
	phi[sa[0]]=-1;
	for(int i = 1; i < n; ++i) phi[sa[i]]=sa[i-1];
	for(int i = 0; i < n; ++i){
		if(phi[i]<0){plcp[i]=0;continue;}
		while(s[i+L]==s[phi[i]+L])L++;
		plcp[i]=L;
		L=max(L-1,0);
	}
	for(int i = 0; i < n; ++i) lcp[i]=plcp[sa[i]];
	return lcp; // lcp[i]=LCP(sa[i-1],sa[i])
}