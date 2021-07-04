// Needs a const ITER
typedef double tp; // type of polynomial
template<class T=tp>
struct poly {  // poly<> : 1 variable, poly<poly<>>: 2 variables, etc.
	vector<T> c;
	T& operator[](int k){return c[k];}
	poly(vector<T>& c):c(c){}
	poly(initializer_list<T> c):c(c){}
	poly(int k):c(k){}
	poly(){}
	poly operator+(poly<T> o){
		int m=c.size(),n=o.c.size();
		poly res(max(m,n));
		for(int i = 0; i < m; ++i)res[i]=res[i]+c[i];
		for(int i = 0; i < n; ++i)res[i]=res[i]+o.c[i];
		return res;
	}
	poly operator*(tp k){
		poly res(c.size());
		for(int i = 0; i < (int)c.size(); ++i)res[i]=c[i]*k;
		return res;
	}
	poly operator*(poly o){
		int m=c.size(),n=o.c.size();
		poly res(m+n-1);
		for(int i = 0; i < m; ++i)for(int j = 0; j < n; ++j)res[i+j]=res[i+j]+c[i]*o.c[j];
		return res;
	}
	poly operator-(poly<T> o){return *this+(o*-1);}
	T operator()(tp v){
		T sum(0);
		for(int i=c.size()-1;i>=0;--i)sum=sum*v+c[i];
		return sum;
	}
	void print(){
		while(!c.empty()&&abs(c.back())<EPS)c.pop_back();
		if(c.empty())puts(" 0");
		else {
			for(auto x:c)printf(" %.6lf",x);
			puts("");
		}
	}
};
// only for double polynomials
pair<poly<>,poly<> > polydiv(poly<> p, poly<> q){ // returns pair (result,rem)
	int n=p.c.size()-q.c.size()+1;
	vector<tp> b(n);
	for(int k=n-1;k>=0;--k){
		b[k]=p.c.back()/q.c.back();
		for(int i = 0; i < (int)q.c.size(); ++i)p[i+k]-=b[k]*q[i];
		p.c.pop_back();
	}
	while(!p.c.empty()&&abs(p.c.back())<EPS)p.c.pop_back();
	return {poly<>(b),p};
}

double pget(poly<>& p, int k){return k<p.c.size()?p[k]:0;}
poly<> bairstow(poly<> p){ // returns polynomial of degree 2 that
	int n=p.c.size()-1;    // divides p
	assert(n>=3&&abs(p.c.back())>EPS);
	double u=p[n-1]/p[n],v=p[n-2]/p[n];
	for(int iter = 0; iter < ITER; ++iter){
		auto w=polydiv(p,{v,u,1});
		poly<> q=w.first,r0=w.second;
		poly<> r1=polydiv(q,{v,u,1}).second;
		double c=pget(r0,1),d=pget(r0,0),g=pget(r1,1),h=pget(r1,0);
		double det=1/(v*g*g+h*(h-u*g)),uu=u;
		u-=det*(-h*c+g*d);v-=det*(-g*v*c+(g*uu-h)*d);

	}
	return {v,u,1};
}
void addr(vector<double>& r, poly<>& p){
	assert(p.c.size()<=3);
	if(p.c.size()<=1)return;
	if(p.c.size()==2)r.push_back(-p[0]/p[1]);
	if(p.c.size()==3){
		double a=p[2],b=p[1],c=p[0];
		double d=b*b-4*a*c;
		if(d<-0.1)return; // huge epsilon because of bad precision
		d=d>0?sqrt(d):0;r.push_back((-b-d)/2/a);r.push_back((-b+d)/2/a);
	}
}
vector<double> roots(poly<> p){
	while(!p.c.empty()&&abs(p.c.back())<EPS)p.c.pop_back();
	for(int i = 0; i < (int)p.c.size(); ++i)p[i]/=p.c.back();
	vector<double> r;int n;
	while((n=p.c.size()-1)>=3){
		poly<> q=bairstow(p);addr(r,q);
		p=polydiv(p,q).first;
		while((int)p.c.size()>n-1)p.c.pop_back();
	}
	addr(r,p);
	return r;
}
