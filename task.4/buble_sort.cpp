#include <iostream>
#include <vector>
using namespace std;

int main(void)
{
    int numbers[7];
    cout<<"请输入7个数字,分别用空格隔开,回车结束:"<<endl;
    for(int i=0;i<7;i++)
    {
        cin>>numbers[i];
    }

    for(int i=7;i>0;i--)
    {
        for(int j=0;j<i-1;j++)
        {
            int temp;
            if(numbers[j]>numbers[j+1])
            {
                temp = numbers[j];
                numbers[j] = numbers[j+1];
                numbers[j+1] = temp;
            }
        }
    }

    cout<<"排序后的结果是：";
    for(int i=0;i<7;i++)
    {
        cout<<numbers[i]<<" ";
    }
    cout<<endl;

}