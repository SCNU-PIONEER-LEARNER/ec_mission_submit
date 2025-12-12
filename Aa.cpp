#include<iostream>
#include<cmath>
using namespace std;
int main()
{
    char a[10];
    cin>>a;
    for(int i=0;a[i]!='\0';i++)
    {
        a[i]=a[i]-32;
    }
    cout<<a;
    return 0;
}