#include <iostream>
using namespace std;

class geometry
{
public:
	virtual double volume() = 0;
	virtual double surface() = 0;
	virtual ~geometry() {};
};

class cube : public geometry
{
private:
	double side;
public:
	double str(double s)
	{
		side = s;
		return s;
	}
	double volume()
	{ 
		return side * side * side;
	}
	double surface()
	{
		return 6 * side * side;
	}

};

class sphere : public geometry
{
private:
	double radius;
public:
	double str(double s)
	{
		radius = s;
		return s;
	}
	double volume()
	{
		return radius * radius * radius * 3.14 * (4.0 / 3.0);
	}
	double surface()
	{
		return 4 * 3.14 * radius * radius;
	}

};



int main()
{
	double s;
	cin >> s;
	cube cub;
	cout << "正方体的边长为" << cub.str(s) << endl;
	cout << "正方体的体积为" << cub.volume() << endl;
	cout << "正方体的表面积为" << cub.surface() << endl;

	sphere sph;
	cout << "球体的半径为" << sph.str(s) << endl;
	cout << "球体的体积为" << sph.volume() << endl;
	cout << "球体的表面积为" << sph.surface() << endl;

		return 0;




}


	
	

	

	





