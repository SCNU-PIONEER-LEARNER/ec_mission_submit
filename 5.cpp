#include <iostream>
using namespace std;

class Geometry{       //几何体类
    public:
    virtual double volume()=0;
    virtual double surfacearea()=0;
};

class Cube:public Geometry{          //正方体类
    private:
    double length;

    public:
    Cube(double l){
        length=l;
    }
    double volume(){
        return length*length*length;
    }
    double surfacearea(){
        return 6*length*length;
    }
};

class Sphere:public Geometry{          //球体类
    private:
    double radius;

    public:
    Sphere(double r){
        radius=r;
    }
    double volume(){
        return (4.0/3.0)*3.14*radius*radius*radius;          //浮点数除法
    }
    double surfacearea(){
        return 4*3.14*radius*radius;
    }
};

int main(void){
    double a;
    cout<<"请输入边长/半径："<<endl;
    cin>>a;

    Cube c(a);
    Sphere s(a);

    cout<<"正方体："<<endl;
    cout<<"体积："<<c.volume()<<endl;
    cout<<"表面积："<<c.surfacearea()<<endl;

    cout<<"球体："<<endl;
    cout<<"体积："<<s.volume()<<endl;
    cout<<"表面积："<<s.surfacearea()<<endl;

    return 0;
}