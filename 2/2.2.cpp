#include <iostream>
using namespace std;
int main(void) {
    int a = 1;
    for (int i = 1; i <= 9 ; i++){
        a = (a + 1) * 2;
    }
cout << "小猴一开始摘了：" << a << "个桃子" << endl; 
return 0;
}  //小猴第九天吃完还剩一个的情况
