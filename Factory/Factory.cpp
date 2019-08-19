#include "pch.h"
#include <iostream>
#include <string>

using namespace std;

//简单工厂模式
class abstractThing	//抽象事物类
{
public:
	virtual void abstractMethod() = 0; //抽象方法
};

class implA :public abstractThing//抽象事物实现类A
{
public:
	void abstractMethod()	override
	{
		cout << "A implemented abstractThing" << endl;
	}
};

class implB : public abstractThing//同上
{
public:
	void abstractMethod()	override
	{
		cout << "B implemented abstractThing" << endl;
	}
};

class Factory //简单工厂类
{
public:
	shared_ptr<abstractThing> getInstance(string str)//第一种实现方式，但有输错的可能。
	{
		if (str == "A")
			return make_shared<implA>();//本来是new,后来决定全改成shared_ptr自动管理内存。
		else if (str == "B")
			return make_shared<implB>();
		return nullptr;
	}

	shared_ptr<abstractThing> getA()//第二种实现方式,不会输错了，但得知道都有啥方法。
	{
		return make_shared<implA>();
	}

	shared_ptr<abstractThing> getB()
	{
		return make_shared<implB>();
	}

	static shared_ptr<abstractThing> sgetA()//第三种方式，或许也是简单工厂最常用的，直接调就行了，都不用创建工厂类。
	{
		return make_shared<implA>();
	}
};

//简单工厂模式下每次添加新的实现都会修改工厂类，违反开闭原则，故产生了工厂方法模式
//说白了就是给工厂抽象一下。
class FactoryMethod
{
public:
	 virtual shared_ptr<abstractThing> getInstance() = 0;
};

class ImplAFactory :public FactoryMethod	//实现工厂，指定到实物A的工厂。这样有新的实现时只需创建个新的工厂，对扩展开放，对修改关闭。
{
public:
	shared_ptr<abstractThing> getInstance() override;
	/*{
		return make_shared<implA>();
	}*/
};
shared_ptr<abstractThing> ImplAFactory::getInstance()	//这里突发奇想想test一下override在类外还需要再写一遍么，但发现测试不出来因为我设的是纯虚函数，等文末我会再设计一个。
{
	return make_shared<implA>();
}

class ImplBFactory :public FactoryMethod	
{
public:
	shared_ptr<abstractThing> getInstance() override
	{
		return make_shared<implB>();
	}
};

//上述工厂方法模式是为了满足开闭原则而对简单工厂模式的升级，它对工厂的一层抽象也只是对这一种类型的工厂来说的，比如说车这个大类，我抽象出来的会是创建车的工厂。
//而下述抽象工厂模式是更进一步的抽象，可以创建很多不同类型的工厂。车这个大类，我可以将车更进一步抽象为交通工具，也就是说抽象工厂中还可以创建诸如摩托车，飞机……的工厂。
//是一种包含关系。

class Car	//抽象的车,对应abstractThing
{
public:
	virtual void type() = 0;
	virtual void price() = 0;
};

class Motor	//抽象摩托，同上
{
public:
	virtual void type() = 0;
	virtual void price() = 0;
};

class Mercedes_Benz:public Car	//实例车，对应ImplA
{
public:
	void type()	override
	{
		cout << "Mercedes_Benz GLC 300" << endl;	//没错GLC还挺好看的。
	}
	void price() override
	{
		cout << "56W" << endl;
	}
};

class Harley_Davidson :public Motor		//实例摩托,这可不对应ImplB，它对应另一个ImplA
{
public:
	void type() override
	{
		cout << "Harley_Davidson Street Bob "<< endl;
	}
	void price() override
	{
		cout << "53k" << endl;
	}
};

class TrafficToolsFactory	//最终极抽象，交通工具工厂
{
public:
	virtual shared_ptr<Car> getCar(string s) = 0;
	virtual shared_ptr<Motor> getMotor(string s) = 0;
};


class CarsFactory:public TrafficToolsFactory	//对车类进行抽象的抽象车工厂,但由于它继承了最终极抽象，而交通工厂类需要实例化的车辆工厂类，所以这个类不能像FactoryMethod一样是抽象类
{
public:
	virtual shared_ptr<Car> getCar(string s) override
	{
		if (s == "Mercedes_Benz")				//由于我将实例化的是车类的工厂，没有办法再用工厂方法模式了。
			return make_shared<Mercedes_Benz>();
		return nullptr;
	}
private:
	virtual shared_ptr<Motor> getMotor(string s) 
	{
		return nullptr;
	}
};

class MotorsFactory:public TrafficToolsFactory	//抽象摩托工厂，同上
{
public:
	virtual shared_ptr<Motor> getMotor(string s) override
	{
		if (s == "Harley_Davidson")
			return make_shared<Harley_Davidson>();
		return nullptr;
	}
private:
	virtual shared_ptr<Car> getCar(string s)
	{
		return nullptr;
	}
};

//class Base
//{
//public:
//	virtual void HelloWorld(int i) const
//	{
//		cout <<"right" << endl;
//	}
//};
//
//class Derived:public Base
//{
//public:
//	void HelloWorld(int i)	override;	//经过测试，override只需写在声明后面就可避免继承失误。
//	//{
//	//	cout << "hahahahaWrong" << endl;	
//	//}
//};
int main()
{
	cout << "Example of Simple Factory" << endl;
	Factory simplefac;
	/*abstractThing* A = simplefac.getImplementation("A"); 
	abstractThing* B = simplefac.getImplementation("B");*/
	shared_ptr<abstractThing> A = simplefac.getInstance("A");
	shared_ptr<abstractThing> B = simplefac.getInstance("B");
	A->abstractMethod();
	B->abstractMethod();
	shared_ptr<abstractThing> A2 = simplefac.getA();
	A2->abstractMethod();
	shared_ptr<abstractThing> A3 = Factory::sgetA();//B同理省略。
	A3->abstractMethod();
	cout << endl;

	cout << "Example of Factory Method"<<endl;
	shared_ptr<FactoryMethod> factoryA = make_shared<ImplAFactory>();//工厂方法模式由于对工厂有一层抽象，所以要先生成专门的工厂。
	shared_ptr<FactoryMethod> factoryB = make_shared<ImplBFactory>();
	shared_ptr<abstractThing> impA = factoryA->getInstance();	//然后再由专门的工厂生成实物。
	shared_ptr<abstractThing> impB = factoryB->getInstance();
	impA->abstractMethod();
	impB->abstractMethod();
	cout << endl;

	cout << "Example for Abstract Factory" << endl;
	shared_ptr<TrafficToolsFactory> carsfactory = make_shared<CarsFactory>();	
	shared_ptr<Car> Benz =	carsfactory->getCar("Mercedes_Benz");	//抽象工厂模式与工厂方法模式还是挺像的，但确实不同，抽象工厂是对工厂做了两层抽象，工厂方法只有一层。
	Benz->type();
	Benz->price();
	shared_ptr<TrafficToolsFactory> motorsfactory = make_shared<MotorsFactory>();
	shared_ptr<Motor> Harley = motorsfactory->getMotor("Harley_Davidson");
	Harley->type();
	Harley->price();
}
