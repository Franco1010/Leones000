
template<typename T>
struct Matrix{
	vector<vector<T>> a;
	Matrix(){}
	Matrix(size_t n, size_t m):a(n, vector<T>(m, 0)){}
	Matrix(size_t n):Matrix(n, n){}
	Matrix(vector<vector<T>> a):a(a){}

	size_t height() const{ return a.size();}
	size_t width() const{return a[0].size();}

	inline const vector<T> &operator[](size_t k) const{return a[k];}
	inline vector<T> &operator[](size_t k){return a[k];}

	static Matrix I(size_t n){
		Matrix mat(n);
		for(int i=0; i<n; i++) mat[i][i]=1;
		return mat;
	}

	Matrix &operator+=(const Matrix &b){
		size_t n=height(), m=width();
		for(int i=0; i<n; i++)for(int j=0; j<m; j++)(*this)[i][j]+=b[i][j];
		return (*this);
	}
	Matrix &operator-=(const Matrix &b){
		size_t n=height(), m=width();
		for(int i=0; i<n; i++)for(int j=0; j<m; j++)(*this)[i][j]-=b[i][j];
		return (*this);
	}
	Matrix &operator*=(const Matrix &b){
		size_t n=height(), m=width(), l=b.width();
		vector<vector<T>> c(n, vector<T>(l, 0));
		for(int i=0; i<n; i++)for(int j=0; j<l; j++)for(int k=0; k<m; k++)c[i][j]+=(*this)[i][k]*b[k][j];
		a.swap(c);
		return (*this);
	}
	Matrix operator+(const Matrix &b) const{return (Matrix(*this)+=b);}
	Matrix operator-(const Matrix &b) const{return (Matrix(*this)-=b);}
	Matrix operator*(const Matrix &b) const{return (Matrix(*this)*=b);}

	Matrix pow(lli k) const{
		Matrix ap(a), ret=I(height());
		while(k){
			if(k&1) ret*=ap;
			ap*=ap;
			k>>=1;
		}
		return ret;
	}

	static pair<Matrix, Matrix> Gauss_Jordan(const Matrix &a, const Matrix &b){
		size_t n=a.height(), m=a.width(), l=b.width();
		Matrix c(n, m+l);
		for(int i=0; i<n; i++) for(int j=0; j<m; j++) c[i][j]=a[i][j];
		for(int i=0; i<n; i++) for(int j=0; j<l; j++) c[i][j+m]=b[i][j];
		int d=0;
		for(int i=0; i<m; i++){
			int p=-1;
			for(int j=d; j<n; j++)if(c[j][i]!=0){p=j; break;}
			if(p==-1) continue;
			swap(c[p], c[d]);
			T invc=T(1)/c[d][i];
			for(int j=i; j<m+l; j++) c[d][j]*=invc;
			for(int j=0; j<n; j++){
				if(j==d) continue;
				T c0=c[j][i];
				for(int k=i; k<m+l; k++)c[j][k]-=c0*c[d][k];
			}
			d++;
		}
		Matrix reta(n, m), retb(n, l);
		for(int i=0; i<n; i++) for(int j=0; j<m; j++) reta[i][j]=c[i][j];
		for(int i=0; i<n; i++) for(int j=0; j<l; j++) retb[i][j]=c[i][j+m];
		return make_pair(reta, retb);
	}

	static pair<vector<T>, vector<vector<T>>> linear_equations(const Matrix &a, const vector<T> &b){
		int n=a.height(), m=a.width();
		Matrix B(n, 1);
		for(int i=0; i<n; i++) B[i][0]=b[i];
		auto p=Gauss_Jordan(a, B);
		vector<int> myon(n,-1);
		vector<int> nuo(m, -1);
		for(int i=0; i<n; i++){
			bool allzero=1;
			for(int j=0; j<m; j++)if(p.first[i][j]!=0){
					allzero=0;
					myon[i]=j;
					nuo[j]=i;
					break;
				}
			if(allzero && p.second[i][0]!=0){
				vector<T> retc;
				vector<vector<T>> retd;
				return make_pair(retc, retd);
			}
		}
		vector<T> c(m);
		vector<vector<T>> d;
		for(int i=0; i<m; i++){
			if(nuo[i]==-1){
				vector<T> v(m);
				v[i]=1;
				for(int j=0; j<n; j++)if(myon[j]!=-1) v[myon[j]]=-p.first[j][i];
				d.push_back(v);
			}else c[i]=p.second[nuo[i]][0];
		}
		return make_pair(c, d);
	}

	Matrix inv() const{
		int n=height();
		Matrix b=I(n);
		auto p=Gauss_Jordan(*this, b);
		if(p.first[n-1][n-1]==0){
			Matrix ret(0);
			return ret;
		}
		return p.second;
	}

	int rank() const{
		int n=height(), m=width();
		Matrix b(n, 0);
		auto p=Gauss_Jordan(*this, b);
		for(int i=0; i<n; i++){
			bool allzero=1;
			for(int j=0; j<m; j++)if(p.first[i][j]!=0){
					allzero=0;
					break;
				}
			if(allzero) return i;
		}
		return n;
	}

	T det() const{
		size_t n=height();
		Matrix A(a);
		T ret(1);
		for(int i=0; i<n; i++){
			int p=-1;
			for(int j=i; j<n; j++)if(A[j][i]!=0){
					p=j; break;
				}
			if(p==-1)return 0;
			if(p!=i) ret*=(-1);
			swap(A[p], A[i]);
			ret*=A[i][i];
			T inva=T(1)/A[i][i];
			for(int j=i+1; j<n; j++){
				T a0=A[j][i];
				for(int k=i; k<n; k++)A[j][k]-=inva*a0*A[i][k];
			}
		}
		return ret;
	}
};
