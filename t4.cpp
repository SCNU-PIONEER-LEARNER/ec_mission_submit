#include <iostream>
#include <vector>
using namespace std;

int main(void)
{
    int num;
    vector <int> number;
    cout <<"请输入7个任意数字：";
    for(int i=0;i<7;i++)
    {
        cin >> num;   
        number.push_back(num);
    }    
 
    for(int i=number.size();i>1;i--)
    {
        for(int k=0;k<i-1;k++)
        {
            if(number[k]>number[k+1])
            {
                int temp=number[k+1];
                number[k+1]=number[k];
                number[k]=temp;                
            }
        }
    }
    cout <<"这七个数从小到大排序为：" ;
    for(int i=0;i<number.size();i++)
    {
        cout << number[i]<<" ";
    }
    return 0;
}