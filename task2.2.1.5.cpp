#include<iostream>
#include<cmath>
using namespace std;

class solid{
    public:
    virtual double volume()=0;
    virtual double surface()=0;
    virtual ~solid() {}

}; 
class Cube: public solid{
    private:
    double side;
    public: 
    Cube(double s):side(s){}
    double volume() override{
        return side*side*side;
    }
    double surface() override{
        return side*side*6;
    }
    void display(){
        cout<<volume()<<endl;
        cout<<surface()<<endl;
    }
};
class Sphere: public solid{
    private:
    double radius;
    public:
    Sphere(double r):radius(r){}
    double volume() override{
        return (4.0/3.0)*M_PI*radius*radius*radius;
    }
    double surface() override{
        return 4*M_PI*radius*radius;
    }
    void display(){
        cout<<volume()<<endl;
        cout<<surface()<<endl;
    }
};
int main(void){
    double value;
    cin>>value;
   Cube cube(value);
   Sphere sphere(value);
   cube.display();
   sphere.display();
   return 0;
}