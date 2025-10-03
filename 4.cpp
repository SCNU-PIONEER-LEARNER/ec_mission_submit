#include <iostream>
using namespace std;

int main(void){
    int a[7];

    cout<<"请随便输入七个整数："<<endl;
    for(int i=0;i<7;i++){
        cin>>a[i];
    }

    for(int i=0;i<6;i++){          //冒泡排序
        for(int j=0;j<6-i;j++){
            if(a[j]>a[j+1]){
                int b=a[j];
                a[j]=a[j+1];
                a[j+1]=b;
            }
        }
    }
    cout<<"排序结果为：";
    for(int i=0;i<=6;i++){
        cout<<a[i]<<" ";
    }
    return 0;
}