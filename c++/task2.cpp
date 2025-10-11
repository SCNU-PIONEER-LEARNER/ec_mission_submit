#include <iostream>
using namespace std;

int main() {
    int peaches = 1;  // 第10天剩下的桃子数
    
    // 从第10天往前逆推到第1天
    for (int day = 9; day >= 1; day--) {
        peaches = (peaches + 1) * 2;
        cout << "第" << day << "天吃之前有 " << peaches << " 个桃子" << endl;
    }
    
    cout << "\n小猴子第一天共摘了 " << peaches << " 个桃子" << endl;
    
    return 0;
}