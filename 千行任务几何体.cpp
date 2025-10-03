#include<iostream>
using namespace std;
//千行任务几何体

class jiheti {
public:
	virtual double tiji() = 0;
	virtual double biaomianji() = 0;

};

class zhengfangti : public jiheti {
private:
	double bianchang;
	double tiji() {
		return bianchang * bianchang * bianchang;
	};

	double biaomianji() {
		return 6 * bianchang * bianchang;
	};

public:
	zhengfangti(double l) :bianchang(l){
		cout << "正方体体积为" << tiji ()<< endl;
		cout << "正方体表面积为" << biaomianji() << endl;
	};

	

};


class qiuti : public jiheti {
private :
	double banjing;

	double tiji() {
		return   banjing * banjing * banjing * 3.14 * (4.0 / 3.0);
	};

	double biaomianji() {
		return 4 * 3.14 * banjing * banjing;
	};
public:
	qiuti(double r):banjing(r) {
		cout << "球体体积为" << tiji ()<< endl;
		cout << "球体表面积为" << biaomianji ()<< endl;
	}
	
	

};





int main()
{
	double a;

	cout << "请输入一个浮点数：";
	
	cin >> a;

	zhengfangti z(a);
	qiuti q(a);

	system("pause");

	return 0;

}