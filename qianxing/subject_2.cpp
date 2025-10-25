#include<iostream>
using namespace std;

int main() {
    int peaches = 1; 
    
    for(int day = 9; day >= 1; day--) {
        peaches = (peaches + 1) * 2;
        cout << "第" << day << "天有 " << peaches << "个桃子" << endl;
    }
    
    cout << "小猴子第一天共摘了 " << peaches << "个桃子" << endl;
    
    return 0;
}