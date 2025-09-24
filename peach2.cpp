#include <iostream>
using namespace std;

int main (){
    int n = 10;
    int pea = 1;

    for(int i = 1;i <= n-1;i++){
        pea = (pea+1)*2;
    }

    cout<<"There were "<<pea<<" peach 10 days ago"<<endl;

    return 0;
}