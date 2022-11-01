const int MAXN = 100;
short mu[MAXN] = {0,1};
void mobius(){
	for(int i = 1; i < MAXN; ++i) if(mu[i])for(int j=i+i;j<MAXN;j+=i)mu[j]-=mu[i];
}