#include <iostream>
using namespace std;

void swap(int a,int b);
int main (void){
    const int size=7;
    int number[size];

    int i;
    for (i=0;i<size;i++){
        cin>>number[i];
    }
    int j;
    for (i=1;i<=6;i++){
        for(j=0;j<6;j++){
            if(number[j]>number[j+1]){
                swap(number[j],number[j+1]);
            }
        }


    }
    for (i=0;i<7;i++){
        cout<<number[i]<<" ";
    }
}
void swap(int a,int b){
    int c;
    c=a;
    a=b;
    b=c;
}