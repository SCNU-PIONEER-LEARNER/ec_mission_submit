#include <iostream>
using namespace std;

int kkk(int a,int b){
    if(b == 0){
        return a;
    }
    return kkk(b,a%b);
}

int main(){
    int a,b;
    cout<<"请输入两个正整数"<<endl;
    cin>>a>>b;

    int m = kkk(a,b);

    int i = (a/m)*b;

    cout<<"最小公倍数为："<<i<<endl;

    return 0;

}