#include<iostream>
using namespace std;
//ǧ�����񼸺���

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
		cout << "���������Ϊ" << tiji ()<< endl;
		cout << "����������Ϊ" << biaomianji() << endl;
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
		cout << "�������Ϊ" << tiji ()<< endl;
		cout << "��������Ϊ" << biaomianji ()<< endl;
	}
	
	

};





int main()
{
	double a;

	cout << "������һ����������";
	
	cin >> a;

	zhengfangti z(a);
	qiuti q(a);

	system("pause");

	return 0;

}