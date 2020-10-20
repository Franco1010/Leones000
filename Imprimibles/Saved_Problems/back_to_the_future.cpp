#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <set>
#include <utility>
using namespace std;

int main(){
  cin.tie(0);
  ios_base::sync_with_stdio(0);
  int n,m,a,b,i,x,y;
  while(cin>>n>>m>>a>>b){
    vector<int>r[100000];
    set<pair<int,int> > orden;
    int s[n];
    bool in[n];
    for(i=0;i<n;i++){s[i]=0; in[i]=1;}
    for(i=0;i<m;i++){
      cin>>x>>y;
      x--;y--;
      r[x].push_back(y);
      r[y].push_back(x);
      s[y]++;s[x]++;
    }
    for(i=0;i<n;i++) orden.insert({s[i],i});
    bool salir=true;
    while(salir && !orden.empty()){
      salir=false;
      long primero=orden.begin()->second;
      for(int ite=0; ite<2;ite++){
        if(s[primero]<a || orden.size()-1-s[primero]<b){
          salir=true;
          orden.erase({s[primero],primero});
          in[primero]=0;
          for(int j:r[primero]){
            if(in[j]){
              orden.erase({s[j],j});
              s[j]--;
              orden.insert({s[j],j});
            }
          }
          break;
        }
        primero=orden.rbegin()->second;

      }
    }
    cout<<orden.size()<<'\n';
  }
}
