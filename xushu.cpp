#include<iostream>
#include<cmath>
using namespace std;
class Geometry
{
    public:
    virtual double calculateVolume()const=0;
    virtual double calculateSurfaceArea()const=0;
    virtual ~Geometry(){}
};
class Cube:public Geometry
{
    private:
    double side;
    public:
    Cube(double s):side(s){}
    double calculateVolume()const override
    {
        return pow(side,3);
    }
    double calculateSurfaceArea()const override
    {
        return 6*pow(side,2);
    }
};
class Sphere:public Geometry
{
    private:
    double radius;
    public:
    Sphere(double r):radius(r){}
    double calculateVolume()const override
    {
        return (4.0/3.0)*M_PI*pow(radius,3);
    }
    double calculateSurfaceArea()const override
    {
        return 4*M_PI*pow(radius,2);
    }
};
int main()
{
    Cube cube(5.0);
    cout<<"正方体:"<<endl;
    cout<<"体积:"<<cube.calculateVolume()<<endl;
    cout<<"表面积:"<<cube.calculateSurfaceArea()<<endl;
    cout<<endl;
    Sphere sphere(3.0);
    cout<<"球:"<<endl;
    cout<<"体积:"<<sphere.calculateVolume()<<endl;
    cout<<"表面积:"<<sphere.calculateSurfaceArea()<<endl;
    return 0;
}