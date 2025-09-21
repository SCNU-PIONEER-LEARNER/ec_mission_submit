#include <iostream>
using namespace std;

int main()
{
    int num[7];
    int temp;
    
    // 输入7个数字
    cout << "请输入7个整数：" << endl;
    for (int i = 0; i < 7; i++) {
        cin >> num[i];
    }
    
    // 对数组从小到大排序
    for (int j = 0; j < 7; j++)
    {
        for (int k = j + 1; k < 7; k++)
        if (num[j] > num[k])
        {
            temp = num[j];
            num[j] = num[k];
            num[k] = temp;
        }
        else continue;
    }

    // 输出排序后的数组
    for (int n = 0; n < 7; n++)
    {
        cout << num[n] << " ";
    }

    return 0;
}