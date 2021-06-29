/*
 © $%Y%$-$%M%$-$%D%$ $%h%$:$%m%$:$%s%$ $%U%$ All Rights Reserved
*/

//#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,fast-math")
//#pragma GCC target("avx,avx2,fma")
#include <bits/stdc++.h>
// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/trie_policy.hpp>
// using namespace __gnu_pbds;
// typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;
#define f first
#define s second
#define fore(i,a,b) for(int i = (a), ThxMK = (b); i < ThxMK; ++i)
#define pb push_back
#define all(s) begin(s), end(s)
#define _ ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define sz(s) int(s.size())
#define ENDL '\n'
using namespace std;
typedef long double ld;
typedef long long lli;
typedef pair<lli,lli> ii;
typedef vector<lli> vi;
#define deb(x) cout << #x": " << (x) << endl;
template <typename T> static constexpr T inf = numeric_limits<T>::max() / 2;
// unsigned int
// mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
// long long
// mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
// int en rango [L,R]
// auto rnd=bind(uniform_int_distribution<int>(L,R), mt19937(time(0)));
// long long en rango [L,R]
// auto rnd=bind(uniform_int_distribution<long long>(L,R), mt19937(time(0)));
// double en rango [L, R)
// auto rnd=bind(uniform_real_distribution<double>(L,R), mt19937(time(0)));
lli gcd(lli a, lli b){return (b?gcd(b,a%b):a);}
lli lcm(lli a, lli b){ if(!a || !b) return 0; return a * b / gcd(a, b); }
int popcount(lli x) { return __builtin_popcountll(x); }
lli poww(lli a, lli b){
    lli res =1;
    while(b){ if(b&1) res = res * a; a = a*a; b/=2; }
    return res;
}
vi sieve(int N){
    vi m(N+1,0);
    vi primes(1,2);
    for(int i = 4; i < N; i += 2) m[i]=1;
    for(int i = 3; i*i <= N; i +=2) if(!m[i]) for(int j = i*i; j < N; j += i) m[j]=1;
    for(int i = 3; i < N; i += 2) if(!m[i]) primes.pb(i);
    return primes;
}
int main(){ _
  // freopen("file.in","r",stdin);
  // freopen("file.out","w",stdout);
  return 0;
}
