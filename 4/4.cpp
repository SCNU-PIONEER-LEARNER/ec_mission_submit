#include <iostream>
using namespace std;
int main() {
    int a[7] {13,11,9,7,5,3,1};
    int i,j,temp;
    for (int j=0;j<6;j++){
        for (int i = 0;i<6; i++){
            if(a[i]>a[i+1]){
               temp=a[i];
               a[i]=a[i+1];
               a[i+1]=temp;

            }
        }
    }
    for (int j=0;j<7;j++){
    cout << a[j]<<endl;
    }
    cout << endl;
return 0;
}