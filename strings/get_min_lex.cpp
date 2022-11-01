vi getminlex(vi s){
	int n=sz(s),k=0; fore(i,0,n) s.pb(s[i]);
	vi f(2*n,-1);
	fore(j,1,2*n){
		int i=f[j-k-1];
		while(i>=0&&s[j]!=s[k+i+1]){
			if(s[j]<s[k+i+1]) k=j-i-1;
			i=f[i];
		}
		if(s[j]!=s[k+i+1]){
			if(s[j]<s[k])k=j;
			f[j-k]=-1;
		} else f[j-k]=i+1;
	}
	vi ans; fore(i,0,n) ans.pb(s[k+i]);
	return ans;
}