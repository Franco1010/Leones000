typedef vector<vector<long long> > Matrix;
long long mod = 1e9 + 7;
Matrix ones(int n) {
Matrix r(n,vector<long long>(n));
	for(int i = 0; i < n; ++i) r[i][i] = 1;
	return r;
}
Matrix operator*(Matrix &a, Matrix &b) {
	int n=(int)(a.size()),m=(int)(b[0].size()),z=(int)(a[0].size());
	Matrix r(n,vector<long long>(m));
	for(int i = 0; i < n; ++i) for(int j = 0; j < m; ++j) for(int k = 0; k < z; ++k)
		r[i][j]+=a[i][k]*b[k][j],r[i][j]%=mod;
	return r;
}
Matrix be(Matrix b, long long e) {
	Matrix r=ones((int)(b.size()));
	while(e){if(e&1LL)r=r*b;b=b*b;e/=2;}
	return r;
}