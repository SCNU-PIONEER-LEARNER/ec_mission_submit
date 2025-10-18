#include <iostream>
using namespace std;

 unsigned kkk( unsigned n,int a = 1){
    if(n == 1) return a;

    return kkk(n-1,(a+1)*2);
}
int main (){
    unsigned int n = 10;

    unsigned peach = kkk(n);
    
    cout<<"There were "<<peach<<" peach 10 days ago"<<endl;

    return 0;
}