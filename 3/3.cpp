#include <iostream>
using namespace std;
int GCD (int m, int n)
    {   int j;
        if(m >= n)
        {
            for (int i = 1;i = 0;)
            {
             i = m % n;
             m = n; n = i;
             j = m;}
        if(m <= n)
        {for (int i =1;i = 0;){
            i = n % m;
            n = m; m = i;
            j = n;}
        return j;}
        }
    }
int main() {
    unsigned int a , b, c , d;
    cout << "请输入第一个数" << endl;
    cin >> a;
    cout << "请输入第二个数" << endl;
    cin >> b;
    c = GCD (a , b);
    d = a * b / c;
    cout << "两数的最小公倍数为：" << d;
    return 0;
 }

