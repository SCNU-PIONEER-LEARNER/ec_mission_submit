#include <iostream>
using namespace std;

// 计算最大公约数
int gcd(int a, int b);

// 计算最小公倍数
int lcm(int a, int b);

int main()
{
    int num1, num2;
    cout << "请输入两个整数：";
    cin >> num1 >> num2;
    
    // 计算并输出最小公倍数
    cout << " 的最小公倍数是：" << lcm(num1, num2) << endl;
    
    return 0;
}

// 计算最大公约数
int gcd(int a, int b) 
{
    // 保证a>b
    if (a < b) 
    {
        int temp = a;
        a = b;
        b = temp;
    }
    
    // 辗转相除
    while (b != 0) 
    {
        int mod = a % b;
        a = b;
        b = mod;
    }
     return a;
}
// 计算最小公倍数
int lcm(int a, int b)
{
     if (a == 0 || b == 0) 
    {
        return 0;
    }
    // 求得最小公倍数
    int result = (a * b) / gcd(a, b);
    return result;
}