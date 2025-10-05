#include <iostream>
using namespace std;
int main(void) {
int count = 0;
cout << "由1、2、3、4组成的互不相同且无重复数字的三位数有:" << endl;
for (int i = 1; i <= 4; i++) {
    for (int j = 1; j <= 4; j++) {
        for (int k= 1; k <= 4; k++) {
            if(i != j && j != k && k != i){
                int number = i + j * 10 + k * 100;
                cout << number << endl;
                count++;
            }
        }
    }
}
                cout << "由1、2、3、4组成的互不相同且无重复数字的三位数有:" << count << "个 "<< endl;
                return 0;
}
