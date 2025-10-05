#include <iostream>
using namespace std;
double pi=3.1415926;

class geometry{
    public :
    virtual double area(double a){return 0;
    }
    virtual double volume(double a){return 0;
    }
    
};

class cube : public geometry{
    public:
    double a,area1,volume1;
    double area(double a) override
    {area1 = 6*a*a;
    return area1;
    }
    double volume(double a) override
    {volume1 = a*a*a;
    return volume1;
    }
};

class circle : public geometry{
    public:
    double a,area2,volume2;
    virtual double area(double a)
    {area2 = 4*pi*a*a;
    return area2;
    }
    virtual double volume(double a)
    {volume2 = 4*pi*a*a*a/3;
    return volume2;
    }
};

int main() {
    double b,c;
    cout << "请输入正方体边长："<< endl;
    cin >> b;
    cube cube;
    cube.area(b);
    cube.volume(b);
    cout << "该正方体的表面积为："<<cube.area(b)<<"体积为:"<<cube.volume(b)<<endl;
    cout << "请输入圆的半径："<< endl;
    cin >> c;
    circle circle;
    circle.area(c);
    circle.volume(c);
    cout << "该圆的表面积为："<< circle.area(b)<<"体积为:"<< circle.volume(b)<<endl;
    return 0;
}