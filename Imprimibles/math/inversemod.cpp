long long inv(long long a, long long mod) { //inverse of a modulo mod
	assert(gcd(a,mod)==1);
	pair<long long, long long> sol = extendedEuclid(a,mod);
	return ((sol.first%mod)+mod)%mod;
}