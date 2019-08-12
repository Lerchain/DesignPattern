#include "pch.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

class someThing
{
	int num;
	string name;
public:
	someThing(string s = "default", int n = 0):num(n),name(s){}

	void doSomeThing()
	{
		cout << name << "do" << num << "thing" << endl;
	}
};
class Decorator
{
	someThing *s;
public:
	Decorator()
	{
		s = new someThing();
	}
	Decorator(someThing something)
	{
		s = new someThing();
		*s = something;
	}
	void doSomething()
	{
		cout << "Decorating something" << endl;
		s->doSomeThing();
	}
	~Decorator()
	{
		delete s;
	}
};

int main()
{
	someThing a("I", 1);
	a.doSomeThing();
	Decorator A(a);
	A.doSomething();
}

