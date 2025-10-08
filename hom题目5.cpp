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
	cout << "������ı߳�Ϊ" << cub.str(s) << endl;
	cout << "����������Ϊ" << cub.volume() << endl;
	cout << "������ı����Ϊ" << cub.surface() << endl;

	sphere sph;
	cout << "����İ뾶Ϊ" << sph.str(s) << endl;
	cout << "��������Ϊ" << sph.volume() << endl;
	cout << "����ı����Ϊ" << sph.surface() << endl;

		return 0;




}


	
	

	

	





