#include <iostream>
#include <cmath>

using namespace std;

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
    double side; // 边长

public:
    // 构造函数
    Cube(double s) : side(s) {}
    
    // 计算正方体体积
    double calculateVolume() const override {
        return side * side * side;
    }
    
    // 计算正方体表面积
    double calculateSurfaceArea() const override {
        return 6 * side * side;
    }
};

// 球类
class Sphere : public Geometry {
private:
    double radius; // 半径

public:
    // 构造函数
    Sphere(double r) : radius(r) {}
    
    // 计算球体积
    double calculateVolume() const override {
        return (4.0 / 3.0) * M_PI * radius * radius * radius;
    }
    
    // 计算球表面积
    double calculateSurfaceArea() const override {
        return 4 * M_PI * radius * radius;
    }
};

int main() {
    double input;
    
    // 输入浮点数
    cout << "请输入一个浮点数: ";
    cin >> input;
    
    // 创建正方体对象并计算
    Cube cube(input);
    cout << "正方体 - 边长: " << input << endl;
    cout << "体积: " << cube.calculateVolume() << endl;
    cout << "表面积: " << cube.calculateSurfaceArea() << endl;
    
    cout << "------------------------" << endl;
    
    // 创建球对象并计算
    Sphere sphere(input);
    cout << "球 - 半径: " << input << endl;
    cout << "体积: " << sphere.calculateVolume() << endl;
    cout << "表面积: " << sphere.calculateSurfaceArea() << endl;
    
    return 0;
}