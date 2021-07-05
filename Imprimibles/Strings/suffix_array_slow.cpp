const int MAXN = 1;
pair<int, int> sf[MAXN];
bool sacomp(int lhs, int rhs) {return sf[lhs]<sf[rhs];}
vector<int> constructSA(string& s){ // O(n log^2(n))
	int n=s.size();                   // (sometimes fast enough)
	vector<int> sa(n),r(n);
	for(int i = 0; i < n; ++i) r[i]=s[i];
	for(int m=1;m<n;m*=2){
		for(int i = 0; i < n; ++i) sa[i]=i,sf[i]={r[i],i+m<n?r[i+m]:-1};
		stable_sort(sa.begin(),sa.end(),sacomp);
		r[sa[0]]=0;
		for(int i = 1; i < n; ++i) r[sa[i]]=sf[sa[i]]!=sf[sa[i-1]]?i:r[sa[i-1]];
	}
	return sa;
}