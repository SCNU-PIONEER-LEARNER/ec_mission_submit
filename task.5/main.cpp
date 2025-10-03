#include <iostream>
#include <vector>
using namespace std;

#include "geometric.h"

int main(void)
{
    float value;
    cout<<"请输入一个数作为圆的半径以及立方体的边长；\n";
    cin>>value;

    Cube cube(value);
    Sphere sphere(value);

    cout<<"立方体的面积为："<<cube.area()<<endl;
    cout<<"立方体的体积为："<<cube.volume()<<endl;
    cout<<"球的面积为："<<sphere.area()<<endl;
    cout<<"球的体积为："<<sphere.volume()<<endl;
}