#include <vector>
#include<iostream>
using namespace std;
int main(void)
{
    vector<int>numbers;
    int num;
    cout<<"请输入整数序列，整数之间用空格隔开："<<endl;
    while(cin>>num)
    {
        numbers.push_back(num);
    }
    
    for(int k=numbers.size();k>1;)
    {
        int m=0;
        for(int i=0;i<k-1;i++)
        {
            if(numbers[i]>numbers[i+1])
         {
            int temp =numbers[i];
            numbers[i]=numbers[i+1];
            numbers[i+1]=temp;
            m=i+1;
         }

        }
        k=m;
        
    }
    for(int num:numbers)
    {
        cout<<num<<" ";
    }
    return 0;


}