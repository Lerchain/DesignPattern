#include "pch.h"
#include <iostream>

using namespace std;

class something
{
public:
	virtual void dosomething() = 0;
};

class needDoSomething:public something
{
public:
	virtual void dosomething()
	{
		cout << "Something need to be done";
	}
};

class Proxy:public something
{
	needDoSomething sth;
public:
	Proxy()
	{
	}
	virtual void dosomething()
	{
		cout << "Under Proxy" << endl;
		sth.dosomething();
	}
};
int main()
{
	something *p = new Proxy();
	p->dosomething();
}

