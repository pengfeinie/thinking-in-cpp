#include <iostream>
#include <string>

using namespace std;

#include <iostream>
class Base
{
public:
	Base(int mem1 = 1, int mem2 = 2) : m_iMem1(mem1), m_iMem2(mem2) { ; }

	virtual void vfunc1() { std::cout << "In vfunc1()" << std::endl; }
	virtual void vfunc2() { std::cout << "In vfunc2()" << std::endl; }
	virtual void vfunc3() { std::cout << "In vfunc3()" << std::endl; }

private:
	int m_iMem1;
	int m_iMem2;
};

class Base2
{
public:
	Base2(int mem = 3) : m_iBase2Mem(mem) { ; }
	virtual void vBase2func1() { std::cout << "In Base2 vfunc1()" << std::endl; }
	virtual void vBase2func2() { std::cout << "In Base2 vfunc2()" << std::endl; }

private:
	int m_iBase2Mem;
};

class Base3
{
public:
	Base3(int mem = 4) : m_iBase3Mem(mem) { ; }
	virtual void vBase3func1() { std::cout << "In Base3 vfunc1()" << std::endl; }
	virtual void vBase3func2() { std::cout << "In Base3 vfunc2()" << std::endl; }

private:
	int m_iBase3Mem;
};

class Devired : public Base, public Base2, public Base3
{
public:
	Devired(int mem = 7) : m_iMem1(mem) { ; }
	virtual void vdfunc1() { std::cout << "In Devired vdfunc1()" << std::endl; }

private:
	int m_iMem1;
};

int main()
{
	// Test_3
	Devired d;
	int *dAddress = (int*)&d;
	typedef void(*FUNC)();

	/* 1. 获取对象的内存布局信息 */
	// 虚表地址一
	int *vtptr1 = (int*)*(dAddress + 0);
	int basemem1 = (int)*(dAddress + 1);
	int basemem2 = (int)*(dAddress + 2);

	int *vtpttr2 = (int*)*(dAddress + 3);
	int base2mem = (int)*(dAddress + 4);

	int *vtptr3 = (int*)*(dAddress + 5);
	int base3mem = (int)*(dAddress + 6);

	/* 2. 输出对象的内存布局信息 */
	int *pBaseFunc1 = (int *)*(vtptr1 + 0);
	int *pBaseFunc2 = (int *)*(vtptr1 + 1);
	int *pBaseFunc3 = (int *)*(vtptr1 + 2);
	int *pBaseFunc4 = (int *)*(vtptr1 + 3);

	(FUNC(pBaseFunc1))();
	(FUNC(pBaseFunc2))();
	(FUNC(pBaseFunc3))();
	(FUNC(pBaseFunc4))();
	// .... 后面省略若干输出内容，可自行补充
	return 0;
}

// g++ test_dynamic_02.cpp -std=c++14 -o test_dynamic_02

// g++ -g test_dynamic_01.cpp -o test_dynamic_01 && gdb ./test_dynamic_01
// b main
// run
// next