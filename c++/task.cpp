#include <iostream>
using namespace std;

int main() 
{
    int count = 0;
    
    cout << "所有互不相同且无重复数字的三位数：" << endl;
    
    
    for (int i = 1; i <= 4; i++) {        // 百位
        for (int j = 1; j <= 4; j++) {    // 十位
            for (int k = 1; k <= 4; k++) { // 个位
                
                if (i != j && i != k && j != k) {
                    int number = i * 100 + j * 10 + k;
                    cout << number << " ";
                    count++;
                    
                    
                }
            }
        }
    }
    
    cout << "\n\n总共可以组成 " << count << " 个互不相同且无重复数字的三位数。" << endl;
    
    return 0;
}