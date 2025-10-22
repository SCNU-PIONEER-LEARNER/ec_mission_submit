#include <iostream>
using namespace std;
class Geometry{
    protected:
 virtual double printVolume(void)=0;//纯虚函数，有关体积的打印
 virtual double printSface(void)=0;//纯虚函数，有关表面积的打印  
};//定义几何体类

//定义立方体类
class Cube:public Geometry{
    private:
    double length,breadth,height;

    public: 
    Cube(double l){
        length=l;

    }//构造函数
    double printVolume() override{
      return length * length * length;
    }//实现纯虚函数
    double printSface() override{
        return 6*length*length;
    }//实现纯虚函数
};


//定义球体类
class Sphere:public Geometry{
    private:
    double radius ;

    public: 
    Sphere(double c){
        radius=c;
    }//构造函数
    double printVolume() override{
        return (4/3)*3.14*radius*radius*radius;
    }//实现纯虚函数
    double printSface() override{
        return 4*3.14*radius*radius;
    }//实现纯虚函数
};

    int main()
{
    double a,b;
    cout << "请输入球的半径：" << endl;
    cin >> b;//输入球的半径
    cout << "请输入立方体的边长：" << endl;
    cin >> a;//输入立方体的边长
    Cube cube(a);//创建立方体对象
    cout << cube.printVolume()<< endl;//输出立方体的体积
    cout << cube.printSface()<< endl;//输出立方体的表面积
    Sphere sphere(b);//创建球体对象
    cout << sphere.printVolume() << endl;//输出球体的体积
    cout << sphere.printSface() << endl;//输出球体的表面积
    return 0;
}