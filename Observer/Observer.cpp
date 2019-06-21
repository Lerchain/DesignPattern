#include "pch.h"
#include <iostream>
#include <string>
#include <vector>
#include <stack>
using namespace std;			//设计模式我是看的Java的自己改的，有些不同的地方。
class observer;         //首先这里需要前向声明，因为C++继承了C的单遍编译。虽然内部应该也是multiple parse。
class subject
{
	vector<observer*> observers; //这里也不像Java单纯的直接存observer,一是因为observer没有定义，二是需要用指针来完成动态绑定。
	int state;
public:
	int getState()
	{
		return state;
	}
	void setState(int state)
	{
		this->state = state;
		notifyAllObservers();
	}
	void notifyAllObservers(); //这俩不能在类内定义，因为observer还没有定义。
	void attach(observer* o);
};
class observer
{
public:
	observer()
	{}
	virtual void update() = 0 ;
protected:
	subject* s;		//这里也是需要用指针，不像java是引用，不用指针就相当于创建了个subject。
};

void subject::notifyAllObservers()
{
	for (observer* o : observers)
	{
		o->update();
	}
}
void subject::attach(observer* o)
{
	observers.push_back(o);
}

string changeSystem(int num, int sys)  //顺便做了个转换进制函数
{
	stack<char> s;
	string res = "";
	char ch;
	int n;
	while (num)
	{
		n = num % sys;
		num /= sys;
		if (n >= 0 && n < 10)
			ch = n + '0';
		else
			ch = n - 10 + 'A';
		s.push(ch);
	}
	while (!s.empty())
	{
		res += s.top();
		s.pop();
	}
	return res;
}
class binaryObserver :public observer
{
public:
	binaryObserver(subject& _s)	//记得传址，这低级错误我都犯了
	{
		_s.attach(this);	
		s = &_s;
	}
	void update() override //填个override避免写错（虽然说update基本不能写错吧）
	{
		cout << "Binary string " << changeSystem(s->getState(),2) << endl;
	}
};
class octalObserver : public observer
{
public:
	octalObserver(subject& _s)
	{
		_s.attach(this);
		s = &_s;
	}
	void update() override
	{
		cout << "Octal string " << changeSystem(s->getState(), 8) << endl;
	}
};
class hexaObserver : public observer
{
public:
	hexaObserver(subject& _s)
	{
		_s.attach(this);
		s = &_s;
	}
	void update() override
	{
		cout << "hexa string " << changeSystem(s->getState(), 16) << endl;
	}
};
int main()
{
	subject aSubject;
	binaryObserver bo(aSubject);
	octalObserver oo(aSubject);
	hexaObserver ho(aSubject);
	aSubject.setState(10);  //done
}
