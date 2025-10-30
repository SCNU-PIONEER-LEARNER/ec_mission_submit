#include <iostream>
#include <cmath>
using namespace std;

const double PI = 3.14;

// 几何体基类
class Geometry {
public:
    // 纯虚函数 - 计算体积
    virtual double calculateVolume() const = 0;
    // 纯虚函数 - 计算表面积
    virtual double calculateSurfaceArea() const = 0;
    // 虚析构函数
    virtual ~Geometry() {}
};

// 正方体类
class Cube : public Geometry {
private:
    double side;  // 边长

public:
    // 构造函数
    Cube(double s) : side(s) {}
    
    // 计算体积
    double calculateVolume() const override {
        return side * side * side;
    }
    
    // 计算表面积
    double calculateSurfaceArea() const override {
        return 6 * side * side;
    }
};

// 球类
class Sphere : public Geometry {
private:
    double radius;  // 半径

public:
    // 构造函数
    Sphere(double r) : radius(r) {}
    
    // 计算体积
    double calculateVolume() const override {
        return (4.0 / 3.0) * PI * radius * radius * radius;
    }
    
    // 计算表面积
    double calculateSurfaceArea() const override {
        return 4 * PI * radius * radius;
    }
};

int main() {
    double input;
    cout << "请输入一个浮点数: ";
    cin >> input;
    
    // 创建正方体和球对象
    Cube cube(input);
    Sphere sphere(input);
    
    // 计算并输出结果
    cout << sphere.calculateSurfaceArea() << " " 
         << sphere.calculateVolume() << " "
         << cube.calculateSurfaceArea() << " " 
         << cube.calculateVolume() << endl;
    
    return 0;
}