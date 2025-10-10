#include<iostream>
#include<cmath>
using namespace std;
class GeometricShapes 
{
    protected:
    virtual float Volume()=0;
    virtual float SurfaceArea( )=0;
    virtual ~GeometricShapes()=default;

};
class Cube:protected GeometricShapes
{   private:
    float SideLength;
    public:
    Cube(float s):SideLength(s){};
    virtual float Volume()
    {
        return SideLength*SideLength*SideLength;
    }
    virtual float SurfaceArea() 
    {
        return SideLength*SideLength*6;
    }
    
};
class Sphere:protected GeometricShapes
{   private:
    float Radius;
    public:
    Sphere(float r ):Radius(r){};
    virtual float Volume( )
    {
        return 4*Radius*Radius*Radius*M_PI/3;
    }
    virtual float SurfaceArea( )
    {
        return Radius*Radius*4*M_PI;
    }
};
int main()
{
float num;
cout<<"请输入一个浮点数"<<endl;
cin>>num;

Cube cube(num);
cout<<"正方体边长是"<<num<<endl;
cout<<"正方体体积是"<<cube.Volume()<<endl;
cout<<"正方体表面积是"<<cube.SurfaceArea()<<endl;
Sphere sphere(num);
cout<<"球体半径是"<<num<<endl;
cout<<"球体体体积是"<<sphere.Volume()<<endl;
cout<<"球体体表面积是"<<sphere.SurfaceArea()<<endl;
return 0;
}