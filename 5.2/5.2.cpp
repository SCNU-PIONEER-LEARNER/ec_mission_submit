#include <iostream>
using namespace std;
double pi=3.1415926;
class geometry{
    public :
         virtual  double area()= 0;
         virtual double volume()= 0;
         virtual ~geometry(){};
         
};
class cube : public geometry{
    private:
     double side;
    public:
       cube(double a) : side (a) {}
       virtual double area()
       {
        return 6*side*side;
    }
       virtual  double volume()
       {
        return side*side*side;
    }
};
class circle : public geometry{
    private:
     double r;
    public:
       circle (double r1) : r(r1){}
       virtual double area()
       {
        return 4*pi*r*r;
    }
       virtual  double volume()
       {
       return  4 * pi * r * r * r /3;
    }
};
int main() {
    double b,c;
    cout << "请输入正方体边长："<< endl;
    cin >> b;
    cube myCube(b);
     cout << "该正方体的表面积为："<< myCube. area()<<
     "体积为:"<< myCube. volume()<<endl;
    cout << "请输入园的半径："<< endl;
    cin >> c;
    circle myCircle(c);
    cout << "该圆的表面积为："<< myCircle. area()<<
    "体积为:"<< myCircle. volume()<<endl;
     return 0;
}
    

