#include <iostream>
using namespace std;

int main() {
    int num1, num2;
    
    cout << "请输入两个正整数: ";
    cin >> num1 >> num2;
    
    if (num1 <= 0 || num2 <= 0) {
        cout << "请输入正整数！" << endl;
        return 1;
    }
    
    // 计算最大公约数
    int a = num1, b = num2;
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    int gcd = a;
    
    // 计算最小公倍数
    int lcm = (num1 * num2) / gcd;
    
    cout << num1 << " 和 " << num2 << " 的最小公倍数是: " << lcm << endl;
    
    return 0;
}