/*#include<cstdio>
#include<algorithm>

long long int modular_pow(long long int base, int exponent,long long int modulus){
    long long int result = 1;
    while (exponent > 0)
    {
        if (exponent & 1)
            result = (result * base) % modulus;

        exponent = exponent >> 1;

        base = (base * base) % modulus;
    }
    return result;
}


long long int PollardRho(long long int n){
  srand (time(NULL));
  if (n==1) return n;
  if (n % 2 == 0) return 2;
  long long int x = (rand()%(n-2))+2;
  long long int y = x;
  long long int c = (rand()%(n-1))+1;
  long long int d = 1;
  while (d==1){
    x = (modular_pow(x, 2, n) + c + n)%n;
    y = (modular_pow(y, 2, n) + c + n)%n;
    y = (modular_pow(y, 2, n) + c + n)%n;
    d = __gcd(abs(x-y), n);
    if (d==n) return PollardRho(n);
  }
  return d;
}
*/
