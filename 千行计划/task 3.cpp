#include <iostream>
using namespace std;

int main(){
    int count = 0;
    cout<<"能组成的不同的百位数有"<<endl;

    for(int i = 1; i <= 4; i++){
        for(int j = 1; j <=4; j++){
            for(int k = 1; k <= 4; k++){
                if(j != i && j != k && i != k){
                    int num = i*100+j*10+k;
                    cout<<num<<" ";
                    count++;
                }
            }
        }
    }
    cout<<"共有"<<count<<"种不同的组合"<<endl;


    return 0;
}