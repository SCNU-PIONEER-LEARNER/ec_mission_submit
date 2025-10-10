#include<iostream>
using namespace std;
int com(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}
int main(){
    int num1;
    int num2;
    cin>>num1>>num2;
    int result=com(num1,num2);
    cout<<num1*num2/result<<endl;
    return 0;
}
