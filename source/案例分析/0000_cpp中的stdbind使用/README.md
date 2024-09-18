# 第1章 C++中的std::bind使用

std::bind 是 C++11 中的一个函数模板，用于创建一个可调用对象（函数对象或者函数指针）的绑定副本，其中一部分参数被固定为指定值，从而生成一个新的可调用对象。

std::bind 的原理可以简单概括如下：

**创建绑定副本**：
当调用 std::bind 时，会生成一个新的可调用对象，其中一部分参数被绑定为指定值，剩余的参数保留为占位符（placeholder）。

**占位符**：
在 std::bind 中，占位符使用 _1, _2, _3 等进行表示，分别代表可调用对象的第一个、第二个、第三个参数，以此类推。在创建绑定副本时，可以通过占位符指定参数的位置。

**生成新的可调用对象**：
绑定副本可以作为一个新的可调用对象，可以直接调用，也可以传递给其他接受可调用对象的函数，从而实现部分参数固定的函数调用。

**参数传递**：
在调用绑定副本时，传递给绑定副本的参数会替换掉占位符，从而形成最终的参数列表，并调用原始函数或函数对象。

**绑定对象的生命周期**：
绑定副本会对传递给它的参数进行复制或者引用，因此绑定对象中的参数需要在绑定副本被调用时仍然有效。

## 1. std::bind绑定普通函数

```c++
#include <iostream>
#include <functional>
#include <string>

void print_sum(int a, int b) {
    std::cout << a + b << std::endl;
    std::cout << "a = " << a << std::endl;
    std::cout << "b = " << b << std::endl;
}

int main() {
    //compile error
    //auto f1 = std::bind(print_sum, 10, std::placeholders::_2);
    //f1(20); // 输出 30
    //std::cout << "-----" << std::endl;

    auto f2 = std::bind(print_sum, 10, std::placeholders::_1);
    f2(20); // 输出 30, a=10, b=20
    std::cout << "-----" << std::endl;

    auto f3 = std::bind(print_sum, std::placeholders::_1, std::placeholders::_2);
    f3(20, 30); // 输出 50, a=20, b=30
    std::cout << "-----" << std::endl;

    auto f4 = std::bind(print_sum, std::placeholders::_2, std::placeholders::_1);
    f4(20, 30); // 输出 50, a=30, b=20
    std::cout << "-----" << std::endl;
    return 0;
}
```

## 2. std::bind绑定成员函数

```c++
#include <iostream>
#include <string>
#include <functional>

class Base{
   public:
     void display_sum(int a1, int a2){
        std::cout << a1 + a2 << '\n';
     }

     int m_data = 30;
};

int main() {
    Base base;
    auto newiFunc = std::bind(&Base::display_sum, &base, 100, std::placeholders::_1);
    newiFunc(20); // should out put 120.
}
```

bind绑定类成员函数时，第一个参数表示对象的成员函数的指针，第二个参数表示对象的地址。
必须显式地指定&Base::diplay_sum，因为编译器不会将对象的成员函数隐式转换成函数指针，所以必须在Base::display_sum前添加&；
使用对象成员函数的指针时，必须要知道该指针属于哪个对象，因此第二个参数为对象的地址 &base；
