#include <iostream>
#include <string>

using namespace std;

class Base {
	public:
		virtual void f() { cout << "Base:f()" << endl; }
		virtual void g() { cout << "Base:g()" << endl; }
		virtual void h() { cout << "Base:h()" << endl; }
};

class ChildA : public Base{
	public:
		void f() { cout << "ChildA:f()" << endl; }
};

class ChildB : public Base{
	public:
		void sayHi() { cout << "ChildB:sayHi()" << endl; }
};

int main()
{
	Base t;
	ChildA a;
	ChildB b;
	
	int breakpoint = 0;

    std::cout <<"第1个虚函数地址"<<(int*)(*((int*)&t))+0 << std::endl;
    std::cout <<"第2个虚函数地址"<<(int*)(*((int*)&t))+1 << std::endl;
    std::cout <<"第3个虚函数地址"<<(int*)(*((int*)&t))+2 << std::endl;
	return 0;
}

// g++ test_dynamic_01.cpp -std=c++14 -o test_dynamic_01

// g++ -g test_dynamic_01.cpp -o test_dynamic_01 && gdb ./test_dynamic_01
// b main
// run
// next