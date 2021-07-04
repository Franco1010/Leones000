void floordiv(long long x, long long y, long long& q, long long& r) { // (for negative x)
	q=x/y;r=x%y;
	if((r!=0)&&((r<0)!=(y<0)))q--,r+=y;
}