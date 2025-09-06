#include <iostream>
#include <cmath>

using namespace std;

class Box
{
private:
   float color;

public:
   double length, width, height;
   double getVolume(void);
   void set(double l, double w, double h);
};

double Box::getVolume(void)
{
   return length * width * height;
}

void Box::set(double l, double w, double h)
{
   length = l;
   width = w;
   height = h;
}

int main()
{
   Box box1;
   Box box2;

   // double volume = 0.0;

   // box1.height = 1;
   // box1.length = 1;
   // box1.width = 1;

   // box2.height = 7.0;
   // box2.length = 10.0;
   // box2.width = 1.0;

   // volume = box1.getVolume();
   // cout << "Volume of Box1 : " << volume << endl;

   // volume = box2.height * box2.length * box2.width;
   // cout << "Volume of Box2 : " << volume << endl;


   cout << std::atan(1.0/2.0) << endl;
}
