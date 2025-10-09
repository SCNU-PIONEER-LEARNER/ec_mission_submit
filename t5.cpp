#include <iostream>
#include <cmath>
using namespace std;
const float PI=3.1415;

class Shape
{
    public:
    virtual float v() const=0;
    virtual float s() const=0;

};

class Cube : public Shape
{
    private:
    float side;
    public:
    Cube(float a):side(a){}
    float v() const override 
    {
        return side*side*side;
    }
    float s() const override 
    {
        return 6*side*side;
    }   
};

class Circle : public Shape
{
    private:
    float r;
    public:
    Circle(float a):r(a) {}
    float v() const override
    {
        return (4.0f*PI*r*r*r)/3.0f;
    }
    float s() const override
    {
        return 4*PI*r*r;
    }
};

int main()
{
    cout <<"请输入一个正数：";
    float num;
    cin >> num;
    Cube cube(num);
    Circle circle(num);
    cout <<"正方体的体积为:"<<cube.v() <<"   "<<"表面积为："<<cube.s()<<endl;
    cout <<"球体的体积为："<<circle.v() <<"   "<<"表面积为："<<circle.s();
}