#include "pch.h"
#include <iostream>
#include <string>
using namespace std;


template<typename T>
class Calculate
{
public:
	T plus(string s)
	{
		T a[2];
		split(s, '+', a);
		return a[0] + a[1];
	}

	T minus(string s)
	{
		T a[2];
		split(s, '-', a);
		return a[0] - a[1];
	}

	T multiply(string s)
	{
		T a[2];
		split(s, '*', a);
		return a[0] * a[1];
	}

	T divide(string s)
	{
		T a[2];
		split(s, '/', a);
		if (!a[1])
			throw "0 can not be a dividend";
		return (T)a[0] / (T)a[1];
	}

	void split(string s, char t, T a[])
	{
		int n = s.size();
		int pos = s.find(t);
		if (pos == -1)
			throw "bad expresion";
		//if(s.find('.'))
		a[0] = atof(s.substr(0, pos).c_str());
		a[1] = atof(s.substr(pos + 1, n - pos).c_str());
	}
};

template<typename T>
class ICalculate
{
public:
	virtual T calculate(string s) = 0;
};

template<typename T>
class Split
{
public:
	void split(string s, char t, T a[])
	{
		int n = s.size();
		int pos = s.find(t);
		if (pos == -1)
			throw "bad expresion";
		a[0] = atof(s.substr(0, pos).c_str());
		a[1] = atof(s.substr(pos + 1, n - pos).c_str());
	}
};

template<typename T>
class Plus :public ICalculate<T>, public Split<T>
{
	Split<T> S;
public:
	virtual T calculate(string s)
	{
		T a[2];
		S.split(s, '+', a);
		return a[0] + a[1];
	}
};

template<typename T>
class Minus :public ICalculate<T>, public Split<T>
{
	Split<T> S;
public:
	virtual T calculate(string s)
	{
		T a[2];
		S.split(s, '-', a);
		return a[0] - a[1];
	}
};

template<typename T>
class Multiply :public ICalculate<T>, public Split<T>
{
	Split<T> S;
public:
	virtual T calculate(string s)
	{
		T a[2];
		S.split(s, '*', a);
		return a[0] * a[1];
	}
};

template<typename T>
class Divide :public ICalculate<T>, public Split<T>
{
	Split<T> S;
public:
	virtual T calculate(string s)
	{
		T a[2];
		S.split(s, '/', a);
		if (a[1] == 0)
			throw "Dividend can not be 0";
		return a[0] / a[1];
	}
};
int main()
{
	Calculate<int> C;
	cout << C.plus("1+2")<<endl;
	cout << C.minus("1-2")<<endl;
	cout << C.multiply("2*3")<<endl;
	cout << C.divide("2/3")<<endl;

	ICalculate<double> *p;
	p = new Plus<double>();
	cout << p->calculate("1+2") << endl;
	p = new Minus<double>();
	cout << p->calculate("1-2") << endl;
	//p = reinterpret_cast<ICalculate<double>*>(new Multiply<int>());//这是个小问题，没有办法转换，毕竟模板是编译期就替换的，目前不知道有妙招否。
	p = new Multiply<double>();
	cout << p->calculate("2*3") << endl;
	p = new Divide<double>();
	cout << p->calculate("2/3") << endl;
}
