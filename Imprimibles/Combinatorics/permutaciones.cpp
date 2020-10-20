
#include <iostream>
#include <map>
#include <vector>
using namespace std;
void permute(vector <int> a, int i, int n)
{
    int j;
    if (i == n)  {
        for(j=0;j<n;j++){
            cout<<a[j]<<" ";
        }
        cout<<endl;
    }
    else
    {
        for (j = i; j < n; j++){
            swap(a[i], a[j]);
            permute(a, i+1, n);
            swap(a[i], a[j]);
        }
    }
}
 int main(){
    cin.tie(0);
    ios_base::sync_with_stdio(0);
     vector <int> num;
     int r,s;
    cin>>r;
     for(int i=0;i<r;i++){
         cin>>s;
         num.push_back(s);
     }
    permute(num,0,r );
}
