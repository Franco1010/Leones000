// LONGEST COMMON SUBSTRING
#include <iostream>
#include <algorithm>
#define ENDL '\n'
#define MOD 1000000007
using namespace std;
string a,b,res;
int L[1001][1001];
int lcs( string X, string Y, int m, int n )
{
   int i, j;
   for (i=0; i<=m; i++)
   {
     for (j=0; j<=n; j++)
     {
       if (i == 0 || j == 0)
         L[i][j] = 0;

       else if (X[i-1] == Y[j-1])
         L[i][j] = L[i-1][j-1] + 1;

       else
         L[i][j] = max(L[i-1][j], L[i][j-1]);
     }
   }
   return L[m][n];
}

void printlcs(int m, int n){
  if(L[m][n]==0)return;
  if(L[m][n]==L[m-1][n]){
    printlcs(m-1,n);
  }else if(L[m][n]==L[m][n-1]){
    printlcs(m,n-1);
  }else {
    res+=a[m-1];
    printlcs(m-1,n-1);
  }
}

int main(){
    cin.tie(0);
    ios_base::sync_with_stdio(0);
    cin>>a>>b;
    cout<<lcs(a, b,a.size(),b.size())<<ENDL;
    res="";
    printlcs(a.size(),b.size());
    reverse(res.begin(),res.end());
    cout<<res<<ENDL;
    return 0;
}
