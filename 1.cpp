#include <iostream>
using namespace std;

int main(void){
    int count=0;

    cout<<"所有互不相同且无重复数字的三位数："<<endl;

    for(int i=1;i<=4;i++){
        for(int j=1;j<=4;j++){
            for(int k=1;k<=4;k++){
                if(i!=j&&i!=k&&j!=k){
                    cout<<i<<j<<k<<" ";
                    count++;
                    if(count%6==0){
                        cout<<endl;
                    }
                }
            }
        }
    }
    
    cout<<"总共可以组成"<<count<<"个互不相同且无重复数字的三位数"<<endl;
    
    return 0;
}