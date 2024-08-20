# 强制类型转换

强制类型转换，也称为显式转换，C++中强制类型转换操作符有static_cast、dynamic_cast、const_cast、reinterpert_cast。

## 1. static_cast

This is the simplest type of cast that can be used. It is a **compile-time cast**. It does things like implicit conversions between types (such as int to float, or pointer to void*), and it can also call explicit conversion functions.

语法 ：static_cast< 想要的类型> (原数据)， 是C++中的关键字。

- 隐式类型转换，比如 char->int , 类层次结构中基类和派生类之间指针或引用的转换。

- 编译器隐式执行的任何类型转换都可以由static_cast显式完成。

- 我们要确保目标数据类型是我们想要的类型，因为static_cast 不做运行时的类型检查RTTI。

- static_cast 会做编译时的类型检查，但C语言的强制类型转换不会做编译时的类型检查。

- 不能更改数据 const , static 等属性。

### 1.1 基本数据类型转换

```c++
#include <iostream>

int main()
{
	float f = 3.5;
	// Implicit type case,float to int
	int a = f;
	std::cout << "The Value of a: " << a << std::endl;
	// using static_cast for float to int
	int b = static_cast<int>(f);
	std::cout << "The Value of b: " << b << std::endl;
}
```

### 1.2 **for primitive data type pointers**

```c++
#include <iostream>

int main()
{
	int a = 10;
	char c = 'a';

	int* q = (int*)&c; // ok
	//int* p = static_cast<int*>(&c); // compile time error
	int* p = static_cast<int*>(static_cast<void*>(&c)); // ok
	return 0;
}
```

### 1.3 for Inheritance

static_cast can provide both upcasting and downcasting in case of inheritance. The following example demonstrates the use of static_cast in the case of upcasting.

- 用于类层次结构中基类和派生类之间指针或引用的转换。


- 进行上行转换（把派生类的指针或引用转换成基类表示）是**安全**的；


- 进行下行转换（把基类指针或引用转换成派生类表示）是**不安全**的。


static_cast用在于基类与派生类指针或引用类型之间的转换，然而它不做运行时的检查，不如dynamic_cast安全。static_cast仅仅是依靠类型转换语句中提供的信息来进行转换，而dynamic_cast则会遍历整个类继承体系进行类型检查，因此dynamic_cast在执行效率上比static_cast要差一些。

```c++
#include <iostream>

class Base {
    virtual void test(){};
};
class Derived : public Base {};

int main()
{
    Derived d1;
    // Implicit cast allowed
    Base* b1 = (Base*)(&d1);
    // upcasting using static_cast
    Base* b2 = static_cast<Base*>(&d1);
    
    Base b3;
    // Implicit cast allowed
    Derived* d2 = (Derived*)(&b3);
    // downcasting using static_cast
    Derived* d3 = static_cast<Derived*>(&b3);
    return 0;
}
```

### 1.4 cast ‘to and from’ Void Pointer

static_cast operator allows casting from any pointer type to void pointer and vice versa.

```c++
#include <iostream>

int main()
{
    int i = 10;
    void* v = static_cast<void*>(&i);
    int* ip = static_cast<int*>(v);
    std::cout << *ip << std::endl;
    return 0;
}
```

## 2. dynamic_cast

dynamic_cast是四个强制类型转换操作符中最特殊的一个，**它支持运行时识别指针或引用**。首先，dynamic_cast依赖于RTTI信息，其次，在转换时，dynamic_cast会检查转换的source对象是否真的可以转换成target类型，这种检查不是语法上的，而是真实情况的检查。基类必须具有虚函数。dynamic_cast是运行时类型信息（RTTI），而这个信息是存储与类的虚函数表关系紧密的信息，只有一个类定义了虚函数，才会有虚函数表。运行时检查，转型不成功则返回一个空指针，非必要不使用dynamic_cast，因为有额外的开销。

- 用于具有虚函数的基类与派生类之间的指针或引用的转换。

- 基类指针或引用 转 派生类指针（必须使用dynamic_cast）
- 派生类指针或引用 转 基类指针（可以使用dynamic_cast，但是更推荐用static_cast）

### 2.1 用于“安全地向下转型”

dynamic_cast**用于类继承层次间的指针或引用转换**。主要还是用于执行“安全的向下转型（safe downcasting）”，也即是基类对象的指针或引用转换为同一继承层次的其他指针或引用。

