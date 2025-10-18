#include <iostream>
using namespace std;

int main(){
    int num[7];

    cout<<"请输入7个整数,中间用空格隔开"<<endl;
    for (int i = 0; i < 7; i++) {
        cin >> num[i];
    }
    
    for (int i = 0;i < 6;i++){
        for (int n = 0; n <= 6-i; n++){
            if (num[n] > num[n+1]){
                swap(num[n],num[n+1]);
            }
        }
    }
    for(int nu:num){
        cout<<nu<<" ";
    }

    return 0;
}