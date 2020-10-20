#include <iostream>
#include <stack>
#include <vector>
using namespace std;
int main(){
    cin.tie(0);
    ios_base::sync_with_stdio(0);
    int n,i,aux;
    cin>>n;
    vector<int>cows(n,0);
    stack<unsigned int> pos;
    stack<unsigned int> h;
    h.push(-1);
    for(i=0;i<n;i++){
        cin>>aux;
        if(aux<=h.top()){h.push(aux);pos.push(i);}
        else{
            while(aux>h.top()){
                cows[pos.top()]=i+1;
                pos.pop();
                h.pop();
            }
            h.push(aux);
            pos.push(i);
        }
    }
    for(i=0;i<n;i++)cout<<cows[i]<<'\n';
}
