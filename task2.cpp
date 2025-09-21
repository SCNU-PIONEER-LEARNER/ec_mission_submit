#include <iostream>
using namespace std;

int main()
{
    int num = 1; // 桃子总数

    for(int i = 1; i < 10; i++) // 循环9天
    {
       num = (num + 1) * 2;
    }
    cout << "猴子第一天一共摘了 " << num << " 个桃子" << endl;
    return 0;
}
