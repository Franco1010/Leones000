#include <bits/stdc++.h>
#define For(i, a, b, c) for(int i = (a); i <= (b); i += (c))
#define Rof(i, a, b, c) for(int i = (a); i >= (b); i += (c))
#define Forn(i, n) For(i, 0, (n) - 1, +1)
#define For1(i, n) For(i, 1, (n), +1)
#define Forall(i, x) for(auto i = (x).begin(); i != (x).end(); i++)
#define size(x) (int) (x).size()
#define all(x) (x).begin(), (x).end()
#define _ ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0), cout.precision(15);
#define debug(x) cout << #x": " << x << '\n';

#define fst first
#define snd second
#define pb push_back
#define lower lower_bound
#define upper upper_bound
#define ENDL '\n'
using namespace std;

typedef long long lli;
typedef unsigned long long ulli;
typedef pair<int, int> ii;

#define N  65536
#define LogN 17

string s;

struct state {
  int sort_index;
  int suffix_index;
  int p;
};

int p[LogN][N], n, i, k, cnt;
state L[N];

int cmp(struct state a, struct state b){
  if( a.sort_index == b.sort_index ){
    return a.suffix_index < b.suffix_index;
  }
  return a.sort_index < b.sort_index;
}


void print(){
  Forn(i, n){
    cout << "sort_index: " << L[i].sort_index << " suffix_index: " << L[i].suffix_index;
    string sss = s.substr(L[i].p);
    sss.pop_back();
    cout << " string: " << sss << " ";
    cout << " p: " << L[i].p << '\n';
  }
  cout << '\n';
}

int main(void){
  //cin >> s;
  debug('i' - 'a');
  debug('m' - 'a');
  debug('p' - 'a');
  debug('s' - 'a');
  s = "mississippi$";
  //s = "attcatg$";
  n = size(s);
  Forn(i, n){
    p[0][i] = s[i] - 'a';
  }
  For1(k, LogN - 1){
    Forn(i, n){
      L[i].sort_index = p[k - 1][i];
      L[i].suffix_index = i + (1 << (k - 1)) < n ? p[k - 1][i + (1 << (k - 1))] : -1;
      L[i].p = i;
    }
    print();
    sort(L, L + n, cmp);
    Forn(i, n){
      int j = i;
      if( i > 0 && L[i].sort_index == L[i - 1].sort_index && L[i].suffix_index == L[i - 1].suffix_index ){
        j = p[k][L[i - 1].p];
      }
      p[k][L[i].p] = j;
    }
  }
  print();
  return 0;
}
