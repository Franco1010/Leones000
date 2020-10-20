#include <iostream>
#include <cmath>
#include <vector>
using namespace std;
#define menor -1

int main(){
    vector<int> LIS;
    vector<int>::iterator it;
    string cadena;
    cin>>cadena;
    LIS.push_back(menor);
    for(int i=0;i<cadena.size();i++){
        if(cadena[i]>LIS.back()) LIS.push_back(cadena[i]);
        else{
            it=lower_bound(LIS.begin(),LIS.end(),cadena[i]);
            LIS[it-LIS.begin()]=cadena[i];
        }
    }
}
