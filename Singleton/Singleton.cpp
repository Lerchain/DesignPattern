#include "pch.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Singleton1
{
	Singleton1()
	{
		cout << "Singleton1 create successfully" << endl;
	}
public:
	static Singleton1& get_instance()
	{
		static Singleton1 instance;
		return instance;
	}
	void hello()
	{
		cout << "hello world";
	}
};

int main()
{
	Singleton1 uq = Singleton1::get_instance();
	uq.hello();
	Singleton1 uq1 = Singleton1::get_instance();
	uq1.hello();

}

