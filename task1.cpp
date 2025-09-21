#include <iostream>
using namespace std;

int main()
{
    int count = 0;  // 计数器
    int a[] = {1, 2, 3, 4};  // 可用数字
    
    cout << "由1、2、3、4组成的互不相同且无重复数字的三位数有：" << endl;
    
    int i,j,k,n;// 百、十、个、三位数
    for (i = 0; i < 4; i++) 
    {
        for (j = 0; j < 4; j++) 
        {
            if (j == i) continue;  
            
            for (k = 0; k < 4; k++) 
                {
                if (k == i || k == j) continue; 
                
                n = a[i] * 100 + a[j] * 10 + a[k];
                cout << n << "、";

                count++;
                
                }
            }
        }
     cout << endl << "总共有 " << count << " 个这样的三位数" << endl;
    
    return 0;
}