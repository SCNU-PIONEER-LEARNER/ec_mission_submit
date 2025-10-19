#include<iostream>
using namespace std;
int search(int a[],int n,int key)
{
    int i;
    for(i=0;i<n;i++)
    {
        if(a[i]==key)
            return i;
    }
    return -1;
}
# define N 10
int main()
    {
      int a[N]={1,3,5,7,9,2,4,6,8,0},i,key;
        cout<<"请输入要查找的数字：";
        cin>>key;
         while(!(cin >> key)) {
        cout << "输入错误，请输入一个数字：";
        cin.clear();  // 清除错误状态
        cin.ignore(10000, '\n');  // 清空输入缓冲区
    }
        i=search(a,N,key);
        if(i==-1)
            cout<<"没有找到"<<endl;
        else
            cout<<"找到了,位置是："<<i+1<<endl;
      
    }

    