#include<iostream>
using namespace std;
int max(int a,int b)
{
    int temp;
    while(b!=0)
    {
        temp=b;
        b=a%b;
        a=temp;
    }
    return a;
}
int main()
{
    int num1;
    int num2;
    cin>>num1>>num2;
    int min=max(num1,num2);
    cout<<num1*num2/min<<endl;
    return 0;
}