至于“向上转型”（即派生类指针或引用类型转换为其基类类型）：

- 本身就是安全的，尽管可以使用dynamic_cast进行转换，但这是没必要的。
- 普通的转换已经可以达到目的，**毕竟使用dynamic_cast是需要开销的**。

对于“向下转型”有两种情况：

- 基类指针所指对象是派生类类型的，这种转换是安全的。

- 基类指针所指对象为基类类型，在这种情况下做运行时做检查，转换失败，返回结果为nullptr。

与指针一样，引用的向下转型也可以分为两种情况，**与指针不同的是，并不存在空引用，所以引用的dynamic_cast检测失败时会抛出一个bad_cast异常：**

```c++
#include <iostream>
#include <string>

class Base {
    virtual void test(){};
};
class Derived : public Base {};

int main()
{
    Base b1;
    Derived* d1 = dynamic_cast<Derived*>(&b1);
    if (d1 == nullptr) {
        std::cout << "d1 == nullptr" << std::endl;
    }
 
    Derived d2;
    Base* b2 = &d2;
    Derived* d3 = dynamic_cast<Derived*>(b2);
    if (d3 == nullptr) {
        std::cout << "d3 == nullptr" << std::endl;
    } else {
        std::cout << "d3 != nullptr" << std::endl;
    }

    return 0;
}
```

使用dynamic_cast转换的Base类至少带有一个虚函数, 当一个类中拥有至少一个虚函数的时候，编译器会为该类构建出一个虚函数表（virtual method table），虚函数表记录了虚函数的地址。如果该类派生了其他子类，且子类定义并实现了基类的虚函数，那么虚函数表会将该函数指向新的地址。虚表是C++多态实现的一个重要手段，也是dynamic_cast操作符转换能够进行的前提条件。当类没有虚函数表的时候（也即一个虚函数都没有定义）,dynamic_cast无法使用RTTI，不能通过编译。当然，虚函数表的建立对效率是有一定影响的，构建虚函数表、由表查询函数 都需要时间和空间上的消耗。所以，除了必须声明virtual（对于一个多态基类而言），不要轻易使用virtual函数。

## 3. const_cast

const_cast 是用来强制去掉这种不能被修改的常数特性。不是去除变量的常量性，而是去除指向常数对象的指针或引用的常量性，对象必须为指针或引用。

- 常量指针被转化成非常量指针，并且仍然指向原来的对象；

- 常量引用被转换成非常量引用，并且仍然指向原来的对象；

```c++
#include <iostream>

int main()
{
    const int a = 10;
    const int* p = &a;
    int* q = const_cast<int*>(p);
    *q = 20;    //fine
    std::cout << a <<" " << *p <<" "<< *q << std::endl; // 10 20 20
    std::cout << &a <<" " << p <<" "<< q << std::endl; //0x7ffc5528e8f4 0x7ffc5528e8f4 0x7ffc5528e8f4
    return 0;
}
```

```c++
#include <iostream>

int main()
{
	const int* p = new int(1);
	//int* d = p;//错误原因：const int*类型不能赋值或者初始化int*类型的实体
	*const_cast<int*>(p) = 50;
	std::cout << *p << std::endl;//50
	int* d = const_cast<int*>(p);
	*d = 100;
	std::cout << *p << std::endl;//100
	//char* dd = const_cast<char*>(p)//错误原因：const_cast只能调节类型限定符，不能更改基础类型
	return 0;
}
```

```c++
#include <iostream>

int main()
{
	int a = 10;
	const int& b = a;
	//b = 20;//错误原因：常量引用，不允许修改值
	//int& c = b;//错误，和常量指针不允许给普通指针赋值或者初始化一样

	int& c = const_cast<int&>(b);
	c = 20;
	std::cout << a << std::endl;//20

	const_cast<int&>(b) = 30;
	std::cout << a << std::endl;//30
	return 0;
}
```

## 4. reinterpret_cast

这个和C语言的强制转换没什么区别，只不过C++用自己的写法替代了C语言的强制转换而已。

①不同类型的指针之间的转换

②指针和能容纳指针的整数类型之间的转换（比如将int类型强转成int*类型）

③不同类型的引用之间的转换

编译期处理执行的是逐字节复制的操作。类似于强制转换，至于会产生什么后果需要自己承担。
