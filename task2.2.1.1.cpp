#include<iostream>
using namespace std;

int main(void){
    int cnt=0;
    int i,j,k;
    for(i=1;i<5;i++){
        for(j=1;j<5;j++){
           for(k=1;k<5;k++){
            if(i!=j && j!=k && k!=i){
                cnt++;
                int number=i*100+j*10+k;
                cout<<number<<"、";
            }
    } 
    }
    }
   cout<<"一共"<<cnt<<"个"<<endl;
   

}
