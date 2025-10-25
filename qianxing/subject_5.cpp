#include <iostream>

using namespace std;

class Geometry {
 public:
    virtual double volume() = 0;
    virtual double area() = 0;
};

class Cube : public Geometry {
 public:
    double side = 0;
    
    double volume() { return side * side * side; }
    double area() { return 6 * side * side; }
};

class Sphere : public Geometry {
 public:
    double radius = 0;
    
    double volume() { return (4.0 / 3.0) * 3.14 * radius * radius * radius; }
    double area() { return 4 * 3.14 * radius * radius; }
};

int main() {
    double n;
    cout << "输入一个数: ";
    cin >> n;
    
    Cube cube;
    cube.side = n;
    
    Sphere sphere;
    sphere.radius = n;
    
    cout << "正方体 - 体积: " << cube.volume() << " 表面积: " << cube.area() << endl;
    cout << "球体 - 体积: " << sphere.volume() << " 表面积: " << sphere.area() << endl;
    
    return 0;
}