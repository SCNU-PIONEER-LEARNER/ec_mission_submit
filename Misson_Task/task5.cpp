#include <iostream>
#include <cmath> 

using namespace std;

// 几何体基类
class Geometry
{
public:
    // 纯虚函数：计算体积
    virtual double Volume() const = 0;
    // 纯虚函数：计算表面积
    virtual double SurfaceArea() const = 0;
    
    // 虚析构函数
    virtual ~Geometry() {}
};

// 正方体类，继承自几何体
class Cube : public Geometry 
{
private:
    double edgeLength;  // 边长，类外不可访问

public:
    // 构造函数，接收边长作为参数
    Cube(double length) : edgeLength(length) {}
    
    // 计算体积：边长的三次方
    double Volume() const override
    {
        return pow(edgeLength , 3);
    }
    
    // 计算表面积：6 * 边长的平方
    double SurfaceArea() const override 
    {
        return 6 * edgeLength * edgeLength;
    }
};

// 球类，继承自几何体
class Sphere : public Geometry 
{
private:
    double radius;  // 半径，类外不可访问

public:
    // 构造函数，接收半径作为参数
    Sphere(double r) : radius(r) {}
    
    // 计算体积：(4/3) * π * 半径的三次方
    double Volume() const override 
    {
        return (4.0 / 3.0) * M_PI * pow(radius, 3);
    }
    
    // 计算表面积：4 * π * 半径的平方
    double SurfaceArea() const override 
    {
        return 4 * M_PI * pow(radius, 2);
    }
};

// 输出几何体的体积和表面积
void printGeometryInfo(const Geometry&shape, const string&shapeName) 
{
    cout << shapeName << "的体积: " << shape.Volume() << endl;
    cout << shapeName << "的表面积: " << shape.SurfaceArea() << endl;
}

int main() 
{
    double value;

    // 输入浮点数

    cout << "输入浮点数: ";
    cin >> value;
    
    // 使用构造函数创建对象，不直接调用类的成员变量
    Cube cube(value);
    Sphere sphere(value);
    
    // 计算并输出结果
    printGeometryInfo(cube, "正方体");
    printGeometryInfo(sphere, "球");
    
    return 0;
}