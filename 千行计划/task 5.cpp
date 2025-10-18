#include <iostream>
#include <cmath>

using namespace std;

const double pi = 3.1415926535;

class Geo {
public:
    virtual double v() const = 0;
    virtual double s() const = 0;
    virtual ~Geo() {}
};

class Cube : public Geo{     //正方体
private:
    double side;

public:
    Cube(double l) : side(l){}

    double v() const override{
        return side * side * side;
    }

    double s() const override{
        return side * side * 6;
    }
};

class Ball : public Geo{   //秋天
private:
    double r;

public:
    Ball(double x) : r(x) {}

    double v() const override{
        return (4.0 / 3.0) * pi * r * r * r;
    }

    double s() const override{
        return 4 * pi * r * r;
    }
};



int main(){
    double q;
    cout<<"请输入一个浮点数：";
    cout.flush();
    cin>>q;

    Cube cube(q);

    Ball ball(q);

    cout<<"正方体 ";
    cout<<"体积为："<< cube.v() << endl;
    cout<<"表面积为："<<cube.s() << endl;

    cout<<"球体 ";
    cout<<"体积为："<< ball.v() << endl;
    cout<<"表面积为："<<ball.s() << endl;

    return 0;
}