/*#include<cstdio>
#include<algorithm>

long long int modular_pow(long long int base, int exponent,
                          long long int modulus)
{
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

bool miillerTest(int d, int n){
  int a = 2 + rand() % (n - 4);
  long long x = modular_pow(a, d, n);
  if (x == 1  || x == n-1) return true;
  while (d != n-1){
    x = (x * x) % n;
    d *= 2;
    if (x == 1) return false;
    if (x == n-1) return true;
  }
  return false;
}
bool isPrime(int n, int k){
  if (n <= 1 || n == 4)  return false;
  if (n <= 3) return true;
  int d = n - 1;
  while (d % 2 == 0) d /= 2;
  for (int i = 0; i < k; i++)
    if (!miillerTest(d, n)) return false;
  return true;
}
*/
