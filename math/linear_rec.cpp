//Needs MOD and LOG
struct LinearRec{
  typedef vector<int> vi;
  int n; vi terms, trans; vector<vi> bin;
  vi add(vi &a, vi &b){
    vi res(n*2+1);
    for(int i = 0; i < n + 1; ++i) for(int j = 0; j < n + 1; ++j) res[i+j]=(res[i+j]*1LL+(long long)a[i]*b[j])%MOD;
    for(int i=2*n; i>n; --i){
      for(int j = 0; j < n; ++j) res[i-1-j]=(res[i-1-j]*1LL+(long long)res[i]*trans[j])%MOD;
      res[i]=0;
    }
    res.erase(res.begin()+n+1,res.end());
    return res;
  }
  LinearRec(vi &terms, vi &trans):terms(terms),trans(trans){
    n=(int)(trans.size());vi a(n+1);a[1]=1;
    bin.push_back(a);
    for(int i = 1; i < LOG; ++i) bin.push_back(add(bin[i-1],bin[i-1]));
  }
  int calc(int k){
    vi a(n+1);a[0]=1;
    for(int i = 0; i < LOG; ++i) if((k>>i)&1)a=add(a,bin[i]);
    int ret=0;
    for(int i = 0 ; i < n ; ++i) ret=((long long)ret+(long long)a[i+1]*terms[i])%MOD;
    return ret;
  }
};